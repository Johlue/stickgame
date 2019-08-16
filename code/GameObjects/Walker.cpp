#include "Walker.h"

Walker::Walker(){}
Walker::Walker(int o_x, int o_y, Display* disp)
{
  x = o_x; y = o_y;
  mDisplay = disp;
}
Walker::~Walker(){}

void Walker::handleEvent(SDL_Event* e){}
void Walker::update(){}
void Walker::render(int cameraX, int cameraY)
{
  SDL_Rect rect2 = { x - cameraX, y - cameraY, 20, 20};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
}
