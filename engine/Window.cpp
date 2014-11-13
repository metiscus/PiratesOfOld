#include <GL/glew.h>

#include <SDL.h>
#include <cassert>
#include <cstdio>

#include "EventManager.hpp"
#include "Window.hpp"

Window::Window(int w, int h, std::string title)
  : mWindow(nullptr)
  , mContext(nullptr)
  , mEventManager(new EventManager())
  , mWidth(w)
  , mHeight(h)
{
  mWindow = SDL_CreateWindow( title.c_str(), 0, 0, w, h, SDL_WINDOW_OPENGL );
  if(!mWindow)
  {
    printf("Failed to create a window.\n");
    exit(1);
  }
  
  mContext = new SDL_GLContext;
  *mContext = SDL_GL_CreateContext(mWindow);
  SDL_GL_MakeCurrent(mWindow, *mContext);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW.\n");
  } 
}

Window::~Window()
{
  assert(0); // unimplemented
}

uint32_t Window::GetWidth() const
{
  return mHeight;
}

uint32_t Window::GetHeight() const
{
  return mWidth;
}

void Window::Swap()
{
  assert(mWindow);
  SDL_GL_SwapWindow(mWindow);
}

void Window::MakeCurrent()
{
  assert(mWindow);
  assert(mContext);
  SDL_GL_MakeCurrent(mWindow, *mContext);
}