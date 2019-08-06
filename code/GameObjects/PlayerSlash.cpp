#include "PlayerSlash.h"

PlayerSlash::PlayerSlash()
{
  type = PLAYERATTACK;
}
PlayerSlash::PlayerSlash(int o_rx, int o_ry, int o_width, int o_height, std::vector<GameObject*>* objs, Display* display)
{
  mDisplay = display;
  rx = o_rx;
  ry = o_ry;
  width = o_width;
  height = o_height;
  objects = objs;
}
PlayerSlash::~PlayerSlash(){}

void PlayerSlash::handleEvent(SDL_Event* e){}
void PlayerSlash::update()
{
  if(lifetime > 0)
  {
    lifetime--;
  } else alive = false;

  // check if playrid is valid, if not fix it
  if(playerid > objects->size() - 1) playerid = 9999999;
  else if((*objects)[playerid]->getType() != PLAYER) playerid = 9999999;

  if(playerid == 9999999)
  {
    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == PLAYER)
      {
        playerid = i;
        break;
      }
    }
  }
  // set location to players (assuming playerid is valid)
  if(playerid != 9999999)
  {
    x = (*objects)[playerid]->getX() + rx;
    y = (*objects)[playerid]->getY() + ry;
  }

  for(int i = 0; i < objects->size(); i++)
  {
    //slay all bullets that enter your threatened area
    if((*objects)[i]->getType() == BULLET)
    {
      GameObject* tempPtr = (*objects)[i];
      if(tempPtr->getX() >= x && tempPtr->getX() <= x + width && tempPtr->getY() >= y && tempPtr->getY() <= y + height)
      {tempPtr->kill();}
    }
  }
}
void PlayerSlash::render(int cameraX, int cameraY)
{
  // temp code to actually be able to see the attack
    SDL_Rect rect = { x - cameraX, y - cameraY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
}

bool PlayerSlash::isOnScreen()
{
  return onScreen;
}

int PlayerSlash::getType()
{
  return type;
}

bool PlayerSlash::isAlive(){return alive;}

CollisionData PlayerSlash::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}

double PlayerSlash::getX(){return x;}
double PlayerSlash::getY(){return y;}
