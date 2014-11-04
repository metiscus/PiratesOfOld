#include <SDL.h>

#include "Button.hpp"
#include "ScreenData.hpp"

Button::Button(int x, int y, int width, int height, const std::string& text )
  : Window( x, y, width, height )
  , mText(text)
  , mIsPressed(false)
{
  ;
}

void Button::onDraw( float dt, std::shared_ptr<ScreenData> data )
{
  data->getRenderer()->drawText(data->getFont(), Vertex(getPosX() + getHeight() / 2.f, getPosY(), 0.f), mText);
}

bool Button::onClick( int x, int y, int button )
{
  if( contains(x,y) )
  {
    mIsPressed = true;
    return true;
  }
  else {
    mIsPressed = true;
    return false;
  }
}

bool Button::getIsPressed() const
{
  return mIsPressed;
}