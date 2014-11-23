#include "ScreenElement.hpp"

ScreenElement::ScreenElement(int x, int y, int w, int h)
  : mCenterX(x), mCenterY(y), mWidth(w), mHeight(h)
{
  ;
}

const bool& ScreenElement::GetIsVisible() const
{
  return mIsVisible;
}

void ScreenElement::SetVisible(bool visible)
{
  mIsVisible = visible;
}