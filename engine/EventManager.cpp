#include <algorithm>
#include <cassert>
#include <mutex>
#include "EventListener.hpp"
#include "EventManager.hpp"

void EventManager::AddListener(std::shared_ptr<EventListener> listener)
{
  mListenerList.push_back( listener );
}

void EventManager::RemoveListener(std::shared_ptr<EventListener> listener)
{
  mListenerList.erase(std::remove(std::begin(mListenerList), std::end(mListenerList), listener), std::end(mListenerList));
}

void EventManager::OnMouseMove(int x, int y)
{
  for(auto itr=mListenerList.begin(); itr!=mListenerList.end(); ++itr)
  {
    (*itr)->OnMouseMove(x, y);
  }
}

void EventManager::OnMouseButtonDown(int button)
{
  for(auto itr=mListenerList.begin(); itr!=mListenerList.end(); ++itr)
  {
    (*itr)->OnMouseButtonDown(button);
  }
}

void EventManager::OnMouseButtonUp(int button)
{
  for(auto itr=mListenerList.begin(); itr!=mListenerList.end(); ++itr)
  {
    (*itr)->OnMouseButtonUp(button);
  }  
}

void EventManager::OnKeyDown(int key)
{
  for(auto itr=mListenerList.begin(); itr!=mListenerList.end(); ++itr)
  {
    (*itr)->OnKeyDown(key);
  } 
}

void EventManager::OnKeyUp(int key)
{
  for(auto itr=mListenerList.begin(); itr!=mListenerList.end(); ++itr)
  {
    (*itr)->OnKeyUp(key);
  }  
}