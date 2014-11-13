#include "LuaEnvironment.hpp"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <cassert>
#include <cstdio>
#include <functional>

LuaEnvironment::LuaEnvironment()
  : mLua(nullptr)
{
    mLua = luaL_newstate();
    luaL_openlibs(mLua);
}

LuaEnvironment::~LuaEnvironment()
{
  lua_close(mLua);
}

void LuaEnvironment::LoadScript(std::string script)
{
  luaL_loadstring(mLua, script.c_str());
  lua_pcall(mLua, 0, 0, 0);
}

void LuaEnvironment::Call(std::string funcName)
{
  assert(mLua);
  lua_getglobal(mLua, funcName.c_str());
  if(lua_pcall(mLua, 0, 0, 0)!=0)
  {
    printf("Call to %s failed.\n", funcName.c_str());
  }

//  luaL_dofile(mLua, "data/scripts/main.lua");
}

void LuaEnvironment::Call(std::string funcName, float arg1)
{
  assert(mLua);
  lua_getglobal(mLua, funcName.c_str());
  lua_pushnumber(mLua, arg1);
  if(lua_pcall(mLua, 1, 0, 0)!=0)
  {
    printf("Call to %s failed.\n", funcName.c_str());
  }  
}
