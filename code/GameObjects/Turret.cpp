#include "Turret.h"

Turret::Turret(){type = TURRET;}
Turret::Turret(int xl, int yl, int w, int h, Display* display)
{
  type = TURRET;
}
Turret::~Turret(){}

void Turret::handleEvent(SDL_Event* e){}
void Turret::update(){}
void Turret::render(int cameraX, int cameraY)
{
  //draw a ball at x, y
  // rotating cannon pipe thing
    //or do the classic: draw 8 lines next to each other version
    // ACTUALLY, I could just use the line rotation thingy from the hazard triangle for this
}

CollisionData Turret::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
