#ifndef BUTTON_HPP_
#define BUTTON_HPP_

//tolua_begin
#include "engine/Drawable.hpp"

#include <string>
#include <memory>

class Button : public Drawable
{
public:
  Button(int x, int y, int width, int height, const std::string& text);

  virtual void OnDraw();
  
private:
  std::string mText;
  bool mIsPressed;
};

#endif