#ifndef SCRIPTENVIRONMENT_HPP_
#define SCRIPTENVIRONMENT_HPP_

#include <cassert>
#include <string>
#include <memory>

#include <angelscript.h>

#include "Scriptable.hpp"

class asIScriptEngine;
class asSMessageInfo;

//! \brief Encapsulates the scripting environment
class ScriptEnvironment
{
public:
  ScriptEnvironment();
  ~ScriptEnvironment();
  
  void LoadScript(std::string script);
  
  template<typename T>
  void RegisterClass(std::string name);
  
  template<typename T, typename F>
  void RegisterMemberFunction(std::string className, std::string functionSpec, F function);

  void Call(std::string funcName);
  void Call(std::string funcName, float arg1);
  
  static void MessageCallback(const asSMessageInfo *msg, void *ptr);
  
private:
  ScriptEnvironment(const ScriptEnvironment&) = delete;
  const ScriptEnvironment& operator=(const ScriptEnvironment&) = delete;
  
  asIScriptEngine* mScriptEngine;
};

template<typename T>
void ScriptEnvironment::RegisterClass(std::string name)
{
  int r;
  r = mScriptEngine->RegisterObjectType(name.c_str(), 0, asOBJ_REF); assert(r >= 0);  
  r = mScriptEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_ADDREF, "void f()", asMETHOD(T, AddRef), asCALL_THISCALL); assert(r >= 0);  
  r = mScriptEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_RELEASE, "void f()", asMETHOD(T, Release), asCALL_THISCALL); assert(r >= 0);
  r = mScriptEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_GET_WEAKREF_FLAG, "int &f()", asMETHOD(T, GetWeakRefFlag), asCALL_THISCALL); assert(r >= 0);
  T::RegisterMethods(*this);
}

template<typename T, typename F>
void ScriptEnvironment::RegisterMemberFunction(std::string className, std::string functionSpec, F function)
{
  int r;
  r = mScriptEngine->RegisterObjectMethod(className.c_str(), functionSpec.c_str(), function, asCALL_THISCALL); assert(r >= 0);
}

#endif // SCRIPTENVIRONMENT_HPP_