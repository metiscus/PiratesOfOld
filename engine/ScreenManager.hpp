#ifndef SCREENMANAGER_HPP_
#define SCREENMANAGER_HPP_

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "Drawable.hpp"
#include "Scriptable.hpp"

class Screen;
class Window;

class ScreenManager : public Scriptable
{
public:
  ScreenManager(std::shared_ptr<Window> window);
  virtual ~ScreenManager() = default;
  
  static void RegisterMethods(ScriptEnvironment& env);
  //virtual void UnregisterMethods(ScriptEnvironment& env);
  
  void LoadScreen(const std::string& name);
  void ShowScreen(const std::string& name);
  void Show();
  void Hide();
  bool IsVisible();
  
private:
  bool mIsVisible;
  std::vector< std::shared_ptr<Screen> > mCurrentScreen;
  std::map< std::string, std::shared_ptr<Screen> > mScreens;
  std::shared_ptr<Window> mWindow;
};

#endif