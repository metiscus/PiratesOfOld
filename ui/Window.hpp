#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <memory>
#include <vector>

//tolua_begin
class ScreenData;
class WindowData;

class WindowBase
{
public:
  //tolua_end 
  virtual ~WindowBase() = default;
  //tolua_begin  
  virtual void onDraw( float dt, std::shared_ptr<ScreenData> data ) = 0;
  virtual bool onClick( int x, int y, int button ) = 0;
  virtual bool onMouseMove( int x, int y ) = 0;
  virtual bool onKeypress( int key ) = 0;
};

class Window : public WindowBase
{
public:
  Window(int x, int y, int w, int h);
  
  void setPosition(int x, int y);
  void setSize(int w, int h);
  
  int getWidth() const;
  int getHeight() const;
  int getPosX() const;
  int getPosY() const;
  
  bool contains(int x, int y) const;

  virtual void onDraw( float dt, std::shared_ptr<ScreenData> data );
  virtual bool onClick( int x, int y, int button );
  virtual bool onMouseMove( int x, int y );
  virtual bool onKeypress( int key );
  
  void addChild( std::shared_ptr<Window> child );
  int getNumChildren() const;
  std::shared_ptr<Window> getChildAtIndex( int idx );
  void removeChildAtIndex( int idx );

  //tolua_end  
protected:
  int mPosX, mPosY;
  int mWidth, mHeight;
  std::shared_ptr<WindowData> mData;
  std::vector< std::shared_ptr<Window> > mChildren;
};//tolua_export

#endif 