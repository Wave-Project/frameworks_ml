// Generated from log.mod.py
// DO NOT EDIT
// clang-format off
#include "TestGenerated.h"

namespace generated_tests::log {

void CreateModel(Model *model);
bool is_ignored(int);
std::vector<::test_helper::MixedTypedExample>& get_examples();

TEST_F(GeneratedTests, log) {
    execute(CreateModel,
            is_ignored,
            get_examples());
}

} // namespace generated_tests::log
TEST_AVAILABLE_SINCE(V1_2, log, generated_tests::log::CreateModel)

namespace generated_tests::log {

void CreateModel_dynamic_output_shape(Model *model);
bool is_ignored_dynamic_output_shape(int);
std::vector<::test_helper::MixedTypedExample>& get_examples_dynamic_output_shape();

TEST_F(DynamicOutputShapeTest, log_dynamic_output_shape) {
    execute(CreateModel_dynamic_output_shape,
            is_ignored_dynamic_output_shape,
            get_examples_dynamic_output_shape());
}

} // namespace generated_tests::log

namespace generated_tests::log {

void CreateModel_relaxed(Model *model);
bool is_ignored_relaxed(int);
std::vector<::test_helper::MixedTypedExample>& get_examples_relaxed();

TEST_F(GeneratedTests, log_relaxed) {
    execute(CreateModel_relaxed,
            is_ignored_relaxed,
            get_examples_relaxed());
}

} // namespace generated_tests::log

namespace generated_tests::log {

void CreateModel_relaxed_dynamic_output_shape(Model *model);
bool is_ignored_relaxed_dynamic_output_shape(int);
std::vector<::test_helper::MixedTypedExample>& get_examples_relaxed_dynamic_output_shape();

TEST_F(DynamicOutputShapeTest, log_relaxed_dynamic_output_shape) {
    execute(CreateModel_relaxed_dynamic_output_shape,
            is_ignored_relaxed_dynamic_output_shape,
            get_examples_relaxed_dynamic_output_shape());
}

} // namespace generated_tests::log

namespace generated_tests::log {

void CreateModel_float16(Model *model);
bool is_ignored_float16(int);
std::vector<::test_helper::MixedTypedExample>& get_examples_float16();

TEST_F(GeneratedTests, log_float16) {
    execute(CreateModel_float16,
            is_ignored_float16,
            get_examples_float16());
}

} // namespace generated_tests::log
TEST_AVAILABLE_SINCE(V1_2, log_float16, generated_tests::log::CreateModel_float16)

namespace generated_tests::log {

void CreateModel_float16_dynamic_output_shape(Model *model);
bool is_ignored_float16_dynamic_output_shape(int);
std::vector<::test_helper::MixedTypedExample>& get_examples_float16_dynamic_output_shape();

TEST_F(DynamicOutputShapeTest, log_float16_dynamic_output_shape) {
    execute(CreateModel_float16_dynamic_output_shape,
            is_ignored_float16_dynamic_output_shape,
            get_examples_float16_dynamic_output_shape());
}

} // namespace generated_tests::log
