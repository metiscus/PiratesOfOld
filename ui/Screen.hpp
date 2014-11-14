#ifndef SCREEN_HPP_
#define SCREEN_HPP_

class Window;

#include <string>
#include <map>
#include <memory>

class ScreenData;

class Screen
{
public:
  Screen();
  Screen(const Screen& rhs) = delete;
  const Screen& operator=(const Screen&) = delete;

  void onDraw(float dt);
  void onClick(int x, int y, int button);
  void onKeypress(int key);

private:
  
};

#endif