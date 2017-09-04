/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "LSTM.h"

#include "CpuExecutor.h"
#include "HalInterfaces.h"

namespace android {
namespace nn {

// TODO: move the kernels to a separate file as soon as we have the
// optimized version ready.
namespace {

template <typename T>
T getScalarData(RunTimeOperandInfo& info) {
    T * data = reinterpret_cast<T*>(info.buffer);
    return data[0];
}

// Limit a float input f between +abs_limit and -abs_limit.
inline float Clip(float f, float abs_limit) {
  float result = (abs_limit < f) ? abs_limit : f;
  result = (-abs_limit > result) ? -abs_limit : result;
  return result;
}

// Multiply a matrix by a batch vector, and store results in a batch-size
// vector.
void MatrixBatchVectorMultiplyAccumulate(const float* matrix, int m_rows,
                                         int m_cols, const float* vector,
                                         int n_batch, float* result) {
  for (int b = 0; b < n_batch; b++) {
    float* result_in_batch = result + b * m_rows;
    const float* matrix_ptr = matrix;
    for (int r = 0; r < m_rows; r++) {
      const float* vector_in_batch = vector + b * m_cols;
      for (int c = 0; c < m_cols; c++) {
        *result_in_batch += *matrix_ptr++ * *vector_in_batch++;
      }
      result_in_batch++;
    }
  }
}

// Cwise product of two vectors.
void VectorVectorCwiseProduct(const float* vector1, const float* vector2,
                              int v_size, float* result) {
  for (int v = 0; v < v_size; v++) {
    *result++ = *vector1++ * *vector2++;
  }
}

// Cwise product and accumulation of two vectors. Since it's a MAC operation, the
// assumption here is that result array is initialized to valid values.
void VectorVectorCwiseProductAccumulate(const float* vector1,
                                        const float* vector2, int v_size,
                                        float* result) {
  for (int v = 0; v < v_size; v++) {
    *result++ += *vector1++ * *vector2++;
  }
}

// Cwise product and accumulation of a vector and a batch-vector. Since it's a MAC
// operation, the assumption here is that result array is initialized to valid
// values.
void VectorBatchVectorCwiseProductAccumulate(const float* vector, int v_size,
                                             const float* batch_vector,
                                             int n_batch, float* result) {
  for (int b = 0; b < n_batch; b++) {
    for (int v = 0; v < v_size; v++) {
      *result++ += vector[v] * *batch_vector++;
    }
  }
}

// Batch vector initialization with another vector.
void VectorBatchVectorAssign(const float* vector, int v_size, int n_batch,
                             float* batch_vector) {
  for (int b = 0; b < n_batch; b++) {
    memcpy(batch_vector + b * v_size, vector, v_size * sizeof(float));
  }
}

// Apply sigmoid to elements of a vector.
void ApplySigmoidToVector(const float* vector, int v_size, float* result) {
  auto sigmoid_func = ActivationFunctor(kActivationSigmoid);
  for (int v = 0; v < v_size; v++) {
    *result++ = (sigmoid_func)(*vector++);
  }
}

// Apply activation function to elements of a vector.
void ApplyActivationToVector(const float* vector, int v_size,
                             ActivationFn activation, float* result) {
  auto activation_func = ActivationFunctor(activation);
  for (int v = 0; v < v_size; v++) {
    *result++ = (activation_func)(*vector++);
  }
}

// Copy vector to another vector.
inline void CopyVector(const float* vector, int v_size, float* result) {
  memcpy(result, vector, v_size * sizeof(float));
}

// Compute "1.0f - elements of vector" (used in CIFG).
void Sub1Vector(const float* vector, int v_size, float* result) {
  for (int v = 0; v < v_size; v++) {
    *result++ = 1.0f - *vector++;
  }
}

// Fill vector with 0.f.
void ZeroVector(float* vector, int v_size) {
  memset(vector, 0, v_size * sizeof(float));
}

// Clip elements of a vector using a abs_limit value.
void ClipVector(const float* vector, int v_size, float abs_limit,
                float* result) {
  for (int v = 0; v < v_size; v++) {
    *result++ = Clip(*vector++, abs_limit);
  }
}

template <typename T>
inline T *GetBuffer(RunTimeOperandInfo* operand) {
  return reinterpret_cast<T*>(operand->buffer);
}

template <typename T>
inline const T *GetBuffer(const RunTimeOperandInfo* operand) {
  return reinterpret_cast<const T*>(operand->buffer);
}

}  // anonymous namespace

LSTMCell::LSTMCell(const Operation& operation,
                   std::vector<RunTimeOperandInfo>& operands) {
  auto GetInput = [&operation,
                   &operands](uint32_t index) -> const RunTimeOperandInfo* {
    const std::vector<uint32_t>& inputs = operation.inputs;
    const int index_of_operand = inputs[index];
    if (index_of_operand < 0) {
      return nullptr;
    }
    return &operands[index_of_operand];
  };

  auto GetOutput = [&operation,
                    &operands](uint32_t index) -> RunTimeOperandInfo* {
    const std::vector<uint32_t>& outputs = operation.outputs;
    const int index_of_operand = outputs[index];
    // Expects index of operand in range.
    return &operands[index_of_operand];
  };

  input_ = GetInput(kInputTensor);

  input_to_input_weights_ = GetInput(kInputToInputWeightsTensor);  // optional
  input_to_forget_weights_ = GetInput(kInputToForgetWeightsTensor);
  input_to_cell_weights_ = GetInput(kInputToCellWeightsTensor);
  input_to_output_weights_ = GetInput(kInputToOutputWeightsTensor);

  recurrent_to_input_weights_ =
      GetInput(kRecurrentToInputWeightsTensor);  // optional
  recurrent_to_forget_weights_ = GetInput(kRecurrentToForgetWeightsTensor);
  recurrent_to_cell_weights_ = GetInput(kRecurrentToCellWeightsTensor);
  recurrent_to_output_weights_ = GetInput(kRecurrentToOutputWeightsTensor);

  cell_to_input_weights_ = GetInput(kCellToInputWeightsTensor);    // optional
  cell_to_forget_weights_ = GetInput(kCellToForgetWeightsTensor);  // optional
  cell_to_output_weights_ = GetInput(kCellToOutputWeightsTensor);  // optional

  input_gate_bias_ = GetInput(kInputGateBiasTensor);
  forget_gate_bias_ = GetInput(kForgetGateBiasTensor);
  cell_bias_ = GetInput(kCellGateBiasTensor);
  output_gate_bias_ = GetInput(kOutputGateBiasTensor);

  projection_weights_ = GetInput(kProjectionWeightsTensor);  // optional
  projection_bias_ = GetInput(kProjectionBiasTensor);        // optional

  params_.activation_ = static_cast<ActivationFn>(getScalarData<int32_t>(operands[operation.inputs[kActivationParam]]));
  params_.cell_clip_ = getScalarData<float>(operands[operation.inputs[kCellClipParam]]);
  params_.proj_clip_ = getScalarData<float>(operands[operation.inputs[kProjClipParam]]);

  output_state_ = GetOutput(kOutputStateTensor);
  cell_state_ = GetOutput(kCellStateTensor);
  output_ = GetOutput(kOutputTensor);

  scratch_buffer_ = GetOutput(kScratchBufferTensor);
}

bool LSTMCell::Eval() {
  const uint32_t n_batch = input_->shape().dimensions[0];
  const uint32_t n_input = input_->shape().dimensions[1];
  // n_cell and n_output will be the same size when there is no projection.
  const uint32_t n_cell = input_to_output_weights_->shape().dimensions[0];
  const uint32_t n_output = recurrent_to_output_weights_->shape().dimensions[1];

  // Since we have already checked that weights are all there or none, we can
  // check the existence of only one to the get the condition.
  const bool use_cifg = (input_to_input_weights_->buffer == nullptr);
  const bool use_peephole = (cell_to_output_weights_->buffer != nullptr);

  // Index the scratch buffers pointers to the global scratch buffer.
  float* input_gate_scratch = nullptr;
  float* cell_scratch = nullptr;
  float* forget_gate_scratch = nullptr;
  float* output_gate_scratch = nullptr;
  if (use_cifg) {
    cell_scratch = reinterpret_cast<float*>(scratch_buffer_->buffer);
    forget_gate_scratch = cell_scratch + n_cell * n_batch;
    output_gate_scratch = cell_scratch + 2 * n_cell * n_batch;
  } else {
    input_gate_scratch = reinterpret_cast<float*>(scratch_buffer_->buffer);
    cell_scratch = input_gate_scratch + n_cell * n_batch;
    forget_gate_scratch = input_gate_scratch + 2 * n_cell * n_batch;
    output_gate_scratch = input_gate_scratch + 3 * n_cell * n_batch;
  }

  // Initialize scratch buffers with bias.
  if (!use_cifg) {
    VectorBatchVectorAssign(GetBuffer<float>(input_gate_bias_), n_cell, n_batch,
                            input_gate_scratch);
  }
  VectorBatchVectorAssign(GetBuffer<float>(forget_gate_bias_), n_cell, n_batch,
                          forget_gate_scratch);
  VectorBatchVectorAssign(GetBuffer<float>(cell_bias_), n_cell, n_batch,
                          cell_scratch);
  VectorBatchVectorAssign(GetBuffer<float>(output_gate_bias_), n_cell, n_batch,
                          output_gate_scratch);

  // For each batch and cell: compute input_weight * input.
  if (!use_cifg) {
    MatrixBatchVectorMultiplyAccumulate(
        GetBuffer<float>(input_to_input_weights_), n_cell, n_input,
        GetBuffer<float>(input_), n_batch, input_gate_scratch);
  }
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(input_to_forget_weights_), n_cell, n_input,
      GetBuffer<float>(input_), n_batch, forget_gate_scratch);
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(input_to_cell_weights_), n_cell, n_input,
      GetBuffer<float>(input_), n_batch, cell_scratch);
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(input_to_output_weights_), n_cell, n_input,
      GetBuffer<float>(input_), n_batch, output_gate_scratch);

  // For each batch and cell: compute recurrent_weight * output_state.
  if (!use_cifg) {
    MatrixBatchVectorMultiplyAccumulate(
        GetBuffer<float>(recurrent_to_input_weights_), n_cell, n_output,
        GetBuffer<float>(output_state_), n_batch, input_gate_scratch);
  }
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(recurrent_to_forget_weights_), n_cell, n_output,
      GetBuffer<float>(output_state_), n_batch, forget_gate_scratch);
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(recurrent_to_cell_weights_), n_cell, n_output,
      GetBuffer<float>(output_state_), n_batch, cell_scratch);
  MatrixBatchVectorMultiplyAccumulate(
      GetBuffer<float>(recurrent_to_output_weights_), n_cell, n_output,
      GetBuffer<float>(output_state_), n_batch, output_gate_scratch);

  // For each batch and cell: update input gate.
  if (!use_cifg) {
    if (use_peephole) {
      VectorBatchVectorCwiseProductAccumulate(
          GetBuffer<float>(cell_to_input_weights_), n_cell,
          GetBuffer<float>(cell_state_), n_batch, input_gate_scratch);
    }
    ApplySigmoidToVector(input_gate_scratch, n_cell * n_batch,
                         input_gate_scratch);
  }

  // For each batch and cell: update forget gate.
  if (use_peephole) {
    VectorBatchVectorCwiseProductAccumulate(
        GetBuffer<float>(cell_to_forget_weights_), n_cell,
        GetBuffer<float>(cell_state_), n_batch, forget_gate_scratch);
  }
  ApplySigmoidToVector(forget_gate_scratch, n_cell * n_batch,
                       forget_gate_scratch);

  // For each batch and cell: update the cell.
  VectorVectorCwiseProduct(forget_gate_scratch, GetBuffer<float>(cell_state_),
                           n_batch * n_cell, GetBuffer<float>(cell_state_));
  ApplyActivationToVector(cell_scratch, n_batch * n_cell, params_.activation_,
                          cell_scratch);
  if (use_cifg) {
    Sub1Vector(forget_gate_scratch, n_batch * n_cell, forget_gate_scratch);
    VectorVectorCwiseProductAccumulate(cell_scratch, forget_gate_scratch,
                                       n_batch * n_cell,
                                       GetBuffer<float>(cell_state_));
  } else {
    VectorVectorCwiseProductAccumulate(cell_scratch, input_gate_scratch,
                                       n_batch * n_cell,
                                       GetBuffer<float>(cell_state_));
  }
  if (params_.cell_clip_ > 0.0) {
    ClipVector(GetBuffer<float>(cell_state_), n_batch * n_cell,
               params_.cell_clip_, GetBuffer<float>(cell_state_));
  }

  // For each batch and cell: update the output gate.
  if (use_peephole) {
    VectorBatchVectorCwiseProductAccumulate(
        GetBuffer<float>(cell_to_output_weights_), n_cell,
        GetBuffer<float>(cell_state_), n_batch, output_gate_scratch);
  }
  ApplySigmoidToVector(output_gate_scratch, n_batch * n_cell,
                       output_gate_scratch);
  ApplyActivationToVector(GetBuffer<float>(cell_state_), n_batch * n_cell,
                          params_.activation_, cell_scratch);
  VectorVectorCwiseProduct(output_gate_scratch, cell_scratch, n_batch * n_cell,
                           output_gate_scratch);

  // For each batch: update the projection and output_state.
  const bool use_projection_weight = (projection_weights_->buffer != nullptr);
  const bool use_projection_bias = (projection_bias_->buffer != nullptr);
  if (use_projection_weight) {
    if (use_projection_bias) {
      VectorBatchVectorAssign(GetBuffer<float>(projection_bias_), n_output,
                              n_batch, GetBuffer<float>(output_));
    } else {
      ZeroVector(GetBuffer<float>(output_), n_batch * n_output);
    }
    MatrixBatchVectorMultiplyAccumulate(GetBuffer<float>(projection_weights_),
                                        n_output, n_cell, output_gate_scratch,
                                        n_batch, GetBuffer<float>(output_));
    if (params_.proj_clip_ > 0.0) {
      ClipVector(GetBuffer<float>(output_), n_batch * n_output,
                 params_.proj_clip_, GetBuffer<float>(output_));
    }
  } else {
    CopyVector(output_gate_scratch, n_batch * n_output,
               GetBuffer<float>(output_));
  }
  CopyVector(GetBuffer<float>(output_), n_batch * n_output,
             GetBuffer<float>(output_state_));

  return true;
}

}  // namespace nn
}  // namespace android