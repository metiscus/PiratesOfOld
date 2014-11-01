#include "Window.hpp"

#include <algorithm>

Window::Window(int x, int y, int w, int h)
  : mPosX(x)
  , mPosY(y)
  , mWidth(w)
  , mHeight(h)
{
  ; 
}

void Window::setPosition(int x, int y)
{
  mPosX = x;
  mPosY = y;
}

void Window::setSize(int w, int h)
{
  mWidth = w;
  mHeight = h;
}

int Window::getWidth() const
{
  return mWidth;
}

int Window::getHeight() const
{
  return mHeight;
}

int Window::getPosX() const
{
  return mPosX;
}

int Window::getPosY() const
{
  return mPosY;
}

bool Window::contains(int x, int y) const
{
  return ((x >= mPosX && x <= mPosX+mWidth) && 
          (y >= mPosY && y <= mPosY+mHeight));
}

void Window::onDraw( float dt, std::shared_ptr<ScreenData> data )
{
  auto itr = mChildren.begin();
  for( ; itr != mChildren.end(); ++itr )
  {
    (*itr)->onDraw(dt, data);
  }
}

bool Window::onClick( int x, int y, int button )
{
  bool ret = false;
  auto itr = mChildren.begin();
  for( ; itr != mChildren.end(); ++itr )
  {
    auto child = (*itr);
    ret = child->onClick(x, y, button);
    if(ret) { break; }
  }
  
  return ret;
}

bool Window::onMouseMove( int x, int y )
{
  bool ret = false;
  auto itr = mChildren.begin();
  for( ; itr != mChildren.end(); ++itr )
  {
    auto child = (*itr);
    ret = child->onMouseMove(x, y);
    if(ret) { break; }
  }
  
  return ret;
}

bool Window::onKeypress( int key )
{
  bool ret = false;
  auto itr = mChildren.begin();
  for( ; itr != mChildren.end(); ++itr )
  {
    auto child = (*itr);
    ret = child->onKeypress(key);
    if(ret) { break; }
  }
  
  return ret;
}

void Window::addChild( std::shared_ptr<Window> child )
{
  mChildren.push_back(child);
}

int Window::getNumChildren() const
{
  return static_cast<int>(mChildren.size());
}

std::shared_ptr<Window> Window::getChildAtIndex( int idx )
{
  return mChildren.at(idx);
}

void Window::removeChildAtIndex( int idx )
{
  mChildren.erase( std::remove( std::begin(mChildren), std::end(mChildren), mChildren[idx] ), std::end(mChildren) );
}