#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "Renderer.hpp"

#include <memory>

//! \brief Interface for objects that draw to the screen
class Drawable
{
public:
  Drawable() = default;
  Drawable(const Drawable& rhs) = delete;
  virtual ~Drawable() = default;
  
  virtual void OnCreate(std::shared_ptr<Renderer> renderer) = 0;
  virtual void OnDraw(std::shared_ptr<Renderer> renderer) = 0; 
};

#endif