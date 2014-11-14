#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <GL/glew.h>
#include <SDL.h>
#include <string>
#include <memory>

class EventManager;

class Window
{
public:
  Window(int w, int h, std::string title);
  ~Window();
  
  uint32_t GetWidth() const;
  uint32_t GetHeight() const;
  
  void Swap();
  void MakeCurrent();
  void PumpEvents();
  
private:
  const Window& operator=(const Window& rhs) = delete;
  Window(const Window& rhs) = delete;
  
  SDL_Window *mWindow;
  SDL_GLContext *mContext;
  
  int mWidth;
  int mHeight;
  
  std::shared_ptr<EventManager> mEventManager;
};

#endif 