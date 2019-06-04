#include "Bullet.h"

Bullet::Bullet(){type = BULLET;}
Bullet::Bullet(int xl, int yl, Vector2D move, Display* display, std::vector<GameObject*>* obj)
{
  type = BULLET;
  x = xl;
  y = yl;
  movement = move;
  mDisplay = display;
  objects = obj;
}
Bullet::~Bullet(){}

void Bullet::handleEvent(SDL_Event* e){}
void Bullet::update()
{
  x += movement.x;
  y += movement.y;
  lifeTime -= 1;
  if(lifeTime < 1) alive = false;
}
void Bullet::render(int cameraX, int cameraY)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, 3);
  // black sphere maybe with white inside
}

CollisionData Bullet::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
