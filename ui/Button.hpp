#ifndef BUTTON_HPP_
#define BUTTON_HPP_

//tolua_begin
#include "Window.hpp"

#include <string>
#include <memory>

class Button : public Window
{
public:
  Button(int x, int y, int width, int height, const std::string& text);
  virtual void onDraw(float dt, std::shared_ptr<ScreenData> data);
  virtual bool onClick(int x, int y, int button);
  
  bool getIsPressed() const;
//tolua_end  
private:
  std::string mText;
  bool mIsPressed;
};//tolua_export

#endif