#include <SDL.h>
//#include <SDL_ttf.h>

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
  /*
  SDL_Color TXT_Color;
  if( mIsPressed )
  {
    TXT_Color.r = 0xAA;
    TXT_Color.g = 0xAA;
    TXT_Color.b = 0xFF;
  }
  else {
    TXT_Color.r = 0xFF;
    TXT_Color.g = 0xFF;
    TXT_Color.b = 0xFF;
  }
  
  SDL_Surface *textMsg = TTF_RenderText_Solid(data->getFont(), mText.c_str(), TXT_Color);
  SDL_Rect dest;
  dest.x = mPosX;
  dest.y = mPosY;
  dest.w = mWidth;
  dest.h = mHeight;
  
  SDL_Texture *button = SDL_CreateTextureFromSurface(data->getRenderer(), textMsg);
  SDL_RenderCopy(data->getRenderer(), button, NULL, NULL);
  SDL_UpdateTexture(button, &dest, textMsg->pixels, textMsg->pitch);
  SDL_FreeSurface(textMsg);
  SDL_DestroyTexture(button);
  */
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