#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/Tanh.c"
#else

static int nn_(Tanh_forward)(lua_State *L)
{
  THTensor *input = luaT_checkudata(L, 2, torch_(Tensor_id));
  THTensor *output = luaT_getfieldcheckudata(L, 1, "output", torch_(Tensor_id));

  THTensor_(resizeAs)(output, input);

  TH_TENSOR_APPLY2(real, output, real, input,   \
                   *output_data = tanh(*input_data);)

  return 1;
}

static int nn_(Tanh_updateGradInput)(lua_State *L)
{
  THTensor *gradOutput = luaT_checkudata(L, 3, torch_(Tensor_id));
  THTensor *output = luaT_getfieldcheckudata(L, 1, "output", torch_(Tensor_id));
  THTensor *gradInput = luaT_getfieldcheckudata(L, 1, "gradInput", torch_(Tensor_id));

  THTensor_(resizeAs)(gradInput, output);
  TH_TENSOR_APPLY3(real, gradInput, real, gradOutput, real, output, \
                   real z = *output_data;                              \
                   *gradInput_data = *gradOutput_data * (1. - z*z););
  return 1;
}

static const struct luaL_Reg nn_(Tanh__) [] = {
  {"Tanh_forward", nn_(Tanh_forward)},
  {"Tanh_updateGradInput", nn_(Tanh_updateGradInput)},
  {NULL, NULL}
};

static void nn_(Tanh_init)(lua_State *L)
{
  luaT_pushmetaclass(L, torch_(Tensor_id));
  luaT_registeratname(L, nn_(Tanh__), "nn");
  lua_pop(L,1);

}

#endif
