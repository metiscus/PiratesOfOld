#include <SDL.h>

#include "Game.hpp"
#include "ScriptEnvironment.hpp"
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
  mScriptEnvironment.reset(new ScriptEnvironment());
  mResourceLoader.reset(new ResourceLoader());
  mResourceLoader->SetDataPath("data");
  
  // load the main game script
  std::string mainScript = mResourceLoader->LoadFileAsString("scripts/main.lua");
  mScriptEnvironment->LoadScript(mainScript);
  mScriptEnvironment->RegisterClass<Renderer>("Renderer");
  
  bool isRunning = true;
  
  while(isRunning)
  {
    mGameWindow->PumpEvents();
    mScriptEnvironment->Call("void OnInput()");
//    mScriptEnvironment->Call("OnPreFrame");
//    mScriptEnvironment->Call("OnFrame");
//    mScriptEnvironment->Call("OnPostFrame");
    
    mGameWindow->Swap();
    usleep(10000);
  }
}