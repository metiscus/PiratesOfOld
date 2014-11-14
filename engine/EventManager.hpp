#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include <mutex>
#include <memory>
#include <vector>

class EventListener;

class EventManager
{
public: 
  EventManager() = default;
  ~EventManager() = default;
  
  void AddListener(std::shared_ptr<EventListener> listener);
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