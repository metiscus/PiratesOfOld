#include <SDL.h>
#include <GL/gl.h>

#include "ui/Screen.hpp"

int main(int argc, char ** argv) 
{
  SDL_Init(SDL_INIT_EVERYTHING);
 
  Screen gameScreen(800, 600, "PiratesOfOld");
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
