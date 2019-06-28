#include "Boundary.h"
#include <cmath>

Boundary::Boundary(){}
Boundary::Boundary(double x_1, double y_1, double x_2, double y_2, Display* display, bool up, bool down, bool right, bool left)
{
  mDisplay = display;
  x = x_1;
  y = y_1;
  x2 = x_2;
  y2 = y_2;
  facingUp = up;
  facingDown = down;
  facingRight = right;
  facingLeft = left;
  type = BOUNDARY;
  if(((x*x)/x) - ((x2*x2)/x2) != 0 && ((y*y)/y) - ((y2*y2)/y2) != 0) sloped = true;
}
Boundary::~Boundary(){}

void Boundary::update(){}
void Boundary::handleEvent(SDL_Event* e){}
void Boundary::render(int cameraX, int cameraY)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x - cameraX, y - cameraY, x2 - cameraX, y2 - cameraY);
}

bool Boundary::getUp(){return facingUp;}
bool Boundary::getDown(){return facingDown;}
bool Boundary::getRight(){return facingRight;}
bool Boundary::getLeft(){return facingLeft;}

// xn and ny values can be whatever since they aren't used at all
CollisionData Boundary::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
{

  double x3 = x;
  double y3 = y;
  double x4 = x2;
  double y4 = y2;

  double xr = -9999;
  double yr = -9999;

// first attempt infinite lines, didn't work in reverse
// amazingly the fucking code can't do math order properly and you need to add a fuckload of brackets to make it not be stupid
  double divider = ((ox1-ox2)*(y3-y4))-((oy1-oy2)*(x3-x4));
  if(divider != 0)
  {
    xr = ( ((ox1*oy2)-(oy1*ox2)) * (x3-x4) -( (ox1-ox2) * ((x3*y4) - (y3*x4)) ) )/divider;
    yr = ( ((ox1*oy2)-(oy1*ox2)) * (y3-y4) -( (oy1-oy2) * ((x3*y4) - (y3*x4)) ) )/divider;
  }

  CollisionData result{xr, yr};
/**
  double pow1 = pow((ox1 - ox2), 2.0);
  double pow2 = pow((oy1 - oy2), 2.0);
  double originDistance = sqrt(pow1 + pow2);

  pow1 = pow((ox1 - xr), 2.0);
  pow2 = pow((oy1 - yr), 2.0);
  double intersectionDistance = sqrt(pow1 + pow2);
*/
  if(
    // intersection point is inside the origin line
    (((ox1 >= xr && ox2 <= xr) || (ox2 >= xr && ox1 <= xr) || (closeEnough(ox1, xr) && closeEnough(ox2, xr))) &&
    ((oy1 >= yr && oy2 <= yr) || (oy2 >= yr && oy1 <= yr) || (closeEnough(oy1, yr) && closeEnough(oy2, yr))))
    &&
    // intersection point is inside boundary object TODO;
    (((x >= xr && x2 <= xr) || (x2 >= xr && x <= xr) || (closeEnough(x, xr) && closeEnough(x2, xr))) &&
    ((y >= yr && y2 <= yr) || (y2 >= yr && y <= yr) || (closeEnough(y, yr) && closeEnough(y2, yr))))
    ) result.intersect = true;
  //if(originDistance > intersectionDistance) result.intersect = true;
  else result.intersect = false;
  result.up = facingUp;
  result.down = facingDown;
  result.right = facingRight;
  result.left = facingLeft;
  result.slope = sloped;

  return result;
}
