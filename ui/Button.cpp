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
  // draw back of button
  QuadInfo quad;
  quad.from.r = quad.from.g = quad.from.b = 0.3;
  quad.to.r = quad.to.g = quad.to.b = 0.3;
  quad.from.x = getPosX() - 0.5f*getWidth();
  quad.to.x   = getPosX() + 0.5f*getWidth();
  quad.from.y = getPosY() - 0.5f*getHeight();
  quad.to.y   = getPosY() + 0.5f*getHeight();
  
  data->getRenderer()->drawQuad(quad);

  Vertex cursor (getPosX() - 0.5*getWidth(), getPosY(), 0.f);
  if(mIsPressed) {
    cursor.b = 1.0f;
  }
  else {
    cursor.r = cursor.g = cursor.b = 1.f;
  }
  //cursor.x -= (mText.length() * 32.) / 2.;
  data->getRenderer()->drawText(data->getFont(), cursor, mText);
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