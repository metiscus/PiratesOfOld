#include "ScreenElement.hpp"
#include "ScriptEnvironment.hpp"

ScreenElement::ScreenElement()
  : mCenterX(0.f)
  , mCenterY(0.f)
  , mWidth(0.f)
  , mHeight(0.f)
{
  ;
}

void ScreenElement::RegisterMethods(ScriptEnvironment& env)
{
  env.RegisterMemberFunction<ScreenElement>("ScreenElement", "float GetCenterX() const", asMETHOD(ScreenElement, GetCenterX));
  env.RegisterMemberFunction<ScreenElement>("ScreenElement", "float GetCenterY() const", asMETHOD(ScreenElement, GetCenterY));
  env.RegisterMemberFunction<ScreenElement>("ScreenElement", "float GetWidth() const", asMETHOD(ScreenElement, GetWidth));
  env.RegisterMemberFunction<ScreenElement>("ScreenElement", "float GetHeight() const", asMETHOD(ScreenElement, GetHeight));
  env.RegisterMemberFunction<ScreenElement>("ScreenElement", "bool Contains(float x, float y) const", asMETHOD(ScreenElement, Contains));
}

float ScreenElement::GetCenterX() const
{
  return mCenterX;
}

float ScreenElement::GetCenterY() const
{
  return mCenterY;
}

float ScreenElement::GetWidth() const
{
  return mWidth;
}

float ScreenElement::GetHeight() const
{
  return mHeight;
}

bool ScreenElement::Contains(float x, float y) const
{
  float minX = mCenterX - 0.5f * mWidth;
  float minY = mCenterY - 0.5f * mHeight;
  float maxX = mCenterX + 0.5f * mWidth;
  float maxY = mCenterY + 0.5f * mHeight;
  return x > minX && x < maxX && y > minY && y < maxY;
}
