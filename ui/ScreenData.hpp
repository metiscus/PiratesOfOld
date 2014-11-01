#ifndef SCREENDATA_HPP_
#define SCREENDATA_HPP_

#include <SDL.h>

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
  
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
};

#endif