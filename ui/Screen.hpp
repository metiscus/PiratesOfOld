#ifndef SCREEN_HPP_
#define SCREEN_HPP_

class Window;

#include <string>
#include <map>
#include <memory>

class Screen
{
public:
  Screen();
  ~Screen() = delete;
  
  void SetWindow(std::shared_ptr<Window> window);
  
private:
  Screen(const Screen& rhs) = delete;
  const Screen& operator=(const Screen&) = delete; 
  
  std::shared_ptr<Window> mWindow;
};

#endif