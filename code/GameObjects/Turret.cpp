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

void Turret::handleEvent(SDL_Event* e){}
void Turret::update()
{
  Point p;
  p.x = x; p.y = y;
  rotatePoint(1, &cannonTopLeft, p);
  rotatePoint(1, &cannonTopRight, p);
  rotatePoint(1, &cannonBottomLeft, p);
  rotatePoint(1, &cannonBottomRight, p);
  angle += 1;
  while(angle > 360){angle -= 360;}
  while (angle < 0){angle += 360;}
  cooldown -= 1;
  if(cooldown < 1) //TODO: spinning to face the player and then not shooting at nothing all the time
  {
    cooldown = shotFrequency;
    //shoot
    Vector2D bulletVector((angle ) * (3.14159265359/180), 5);
    objects->push_back(new Bullet(200, 200, bulletVector, mDisplay, objects));
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
