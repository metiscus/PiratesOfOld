#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <memory>

class ScreenData;

class WindowBase
{
public:
  WindowBase() = default;
  virtual ~WindowBase() = default;
  
  virtual void onDraw( float dt, std::shared_ptr<ScreenData> data ) = 0;
  virtual void onClick( int x, int y, int button ) = 0;
  virtual void onMouseMove( int x, int y ) = 0;
  virtual void onKeypress( int key ) = 0;
};

class Window : public WindowBase
{
public:
  
  
private:
  
};

#endif 