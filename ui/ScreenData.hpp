#ifndef SCREENDATA_HPP_
#define SCREENDATA_HPP_

#include <SDL.h>
#include <SDL_ttf.h>

class ScreenData
{
public:
  ScreenData()
  {
    mWindow   = nullptr;
    mRenderer = nullptr;
  }
  
  ~ScreenData()
  {
    if(mRenderer) SDL_DestroyRenderer(mRenderer);
    if(mWindow) SDL_DestroyWindow(mWindow);
  }

  SDL_Window*& getWindow() { return mWindow; }
  SDL_Renderer*& getRenderer() { return mRenderer; }
  TTF_Font*& getFont() { return mFont; }
  SDL_Texture*& getTexture() { return mTexture; }
  
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  TTF_Font *mFont;
  SDL_Texture *mTexture;
};

#endif