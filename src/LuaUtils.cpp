//
//  LuaUtils.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "LuaUtils.h"

void stackDump(lua_State *L) {
  int i;
  int top = lua_gettop(L);
  for(i = 1;i <= top;i++) {
    int t = lua_type(L, i);
    printf("[%d]:", i);
    switch(t) {
      case LUA_TSTRING:
        printf("%s", lua_tostring(L, i));
        break;
      case LUA_TBOOLEAN:
        printf(lua_toboolean(L, i) ? "true" : false);
        break;
      case LUA_TNUMBER:
        printf("%g", lua_tonumber(L, i));
        break;
      default:
        printf("%s", lua_typename(L, i));
        break;
    }
    printf("\n");
  }
  printf("\n");
}

void error(lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  printf("\n[stack dump]\n");
  stackDump(L);
  lua_close(L);
  exit(EXIT_FAILURE);
}

void callLua(lua_State *L, std::string category, int nargs, int nresults, int errfunc) {
  if(lua_pcall(L, nargs, nresults, errfunc) != 0 ) {
    error(L, "[%s]error:%s", category.c_str(), lua_tostring(L, -1));
  }
}

void callLuaFunc(lua_State *L, std::string funcNm, int nargs, int nresults, int errfunc) {
  lua_getglobal(L, funcNm.c_str());
  callLua(L, funcNm, nargs, nresults, errfunc);
}