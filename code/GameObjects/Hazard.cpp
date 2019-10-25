#include "Hazard.h"

Hazard::Hazard(){type = HAZARD;}
Hazard::Hazard(int xl, int yl, int w, int h, int haztype, double angle, int odamage, Display* display)
{
  type = HAZARD;
  hazardType = haztype;
  x = xl;
  y = yl;
  width = w;
  height = h;
  mDisplay = display;
  damage = odamage;

  topPoint.x = x + (width/2);
  topPoint.y = y;

  bottomLeftPoint.x = x;
  bottomLeftPoint.y = y + height;

  bottomRightPoint.x = x + width;
  bottomRightPoint.y = y + height;
}
Hazard::~Hazard(){}

void Hazard::handleEvent(SDL_Event* e){}
void Hazard::update(){}
void Hazard::render(int cameraX, int cameraY)
{
  switch(hazardType)
  {
    // what type of hazard
    case SPIKE:
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(mDisplay->getRenderer(), bottomLeftPoint.x - cameraX, bottomLeftPoint.y - cameraY, bottomRightPoint.x - cameraX, bottomRightPoint.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), bottomLeftPoint.x - cameraX, bottomLeftPoint.y - cameraY, topPoint.x - cameraX, topPoint.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), topPoint.x - cameraX, topPoint.y - cameraY, bottomRightPoint.x - cameraX, bottomRightPoint.y - cameraY);
    //do stuff
    break;
  }
}

void Hazard::rotate(double angle)
{
  Point center;
  center.x = x+(width/2);
  center.y = y + height;
  //rotate the whole spike by rotateing each of it's points
  rotatePoint(angle, &topPoint, center);
  rotatePoint(angle, &bottomLeftPoint, center);
  rotatePoint(angle, &bottomRightPoint, center);
}

CollisionData Hazard::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
{

  double x3, y3; //first point of this object
  double x4, y4; //second point of this object

  double xr = -9999;
  double yr = -9999;

  CollisionData result{xr, yr};
  result.intersect = false;
  result.damage = damage;
  result.knockback = knockback;
  result.iframes = iframes;

  // first attempt infinite lines, didn't work in reverse
  // amazingly the fucking code can't do math order properly and you need to add a fuckload of brackets to make it not be stupid
  // this is a spike check, probs do other things for different hazards
  for(int i = 0; i < 3; i++)
  {
    // run collision for each of the lines in the triangle
    if(i == 0)
    {
      x3 = bottomLeftPoint.x;
      y3 = bottomLeftPoint.y;
      x4 = topPoint.x;
      y4 = topPoint.y;
    }
    else if(i == 1)
    {
      x3 = bottomRightPoint.x;
      y3 = bottomRightPoint.y;
      x4 = topPoint.x;
      y4 = topPoint.y;
    }
    else if(i == 2)
    {
      x3 = bottomLeftPoint.x;
      y3 = bottomLeftPoint.y;
      x4 = bottomRightPoint.x;
      y4 = bottomRightPoint.y;
    }
    double divider = ((ox1-ox2)*(y3-y4))-((oy1-oy2)*(x3-x4));
    if(divider != 0)
    {
      xr = ( ((ox1*oy2)-(oy1*ox2)) * (x3-x4) -( (ox1-ox2) * ((x3*y4) - (y3*x4)) ) )/divider;
      yr = ( ((ox1*oy2)-(oy1*ox2)) * (y3-y4) -( (oy1-oy2) * ((x3*y4) - (y3*x4)) ) )/divider;
    }

    result.x = xr;
    result.y = yr;

    double pow1 = pow((ox1 - ox2), 2.0);
    double pow2 = pow((oy1 - oy2), 2.0);
    double originDistance = sqrt(pow1 + pow2);

    pow1 = pow((ox1 - xr), 2.0);
    pow2 = pow((oy1 - yr), 2.0);
    double intersectionDistance = sqrt(pow1 + pow2);
    if(
      // intersection point is inside the origin line
      (((ox1 >= xr && ox2 <= xr) || (ox2 >= xr && ox1 <= xr)) && ((oy1 >= yr && oy2 <= yr) || (oy2 >= yr && oy1 <= yr)))
      &&
      // intersection point is inside current triangle line
      //MIGHT BE BROKEN
      (((x3 >= xr && x4 <= xr) || (x4 >= xr && x3 <= xr)) && ((y3 >= yr && y4 <= yr) || (y4 >= yr && y3 <= yr)))
      ) result.intersect = true;
  }
  return result;
}
