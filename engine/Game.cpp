#include <SDL.h>

#include "Game.hpp"
#include "LuaEnvironment.hpp"
#include "Renderer.hpp"
#include "ResourceLoader.hpp"
#include "Window.hpp"

// hax
#include <unistd.h>

void Game::StartGame()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetSwapInterval(1);
  
  mGameWindow.reset(new Window(1024, 768, "PiratesOfOld"));
  mRenderer.reset(new Renderer(mGameWindow));
  mLuaEnvironment.reset(new LuaEnvironment());
  mResourceLoader.reset(new ResourceLoader());
  mResourceLoader->SetDataPath("data");
  
  // load the main game script
  std::string mainScript = mResourceLoader->LoadFileAsString("scripts/main.lua");
  mLuaEnvironment->LoadScript(mainScript);
  
  bool isRunning = true;
  
  while(isRunning)
  {
    mLuaEnvironment->Call("OnInput");
    mLuaEnvironment->Call("OnPreFrame");
    mLuaEnvironment->Call("OnFrame");
    mLuaEnvironment->Call("OnPostFrame");
    
    mGameWindow->Swap();
    usleep(10000);
  }
}