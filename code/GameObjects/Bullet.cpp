#include "Bullet.h"

Bullet::Bullet(){type = BULLET;}
Bullet::Bullet(int xl, int yl, int w, int h, Display* display){type = BULLET;}
Bullet::~Bullet(){}

void Bullet::handleEvent(SDL_Event* e){}
void Bullet::update(){}
void Bullet::render(int cameraX, int cameraY)
{
  // black sphere maybe with white inside
}

CollisionData Bullet::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
