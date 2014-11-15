#include "ScreenManager.hpp"

ScreenManager::ScreenManager(std::shared_ptr<Window> window)
  : mWindow(nullptr)
{
  
}
  
void ScreenManager::RegisterMethods(ScriptEnvironment& env)
{
  
}
 

void ScreenManager::LoadScreen(const std::string& name)
{
  
}

void ScreenManager::ShowScreen(const std::string& name)
{
  
}

void ScreenManager::Show()
{
  mIsVisible = true;
}

void ScreenManager::Hide()
{
  mIsVisible = false;
}

bool ScreenManager::IsVisible()
{
  return mIsVisible;
}