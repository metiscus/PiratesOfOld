#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <string>
#include <map>
#include <memory>

#include "Drawable.hpp"
#include "Scriptable.hpp"

class ScreenElement;
class Window;

//! \brief Container for ScreenElements (buttons, labels, etc)
class Screen : public Drawable, public Scriptable
{
public:
  Screen();
  virtual ~Screen();
  
  static void RegisterMethods(ScriptEnvironment& env);
  //virtual void UnregisterMethods(ScriptEnvironment& env);
  
  void AddElement(std::string name, ScreenElement *element);
  void RemoveElement(std::string name);
  ScreenElement* GetElement(std::string name);

  void SetWindow(std::shared_ptr<Window> window);
  
private:
  Screen(const Screen& rhs) = delete;
  const Screen& operator=(const Screen&) = delete; 
  
  std::shared_ptr<Window> mWindow;
  std::map<std::string, ScreenElement*> mElements;
};

#endif