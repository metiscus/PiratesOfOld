#include <SDL.h>
#include "Screen.hpp"
#include "ScreenData.hpp"
#include "Window.hpp"

#include <cstdio>

Screen::Screen(int width, int height, std::string title)
  : mWidth(width)
  , mHeight(height)
  , mTitle(title)
  , mData(new ScreenData)
{
  mData->getWindow() = SDL_CreateWindow(title.c_str(),
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width, height, 0);
  
  mData->getRenderer() = SDL_CreateRenderer(mData->getWindow(), -1, SDL_RENDERER_ACCELERATED);
  
}

int Screen::getWidth() const
{
  return mWidth;
}

int Screen::getHeight() const
{
  return mHeight;
}

void Screen::setRoot(std::shared_ptr<Window> window)
{
  mRoot = window;
}

std::shared_ptr<Window> Screen::getRoot()
{
  return mRoot;
}

void Screen::onDraw(float dt)
{
  if(mRoot) {
    mRoot->onDraw( dt, mData );
  }
  
  fprintf(stderr, "Dt is %7f\r", dt);
  
  SDL_RenderClear(mData->getRenderer());
  SDL_RenderPresent(mData->getRenderer());  
}

void Screen::onClick(int x, int y, int button)
{
  if(mRoot) {
    mRoot->onClick(x, y, button);
  }
}

void Screen::onKeypress(int key)
{
  if(mRoot) {
    mRoot->onKeypress(key);
  }
}