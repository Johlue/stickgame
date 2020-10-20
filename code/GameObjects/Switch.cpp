#include "Switch.h"

Switch::Switch(){}
Switch::Switch(int o_x, int o_y, Display display, std::vector<GameObject*>* obj, bool once , int reactivTime)
{
  x = o_x;
  y = o_y;
  mDisplay = display;
  objects = obj;
  onlyOnce = once;
  reactivationTime = reactivTime;
}
Switch::~Switch(){}

void Switch::handleEvent(SDL_event* e){}

void Switch::update()
{
    if(reactivationTimeRemaining > 0)
    {
      reactivationTimeRemaining--;
      if(reactivationTimeRemaining == 0)
      {
        activate(true);
      }
    }
}

bool Switch::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 7)
  {
    return true;
  }
  return false;
}

void Switch::activate(bool reactivate)
{
  // do switchy things
  if(reactivationTime > 0 && !reactivate)
  {
    reactivationTimeRemaining = reactivationTime;
  }
}
