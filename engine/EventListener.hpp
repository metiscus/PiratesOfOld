#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

class EventListener
{
public:
  EventListener() = default;
  virtual ~EventListener() = default;
  
  virtual bool OnMouseMove(int x, int y);
  virtual bool OnMouseButtonDown(int button);
  virtual bool OnMouseButtonUp(int button);
  virtual bool OnKeyDown(int key);
  virtual bool OnKeyUp(int key);
  
private:
  EventListener(const EventListener&) = delete;
  const EventListener& operator=(const EventListener&) = delete;
};

#endif