#ifndef LUAENVIRONMENT_HPP_
#define LUAENVIRONMENT_HPP_

struct lua_State;

#include <string>

class LuaEnvironment
{
public:
  LuaEnvironment();
  ~LuaEnvironment();
  
  void LoadScript(std::string script);
  void Call(std::string funcName);
  void Call(std::string funcName, float arg1);

private:
  LuaEnvironment(const LuaEnvironment&) = delete;
  const LuaEnvironment& operator=(const LuaEnvironment&) = delete;
  
  lua_State *mLua;
};

#endif 