#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

//! \brief Interface to be implemented by classes that want to know about OS window events
class EventListener
{
public:
  EventListener() = default;
  virtual ~EventListener() = default;
  
  //! \brief Called when the mouse has moved
  //! \param x - Position of the mouse in pixels
  //! \param y - Position of the mouse in pixels
  //! \return true if the message was processed
  virtual bool OnMouseMove(int x, int y);
  
  //! \brief Called when the mouse has had a button pressed
  //! \param button - index of the button
  //! \return true if the message was processed  
  virtual bool OnMouseButtonDown(int button);
  
  //! \brief Called when the mouse has had a button released
  //! \param button - index of the button
  //! \return true if the message was processed 
  virtual bool OnMouseButtonUp(int button);
  
  //! \brief Called when the keyboard has had a key pressed
  //! \param key - index of the key
  //! \return true if the message was processed 
  virtual bool OnKeyDown(int key);
  
  //! \brief Called when the keyboard has had a key released
  //! \param key - index of the key
  //! \return true if the message was processed 
  virtual bool OnKeyUp(int key);
  
private:
  EventListener(const EventListener&) = delete;
  const EventListener& operator=(const EventListener&) = delete;
};

#endif