// clang-format off
// Generated file (from: svdf_float16.mod.py). Do not edit
#include "../../TestGenerated.h"

namespace svdf_float16 {
// Generated svdf_float16 test
#include "generated/examples/svdf_float16.example.cpp"
// Generated model constructor
#include "generated/models/svdf_float16.model.cpp"
} // namespace svdf_float16

TEST_F(GeneratedTests, svdf_float16) {
    execute(svdf_float16::CreateModel,
            svdf_float16::is_ignored,
            svdf_float16::get_examples());
}

