#include "Scriptable.hpp"


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