#include <GL/glew.h>
#include <GL/gl.h>

#include "engine/Game.hpp"

int main(int argc, char ** argv) 
{
  std::unique_ptr<Game> theGame (new Game());
  theGame->StartGame();
  
/*
  uint64_t lastTick = SDL_GetTicks();
  while (!SDL_QuitRequested()) {
    uint64_t thisTick = SDL_GetTicks();
    gameScreen.onDraw( 1.e-3 * (thisTick - lastTick) );
    lastTick = thisTick;
  }

  SDL_Quit();
*/

  return 0;
}
