#include <GL/glew.h>
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
  std::shared_ptr<Renderer> myRenderer(new Renderer(0, 0, width, height, title));
  mData->getFont() = myRenderer->loadFont("data/DroidSans.ttf");
  mData->setRenderer(myRenderer);

  GLuint program = myRenderer->createProgram(std::string("default"));
  GLuint fshader = myRenderer->loadShader(std::string("data/default.frag"), Renderer::Shader_Fragment);
  GLuint vshader = myRenderer->loadShader(std::string("data/default.vert"), Renderer::Shader_Vertex);
  myRenderer->compileShader(fshader);
  myRenderer->compileShader(vshader);
  myRenderer->addShader(program, fshader);
  myRenderer->addShader(program, vshader);
  myRenderer->linkProgram(program);
  myRenderer->useProgram(program);
  myRenderer->clearColor( 0.5, 0.5, 0.5, 0.1 );
  myRenderer->enableBlending();
  myRenderer->enableTexturing();

  glViewport(0, 0, width, height);
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
  std::shared_ptr<Renderer> renderer = mData->getRenderer();
  renderer->begin();
  renderer->clear(true);
  if(mRoot) {
    mRoot->onDraw( dt, mData );
  }
  renderer->end();

  fprintf(stderr, "Dt is %7f\r", dt); 
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