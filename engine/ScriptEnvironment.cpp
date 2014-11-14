#include "ScriptEnvironment.hpp"
#include <add_on/scriptstdstring/scriptstdstring.h>

#include <cassert>
#include <cstdio>
#include <functional>

Scriptable::Scriptable()
  : mRefCount(1)
  , mWeakRefFlag(nullptr)
{
  
}

Scriptable::~Scriptable()
{
  if(mWeakRefFlag)
  {
    // Tell the ones that hold weak references that the object is destroyed
    mWeakRefFlag->Set(true);
    mWeakRefFlag->Release();
  }
}

int Scriptable::AddRef()
{
  return ++mRefCount;
}

int Scriptable::Release()
{
  if(--mRefCount == 0)
  {
    delete this;
    return 0;
  }
  return mRefCount;
}

asILockableSharedBool* Scriptable::GetWeakRefFlag()
{
  if(!mWeakRefFlag)
  {
    mWeakRefFlag = asCreateLockableSharedBool();
  }

  return mWeakRefFlag;  
}

void print(const std::string& text)
{
  printf("[script] : %s\n", text.c_str());
}

ScriptEnvironment::ScriptEnvironment()
  : mScriptEngine(nullptr)
{
  mScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  assert(mScriptEngine);
  
  RegisterStdString(mScriptEngine);
  
  if(mScriptEngine->GetModule("main", asGM_ALWAYS_CREATE) == 0)
  {
    assert(false);
  }
    
  mScriptEngine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
  mScriptEngine->RegisterGlobalFunction("void print(const string& in)", asFUNCTION(print), asCALL_CDECL);
}

ScriptEnvironment::~ScriptEnvironment()
{

}

void ScriptEnvironment::MessageCallback(const asSMessageInfo *msg, void *ptr)
{
  const char *type = "ERR ";
  if(msg->type == asMSGTYPE_WARNING)
  {
    type = "WARN";
  }
  else if(msg->type == asMSGTYPE_INFORMATION)
  {
    type = "INFO";
  }
  
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);  
}

void ScriptEnvironment::LoadScript(std::string script)
{
  mScriptEngine->SetEngineProperty(asEP_COPY_SCRIPT_SECTIONS, true);
  asIScriptModule *mod = mScriptEngine->GetModule("main", asGM_CREATE_IF_NOT_EXISTS);
  mod->AddScriptSection("main", script.c_str(), script.size(), 0);
  mod->Build();
}

void ScriptEnvironment::Call(std::string funcName)
{
  asIScriptModule *mod = mScriptEngine->GetModule("main", asGM_ONLY_IF_EXISTS);
  asIScriptFunction *func = mod->GetFunctionByDecl(funcName.c_str());
  if(func == 0)
  {
    printf("The script must have the function '%s'. Please add it and try again.\n", funcName.c_str());
    return;
  }
  
  // Create our context, prepare it, and then execute
  asIScriptContext *ctx = mScriptEngine->CreateContext();
  ctx->Prepare(func);
  int r = ctx->Execute();
  if(r != asEXECUTION_FINISHED)
  {
    // The execution didn't complete as expected. Determine what happened.
    if(r == asEXECUTION_EXCEPTION)
    {
      // An exception occurred, let the script writer know what happened so it can be corrected.
      printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
    }
  }
  
  ctx->Unprepare();
}

void ScriptEnvironment::Call(std::string funcName, float arg1)
{

 
}
