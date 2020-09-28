#include "Slash.h"

Slash::Slash()
{
  type = PLAYERATTACK;
}
Slash::Slash(double * o_x, double * o_y, int o_rx, int o_ry, int o_width, int o_height, int o_direction, bool playerSlash, std::vector<GameObject*>* objs, Display* display, int mvtype, int duration, int dmg, int invfrm, double kb)
{
  mDisplay = display;
  direction = o_direction;
  ox = o_x;
  oy = o_y;
  rx = o_rx;
  ry = o_ry;
  width = o_width;
  height = o_height;
  objects = objs;
  playerOwned = playerSlash;
  lifetime = duration;
  damage = dmg;
  iframes = invfrm;
  moveType = mvtype;
  knockback = kb;
  flailspeed = flailspeed * direction;
}
Slash::~Slash(){}

void Slash::handleEvent(SDL_Event* e){}
void Slash::update()
{
  if(moveType == S_FLAIL)
  {
    if(flailreversal)
    {
      rx += flailspeed;
      flailspeed += .1 * direction;
    }
    else
    {
      rx += flailspeed;
      flailspeed -= .1 * direction;
    }
    if(closeEnough(flailspeed, 0))
    {
      if(flailreversal)   {lifetime = 0;}
      flailspeed = -8 * direction;
      flailreversal = true;
    }
  }
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
    x = *ox + rx;
    y = *oy + ry;
  }

  for(int i = 0; i < objects->size(); i++)
  {
    // if its the players slash, then do damage to enemies
    CollisionData cd;
    cd.damage = damage;
    cd.iframes = iframes;
    cd.knockback = knockback;
    if(direction == 1) {cd.knockback = -knockback;}
    if(flailreversal) {cd.knockback = -cd.knockback;}

    if(!damageDealt) // can only deal damage once during it's lifecycle (but it is possible to multihit)
    {
      if(playerOwned == true)
      {
        if((*objects)[i]->getType() == WALKER)
        {
          Walker * bptr;
          bptr = dynamic_cast<Walker*>((*objects)[i]);
          // if the hitboxes don't not overlap then do the thing
          if(!(bptr->getX() > x + width || x > bptr->getX() + bptr->getWidth())
          && !(bptr->getY() > y + height || y > bptr->getY() + bptr->getHeight()))
          {
            bptr->damaged(cd);
            damageDealt = true;
          }
        }
        if((*objects)[i]->getType() == TURRET)
        {
          Turret * bptr;
          bptr = dynamic_cast<Turret*>((*objects)[i]);
          if(!(bptr->getX() - bptr->getRadius() > x + width || x > bptr->getX() + bptr->getRadius())
          && !(bptr->getY() - bptr->getRadius() > y + height || y > bptr->getY() + bptr->getRadius()))
          {
            bptr->damaged(cd);
            damageDealt = true;
          }
        }
      }
      // if its not the players then damage the player
      if(playerOwned == false && (*objects)[i]->getType() == PLAYER)
      {
        Player * bptr;
        bptr = dynamic_cast<Player*>((*objects)[i]);
        if(!(bptr->getX() > x + width || x > bptr->getX() + bptr->getWidth())
        && !(bptr->getY() > y + height || y > bptr->getY() + bptr->getHeight()))
        {
          bptr->damaged(cd);
          damageDealt = true;
        }
      }
    }
    //slay all bullets that enter your threatened area
    if((*objects)[i]->getType() == BULLET)
    {
      GameObject* tempPtr = (*objects)[i];
      if(tempPtr->getX() >= x && tempPtr->getX() <= x + width && tempPtr->getY() >= y && tempPtr->getY() <= y + height)
      {tempPtr->kill();}
    }
  }
}
bool Slash::render(int cameraX, int cameraY, int priority)
{
  // temp code to actually be able to see the attack
    SDL_Rect rect = { x - cameraX, y - cameraY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
    return true;
}

bool Slash::isOnScreen()
{
  return onScreen;
}

int Slash::getType()
{
  return type;
}

bool Slash::isAlive(){return alive;}

CollisionData Slash::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}

double Slash::getX(){return x;}
double Slash::getY(){return y;}
