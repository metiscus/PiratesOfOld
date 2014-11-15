#ifndef SCREENELEMENT_HPP_
#define SCREENELEMENT_HPP_

#include "Drawable.hpp"
#include "EventListener.hpp"
#include "Scriptable.hpp"

class ScreenElement : public Drawable, public EventListener, public Scriptable
{
public:
  ScreenElement();
  virtual ~ScreenElement() = default;
  
  static void RegisterMethods(ScriptEnvironment& env);
  //virtual void UnregisterMethods(ScriptEnvironment& env);
  
  float GetCenterX() const;
  float GetCenterY() const;
  float GetWidth() const;
  float GetHeight() const;
  
  bool Contains(float x, float y) const;

protected:
  float mCenterX, mCenterY;
  float mWidth, mHeight;
  
private:
  ScreenElement(const ScreenElement&) = delete;
  const ScreenElement& operator=(const ScreenElement&) = delete;
};


#endif