#ifndef SCREENDATA_HPP_
#define SCREENDATA_HPP_

#include "Renderer.hpp"

class ScreenData
{
public:
  ScreenData()
    : mRenderer(nullptr)
    , mFont(0)
    , mProgram(0)
  {
  }

  void setRenderer(std::shared_ptr<Renderer> renderer) { mRenderer = renderer; }
  std::shared_ptr<Renderer> getRenderer() { return mRenderer; }
  GLuint& getFont() { return mFont; }
  GLuint& getProgram() { return mProgram; }
  
private:
  std::shared_ptr<Renderer> mRenderer;
  GLuint mFont;
  GLuint mProgram;
};

#endif