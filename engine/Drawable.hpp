#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "Renderer.hpp"

class Drawable
{
public:
  Drawable();
  Drawable(const Drawable& rhs) = delete;
  virtual ~Drawable() = delete;
  
  virtual void OnDraw() = 0; 
};

#endif