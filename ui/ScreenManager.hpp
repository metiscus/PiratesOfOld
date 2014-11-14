#ifndef SCREENMANAGER_HPP_
#define SCREENMANAGER_HPP_

#include <memory>
#include <vector>

class ScreenManager
{
public:
  
  
private:
  std::vector< std::shared_ptr<Screen> > mScreenList;
  std::shared_ptr<Window> mWindow;
};

#endif