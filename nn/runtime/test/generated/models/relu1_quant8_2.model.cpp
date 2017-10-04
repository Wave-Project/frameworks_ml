// Generated file (from: relu1_quant8_2.mod.py). Do not edit
void CreateModel(Model *model) {
  OperandType type0(Type::TENSOR_QUANT8_ASYMM, {2, 256, 256, 2}, 1.f, 128);
  // Phase 1, operands
  auto input = model->addOperand(&type0);
  auto output = model->addOperand(&type0);
  // Phase 2, operations
  model->addOperation(ANEURALNETWORKS_RELU1, {input}, {output});
  // Phase 3, inputs and outputs
  model->setInputsAndOutputs(
    {input},
    {output});
  assert(model->isValid());
}

bool is_ignored(int i) {
  static std::set<int> ignore = {};
  return ignore.find(i) != ignore.end();
}