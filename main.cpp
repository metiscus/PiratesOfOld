#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL.h>
//#include <SDL_ttf.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "ui/Button.hpp"
#include "ui/Screen.hpp"
//test
#include "ui/ScreenData.hpp"

int main(int argc, char ** argv) 
{
  SDL_Init(SDL_INIT_EVERYTHING);
  //TTF_Init();
  // create the lua state
  lua_State *lua = luaL_newstate();
  
  Screen gameScreen(1024, 800, "PiratesOfOld");
  std::shared_ptr<Button> button (new Button(0, 0, 200, 100, "Hello World"));
  gameScreen.setRoot(button);

  float radius = 100;
  float theta = 0;

  SDL_GL_SetSwapInterval(1);
  
  uint64_t lastTick = SDL_GetTicks();
  while (!SDL_QuitRequested()) {
    uint64_t thisTick = SDL_GetTicks();
    gameScreen.onDraw( 1.e-3 * (thisTick - lastTick) );
    lastTick = thisTick;

    //button->setPosition(radius*cos(theta), radius*sin(theta));
    //theta += 0.008;
    //SDL_Delay(15);
  }

  SDL_Quit();

  return 0;
}
