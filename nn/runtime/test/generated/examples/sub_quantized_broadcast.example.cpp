// clang-format off
// Generated file (from: sub_quantized_broadcast.mod.py). Do not edit
std::vector<MixedTypedExample>& get_examples() {
static std::vector<MixedTypedExample> examples = {
// Begin of an example
{
.operands = {
//Input(s)
{ // See tools/test_generator/include/TestHarness.h:MixedTyped
  // int -> FLOAT32 map
  {},
  // int -> INT32 map
  {},
  // int -> QUANT8_ASYMM map
  {{0, {100, 200}}, {1, {1, 2, 3, 4}}},
  // int -> QUANT16_SYMM map
  {},
  // int -> FLOAT16 map
  {},
  // int -> BOOL8 map
  {},
},
//Output(s)
{ // See tools/test_generator/include/TestHarness.h:MixedTyped
  // int -> FLOAT32 map
  {},
  // int -> INT32 map
  {},
  // int -> QUANT8_ASYMM map
  {{0, {99, 198, 97, 196}}},
  // int -> QUANT16_SYMM map
  {},
  // int -> FLOAT16 map
  {},
  // int -> BOOL8 map
  {},
}
},
}, // End of an example
};
return examples;
};

