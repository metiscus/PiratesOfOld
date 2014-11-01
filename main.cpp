#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/gl.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "ui/Button.hpp"
#include "ui/Screen.hpp"

int main(int argc, char ** argv) 
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  // create the lua state
  lua_State *lua = luaL_newstate();
  
  Screen gameScreen(800, 600, "PiratesOfOld");
  std::shared_ptr<Button> button (new Button(200, 200, 100, 100, "Hello World!"));
  gameScreen.setRoot(button);
  
  
  uint64_t lastTick = SDL_GetTicks();
  while (!SDL_QuitRequested()) {
    uint64_t thisTick = SDL_GetTicks();
    gameScreen.onDraw( 1.e-3 * (thisTick - lastTick) );
    lastTick = thisTick;
    SDL_Delay(15);
  }

  SDL_Quit();

  return 0;
}
