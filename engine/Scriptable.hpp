#ifndef SCRIPTABLE_HPP_
#define SCRIPTABLE_HPP_

#include <angelscript.h>

class ScriptEnvironment;

//! \brief Interface implemented by objects that are scriptable
class Scriptable
{
public:
  Scriptable();
  virtual ~Scriptable();

  //! \brief Prototype function to register all methods with the script engine
  static void RegisterMethods(ScriptEnvironment& env) { }
  //virtual void UnregisterMethods(ScriptEnvironment& env) = 0;
  
  //! \brief Increase the reference count
  int AddRef();
  
  //! \brief Decrease the reference count (and possibly delete the object)
  int Release();
  
  //! \brief Get the weak reference flag (for use by the scripting system)
  asILockableSharedBool *GetWeakRefFlag();
  
private:
  int mRefCount;  
  asILockableSharedBool *mWeakRefFlag;
};

#endif