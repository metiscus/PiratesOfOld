#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Window.hpp"

#include <string>

class Button : public Window
{
public:
  Button(int x, int y, int width, int height, const std::string& text );
  virtual void onDraw( float dt, std::shared_ptr<ScreenData> data );
  virtual bool onClick( int x, int y, int button );
  
  bool getIsPressed() const;
  
private:
  std::string mText;
  bool mIsPressed;
};

#endif