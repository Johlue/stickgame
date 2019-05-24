#include "Hazard.h"

Hazard::Hazard(){type = HAZARD;}
Hazard::Hazard(int xl, int yl, int w, int h, int haztype, double angle, Display* display)
{
  type = HAZARD;
  hazardType = haztype;
  x = xl;
  y = yl;
  width = w;
  height = h;
  mDisplay = display;

  topPoint.x = x + (width/2);
  topPoint.y = y;

  bottomLeftPoint.x = x;
  bottomLeftPoint.y = y + height;

  bottomRightPoint.x = x + width;
  bottomRightPoint.y = y + height;
}
Hazard::~Hazard(){}

void Hazard::handleEvent(SDL_Event* e){}
void Hazard::update()
{}
void Hazard::render()
{
  switch(hazardType)
  {
    // what type of hazard
    case SPIKE:
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mDisplay->getRenderer(), bottomLeftPoint.x, bottomLeftPoint.y, bottomRightPoint.x, bottomRightPoint.y);
    SDL_RenderDrawLine(mDisplay->getRenderer(), bottomLeftPoint.x, bottomLeftPoint.y, topPoint.x, topPoint.y);
    SDL_RenderDrawLine(mDisplay->getRenderer(), topPoint.x, topPoint.y, bottomRightPoint.x, bottomRightPoint.y);
    //do stuff
    break;
  }
}

void Hazard::rotate(double angle)
{
  //rotate the whole spike by rotateing each of it's points
  rotatePoint(angle, &topPoint);
  rotatePoint(angle, &bottomLeftPoint);
  rotatePoint(angle, &bottomRightPoint);
}

void Hazard::rotatePoint(double angle, Point * origin)
{
  angle = (angle ) * (3.14159265359/180); // Convert to radians

  double centerX = x+(width/2);
  double centerY = y + height;
  std::cout <<"CenterPoint: (" << centerX<< ", " << centerY << ")" << std::endl;

  std::cout <<"Origin: (" << origin->x<< ", " << origin->y << ")" << std::endl;
  double rotatedX = (cos(angle) * (origin->x - centerX)) - (sin(angle) * (origin->y - centerY)) + centerX;

  double rotatedY = (sin(angle) * (origin->x - centerX)) + (cos(angle) * (origin->y - centerY)) + centerY;
  std::cout <<"RotatedPoint: (" << rotatedX<< ", " << rotatedY << ")" << std::endl << std::endl;

  origin->x = rotatedX;
  origin->y = rotatedY;

}

CollisionData Hazard::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
