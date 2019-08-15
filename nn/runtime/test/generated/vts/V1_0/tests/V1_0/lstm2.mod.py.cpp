// Generated from lstm2.mod.py
// DO NOT EDIT
// clang-format off
#include "GeneratedTests.h"

namespace generated_tests::lstm2 {

std::vector<::test_helper::MixedTypedExample>& get_examples();

} // namespace generated_tests::lstm2

namespace android::hardware::neuralnetworks::V1_0::generated_tests::lstm2 {

Model createTestModel();
bool is_ignored(int);

TEST_F(NeuralnetworksHidlTest, lstm2) {
  Execute(device,
          createTestModel,
          is_ignored,
          ::generated_tests::lstm2::get_examples());
}

TEST_F(ValidationTest, lstm2) {
  const Model model = createTestModel();
  const std::vector<Request> requests = createRequests(::generated_tests::lstm2::get_examples());
  validateEverything(model, requests);
}

} // namespace android::hardware::neuralnetworks::V1_0::generated_tests::lstm2

