/**
 * Copyright 2014 Facebook
 * @author Tudor Bosman (tudorb@fb.com)
 */

#include <cstdio>
#include <dlfcn.h>

#include <glog/logging.h>

#ifdef FB_INTERNAL
#include <mkl.h>
#else
#define LUAOPEN(x) luaopen_fbtorch_ext(x)
#endif

#include "Exceptions.h"

using namespace facebook::deeplearning::torch;

extern "C" int print_debug_traceback(lua_State* L) {
  int top = lua_gettop(L);
  lua_getglobal(L, "debug");
  lua_getfield(L, -1, "traceback");
  lua_call(L, 0, 1);
  lua_getglobal(L, "print");
  lua_pushvalue(L, -2);
  lua_call(L, 1, 0);
  lua_settop(L, top);
  return 0;
}

extern "C" int LUAOPEN(lua_State* L) {
  // Ensure that torch is loaded, so it doesn't reset the TH error handler
  lua_getglobal(L, "require");
  lua_pushstring(L, "torch");
  lua_call(L, 1, 1);

  // Note, leaving torch module on the stack, so we can return it
  return 1;  // returning 1 value (torch module)
}
