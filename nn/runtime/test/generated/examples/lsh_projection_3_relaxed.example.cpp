// clang-format off
// Generated file (from: lsh_projection_3_relaxed.mod.py). Do not edit
std::vector<MixedTypedExample> examples = {
// Begin of an example
{
.operands = {
//Input(s)
{ // See tools/test_generator/include/TestHarness.h:MixedTyped
  // int -> FLOAT32 map
  {{1, {}}},
  // int -> INT32 map
  {{0, {12345, 54321, 67890, 9876, -12345678, -87654321}}},
  // int -> QUANT8_ASYMM map
  {}
},
//Output(s)
{ // See tools/test_generator/include/TestHarness.h:MixedTyped
  // int -> FLOAT32 map
  {},
  // int -> INT32 map
  {{0, {1, 6, 10, 12}}},
  // int -> QUANT8_ASYMM map
  {}
}
},
}, // End of an example
};

