#include "Renderer.hpp"

#include <cstdio>
#include <GL/glew.h>

Renderer::Renderer(int x, int y, int w, int h, std::string title)
{
  mWindow = SDL_CreateWindow( title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL );
  if(!mWindow)
  {
    printf("Failed to create a window.\n");
    exit(1);
  }
  
  mContext = SDL_GL_CreateContext(mWindow);
  SDL_GL_MakeCurrent(mWindow, mContext);
  if(!glewInit())
  {
    printf("Failed to initialize GLEW.\n");
  }
}

Renderer::~Renderer()
{
  
}