#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>

#include "Window.hpp"

class GameConfig;
class LuaEnvironment;
class Renderer;
class ResourceLoader;
class Window;

class Game
{
public:
  void StartGame();
  
private:
  std::shared_ptr<GameConfig>     mGameConfig;
  std::shared_ptr<LuaEnvironment> mLuaEnvironment;
  std::shared_ptr<Window>         mGameWindow;
  std::shared_ptr<Renderer>       mRenderer;
  std::shared_ptr<ResourceLoader> mResourceLoader;
};

#endif 