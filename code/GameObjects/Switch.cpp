#include "Switch.h"

Switch::Switch(){}
Switch::Switch(double o_x, double o_y, Display* display, std::vector<GameObject*>* obj, int switch_Type, bool once , int reactivTime, bool activ)
{
  activated = activ;
  type == SWITCH;
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
    width = 32;
    height = 8;
    break;
  }
}
Switch::~Switch(){}

void Switch::handleEvent(SDL_Event* e){}

void Switch::update()
{

  if(onlyOnce && used){return;}

  activatedThisFrame = false;

  if(reactivationTimeRemaining > 0)
  {
    reactivationTimeRemaining--;
    if(reactivationTimeRemaining == 0)
    {
      activate(true);
    }
  }
  if(cooldown > 0)
  {
    cooldown--;
  }
  else
  {
    if(detectCollision())
    {
      activate();
    }
  }
}

bool Switch::detectCollision()
{
  for(int i = 0; i < objects->size(); i++)
  {
    if(switchType == SWITCH_WALL)
    {
      if((*objects)[i]->getType() == BULLET)
      {
        if (!(x + width < (*objects)[i]->getX() || (*objects)[i]->getX() < x
        || y + height < (*objects)[i]->getY() || (*objects)[i]->getY() < y))
        {
          return true;
        }
      }
      else if((*objects)[i]->getType() == PLAYERATTACK)
      {
        if (!(x + width < (*objects)[i]->getX() || (*objects)[i]->getX() + (*objects)[i]->getWidth() < x
        || y + height < (*objects)[i]->getY() || (*objects)[i]->getY() + (*objects)[i]->getHeight() < y))
        {
          return true;
        }
      }
    }
    else if(switchType == SWITCH_FLOOR)
    {
      if((*objects)[i]->getType() == PLAYER || (*objects)[i]->getType() == WALKER)
      {
        double gx = (*objects)[i]->getX();
        double gy = (*objects)[i]->getY();
        double gw = (*objects)[i]->getWidth();
        double gh = (*objects)[i]->getHeight();

        if (!(x + width < gx || x > gx + gw) && !(y + height < gy || y > gy + gh))
        {
          return true;
        }
      }
    }
  }
  return false;
}

bool Switch::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 7)
  {
    if(switchType == SWITCH_FLOOR)
    {
      if(activated){height = 4; y += 4;}
      else{height = 8;}
    }
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
    SDL_RenderDrawLine(mDisplay->getRenderer(),
      x - cameraX, y - cameraY, x + width - cameraX, y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(),
      x - cameraX, y - cameraY, x - cameraX, y + height - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(),
      x + width - cameraX, y - cameraY, x + width - cameraX, y + height - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(),
      x - cameraX, y + height - cameraY, x + width - cameraX, y + height - cameraY);

    if(onlyOnce && used){SDL_SetRenderDrawColor(mDisplay->getRenderer(), 100, 100, 100, 0xFF);}
    else if(activated) {SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 255, 0, 0xFF);}
    else {SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);}
    SDL_Rect rect = { x + 1 - cameraX, y + 1 - cameraY, width - 1, height - 1};
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect);

    if(switchType == SWITCH_FLOOR)
    {
      if(activated){y -= 4;}
      height = 8;
    }

    return true;
  }
  return false;
}

int Switch::activateThisObject(bool on)
{
  activate();
}

void Switch::activate(bool reactivate)
{
  if(activatedThisFrame) {return;}
  activatedThisFrame = true;
  if(onlyOnce && used){return;}
  used = true;
  if(reactivate)
  {
    activated = false;
    activateObjects(activated);
    return;
  }

  cooldown = 60;
  if(reactivationTime > 0 && !reactivate)
  {
    reactivationTimeRemaining = reactivationTime;
    activated = true;
    activateObjects(activated);
  }
  if(reactivationTime <= 0)
  {
    activated = !activated;
    activateObjects(activated);
  }
}

void Switch::activateObjects(bool on)
{
  for(int i = 0; i < activatableObjects.size(); i++)
  {
    for(int i2 = 0; i2 < objects->size(); i2++)
    {
      if((*objects)[i2]->getId() == activatableObjects[i])
      {
        (*objects)[i2]->activateThisObject(on);
        break;
      }
    }
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
