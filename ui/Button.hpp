#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "ScreenElement.hpp"

#include <string>
#include <memory>

class Button : public ScreenElement
{
public:
  Button(int x, int y, int width, int height, const std::string& text);

  virtual void OnDraw();
  
private:
  std::string mText;
  bool mIsPressed;
};

#endif