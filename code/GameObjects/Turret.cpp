#include "Turret.h"

Turret::Turret(){type = TURRET;}
Turret::Turret(int xl, int yl, Display* display, std::vector<GameObject*>* obj)
{
  objects = obj;
  type = TURRET;
  x = xl;
  y = yl;

  cooldown = shotFrequency;

  cannonTopLeft.x = x - 4;
  cannonTopLeft.y = y - 20;
  cannonTopRight.x = x + 4;
  cannonTopRight.y = y - 20;
  cannonBottomLeft.x = x - 4;
  cannonBottomLeft.y = y - 9;
  cannonBottomRight.x = x + 4;
  cannonBottomRight.y = y - 9;

  mDisplay = display;
}
Turret::~Turret(){}

void Turret::move(double xo, double yo)
{
  x += xo;
  y += yo;
  cannonTopLeft.x += xo;
  cannonTopLeft.y += yo;
  cannonTopRight.x += xo;
  cannonTopRight.y += yo;
  cannonBottomLeft.x += xo;
  cannonBottomLeft.y += yo;
  cannonBottomRight.x += xo;
  cannonBottomRight.y += yo;
}

void Turret::rotate(double angl)
{
  Point p;
  p.x = x; p.y = y;
  rotatePoint(angl, &cannonTopLeft, p);
  rotatePoint(angl, &cannonTopRight, p);
  rotatePoint(angl, &cannonBottomLeft, p);
  rotatePoint(angl, &cannonBottomRight, p);
  angle += angl;
  while(angle > 360){angle -= 360;}
  while (angle < 0){angle += 360;}
}

void Turret::handleEvent(SDL_Event* e){}
void Turret::update()
{
  // check if playrid is valid, if not fix it
  if(playerid > objs->size() - 1) playerid = 9999999;
  else if((*objs)[playerid]->getType() != PLAYER) playerid = 9999999;

  if(playerid == 9999999)
  {
    for(int i = 0; i < objs->size(); i++)
    {
      if((*objs)[i]->getType() == PLAYER)
      {
        playerid = i;
        break;
      }
    }
  }
  rotate(2);
  cooldown -= 1;
  if(cooldown < 1) //TODO: spinning to face the player and then not shooting at nothing all the time
  {
    cooldown = shotFrequency;
    //shoot
    Vector2D bulletVector((angle ) * (3.14159265359/180), bulletSpeed);
    objects->push_back(new Bullet(x, y, bulletVector, mDisplay, objects));
  }
}
void Turret::render(int cameraX, int cameraY)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, 10);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonBottomLeft.x - cameraX, cannonBottomLeft.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonBottomRight.x - cameraX, cannonBottomRight.y - cameraY);
  //draw a ball at x, y
  // rotating cannon pipe thing
    //or do the classic: draw 8 lines next to each other version
    // ACTUALLY, I could just use the line rotation thingy from the hazard triangle for this
}

CollisionData Turret::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
