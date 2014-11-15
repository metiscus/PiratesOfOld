#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <GL/glew.h>
#include <SDL.h>
#include <string>
#include <memory>
#include <mutex>

class EventManager;

//! \brief Encapsulates the functionality of a window in the windowing system
class Window
{
public:
  /**
   * \brief Create a new window in the local windowing system
   * \param width - Width of window
   * \param height - Height of window
   * \param title - Title of window
   */
  Window(int width, int height, std::string title);
  ~Window();
  
  //! \brief Get the width of the window in pixels
  uint32_t GetWidth() const;
  
  //! \brief Get the height of the window in pixels
  uint32_t GetHeight() const;
  
  //! \brief Perform the OS specific swap of the front and rear buffers
  void SwapBuffers();
  
  //! \brief Make the current window the active window for draw operations
  void MakeCurrent();
  
  //! \brief Poll the event queue for this window and process all waiting messages
  //! Waiting messages are parsed and handled by the EventManager
  void PumpEvents();
  
  //! \brief Get the EventManager associated with this Window
  std::shared_ptr<EventManager> GetEventManager();
  
private:
  const Window& operator=(const Window& rhs) = delete;
  Window(const Window& rhs) = delete;
  
  SDL_Window *mWindow;
  SDL_GLContext *mContext;
  
  int mWidth;
  int mHeight;
  
  std::shared_ptr<EventManager> mEventManager;
  
  static std::once_flag sWindowSystemInit;
};

#endif 