#ifndef SCREEN_HPP_
#define SCREEN_HPP_

class Window;

#include <string>
#include <map>
#include <memory>

//tolua_begin
class ScreenData;

class Screen
{
public:
  Screen(int width, int height, std::string title);
//tolua_end
  Screen(const Screen& rhs) = delete;
  const Screen& operator=(const Screen&) = delete;
//tolua_begin  
  int getWidth() const;
  int getHeight() const;
  
  void setRoot(std::shared_ptr<Window> window);
  std::shared_ptr<Window> getRoot();

  void onDraw(float dt);
  void onClick(int x, int y, int button);
  void onKeypress(int key);

  //std::shared_ptr<ScreenData> _getData() { return mData; }
//tolua_end
private:
  int mWidth;
  int mHeight;
  std::string mTitle;
  std::shared_ptr<Window> mRoot;
  std::shared_ptr<ScreenData> mData;
};//tolua_export

#endif