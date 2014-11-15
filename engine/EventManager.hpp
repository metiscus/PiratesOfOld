#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include <mutex>
#include <memory>
#include <vector>

class EventListener;

//! \brief Encapsulates OS level events and sends them to EventListeners
//! The OnX() functions are to be called by the Window class implementations
//! to abstract EventManager from the details of the underlying Window
class EventManager
{
public: 
  EventManager() = default;
  ~EventManager() = default;
  
  //! \brief Add a listener to be notified of events
  void AddListener(std::shared_ptr<EventListener> listener);
  
  //! \brief Remove a listener from the notification list
  void RemoveListener(std::shared_ptr<EventListener> listener);
  
  void OnMouseMove(int x, int y);
  void OnMouseButtonDown(int button);
  void OnMouseButtonUp(int button);
  void OnKeyDown(int key);
  void OnKeyUp(int key);
  
private:
  std::vector< std::shared_ptr<EventListener> > mListenerList;
  
  EventManager(const EventManager& rhs) = delete;
  const EventManager& operator=(const EventManager& rhs) = delete;
};


#endif 