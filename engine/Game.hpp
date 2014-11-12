#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>

class GameConfig;
class LuaEnvironment;
class EventManager;

class Game
{
public:
  void StartGame();
  
private:
  std::shared_ptr<GameConfig>     mGameConfig;
  std::shared_ptr<LuaEnvironment> mLuaEnvironment;
  std::shared_ptr<EventManager>   mEventManager;
};

#endif 