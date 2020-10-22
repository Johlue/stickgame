#include "Switch.h"

Switch::Switch(){}
Switch::Switch(double o_x, double o_y, Display* display, std::vector<GameObject*>* obj, int switch_Type, bool once , int reactivTime)
{
  x = o_x;
  y = o_y;
  mDisplay = display;
  objects = obj;
  onlyOnce = once;
  reactivationTime = reactivTime;
  switchType = switch_Type;
  switch(switchType)
  {
    case SWITCH_WALL:
    width = 16;
    height = 16;
    break;

    case SWITCH_FLOOR:
    break;
  }
}
Switch::~Switch(){}

void Switch::handleEvent(SDL_Event* e){}

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
    switch(switchType)
    {
      case SWITCH_WALL:
      {
        SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
        SDL_RenderDrawLine(mDisplay->getRenderer(),
          x - cameraX, y - cameraY, x + width - cameraX, y - cameraY);
        SDL_RenderDrawLine(mDisplay->getRenderer(),
          x - cameraX, y - cameraY, x - cameraX, y + height - cameraY);
        SDL_RenderDrawLine(mDisplay->getRenderer(),
          x + width - cameraX, y - cameraY, x + width - cameraX, y + height - cameraY);
        SDL_RenderDrawLine(mDisplay->getRenderer(),
          x - cameraX, y + height - cameraY, x + width - cameraX, y + height - cameraY);

        if(onlyOnce && activated){SDL_SetRenderDrawColor(mDisplay->getRenderer(), 100, 100, 100, 0xFF);}
        if(activated) {SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 255, 0, 0xFF);}
        else {SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);}
        SDL_Rect rect = { x + 1 - cameraX, y + 1 - cameraY, width - 1, height - 1};
        SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
      }
      break;

      case SWITCH_FLOOR:
      {

      }
      break;
    }
    return true;
  }
  return false;
}

void Switch::activate(bool reactivate)
{
  if(onlyOnce && activated){return;}
  if(reactivate)
  {
    activated = false;
    return;
  }
  if(reactivationTime > 0 && !reactivate)
  {
    reactivationTimeRemaining = reactivationTime;
    activated = true;
  }
}

void Switch::activateObjects(bool on)
{
  for(int i = 0; i < activatableObjects.size(); i++)
  {
    
  }
}

void Switch::addActivatable(int o_id)
{
  for(int i = 0; i < activatableObjects.size(); i++)
  {
    if(activatableObjects[i] == o_id)
    {
      return;
    }
  }
  activatableObjects.push_back(o_id);
}
