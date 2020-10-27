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
}
Boundary::~Boundary(){}

void Boundary::update(){}
void Boundary::handleEvent(SDL_Event* e){}
bool Boundary::render(int cameraX, int cameraY, int priority)
{
  //int i = 3 - priority;
  if(priority >= 3)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), (0), (0), (0), SDL_ALPHA_OPAQUE);
    if(goThrough) SDL_SetRenderDrawColor(mDisplay->getRenderer(), (200), (200), (200), SDL_ALPHA_OPAQUE);
    //if(facingUp)
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - cameraX, y - cameraY, x2 - cameraX, y2 - cameraY);
    //else if(facingDown)
    //  SDL_RenderDrawLine(mDisplay->getRenderer(), x - cameraX, y-i - cameraY, x2 - cameraX, y2-i - cameraY);
    //else if(facingRight)
    //  SDL_RenderDrawLine(mDisplay->getRenderer(), x-i - cameraX, y - cameraY, x2-i - cameraX, y2 - cameraY);
    //else if(facingLeft)
    //  SDL_RenderDrawLine(mDisplay->getRenderer(), x+i - cameraX, y - cameraY, x2+i - cameraX, y2 - cameraY);
    //if(priority >= 3) return true;
    return true;
  }
  return false;
}

double Boundary::getX2(){return x2;}
double Boundary::getY2(){return y2;}
bool Boundary::getUp(){return facingUp;}
bool Boundary::getDown(){return facingDown;}
bool Boundary::getRight(){return facingRight;}
bool Boundary::getLeft(){return facingLeft;}
void Boundary::setGoThrough(bool gt){goThrough = gt;}
bool Boundary::getGoThrough(){return goThrough;}

int Boundary::activateThisObject(bool on)
{
  if(on != activated)
  {
    activated = !activated;
    goThrough = !goThrough;
  }
}

int Boundary::collisionCheck(double ox1, double oy1, double ox2, double oy2, int checkType)
{
  if(goThrough) {return BOUNDARY_GO_THROUGH;}

  if((!facingUp && !facingDown && !facingLeft && !facingRight)){return BOUNDARY_NON_DIRECTIONAL;}

  if(!facingUp && !facingDown && checkType == BOUNDARY_Y)
    {return BOUNDARY_DISTANCE_LONG;}
  if(facingUp || facingDown){
    if(checkType == BOUNDARY_Y && (oy1 < y && oy1 < y2 && oy2 < y && oy2 < y2)
                               || (oy1 > y && oy1 > y2 && oy2 > y && oy2 > y2))
    {return BOUNDARY_DISTANCE_LONG;}}

  if(!facingRight && !facingLeft && checkType == BOUNDARY_X)
    {return BOUNDARY_DISTANCE_LONG;}
  if(facingRight || facingLeft){
    if(checkType == BOUNDARY_X && (ox1 > x && ox1 > x2 && ox2 > x && ox2 > x2)
                               || (ox1 < x && ox1 < x2 && ox2 < x && ox2 < x2))
    {return BOUNDARY_DISTANCE_LONG;}}


  return BOUNDARY_COLLISION;
}

// xn and ny values can be whatever since they aren't used at all
CollisionData Boundary::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
{

  double xr = -9999;
  double yr = -9999;

  CollisionData result{xr, yr};
  result.intersect = false;

  if((!facingUp && !facingDown && !facingLeft && !facingRight) || goThrough)
  {
    return result;
  }

  if((oy1 < y && oy1 < y2 && oy2 < y && oy2 < y2) || (oy1 > y && oy1 > y2 && oy2 > y && oy2 > y2)
  || (ox1 > x && ox1 > x2 && ox2 > x && ox2 > x2) || (ox1 < x && ox1 < x2 && ox2 < x && ox2 < x2))
  {return result;}

  double x3 = x;
  double y3 = y;
  double x4 = x2;
  double y4 = y2;


// first attempt infinite lines, didn't work in reverse
// amazingly the fucking code can't do math order properly and you need to add a fuckload of brackets to make it not be stupid
  double divider = ((ox1-ox2)*(y3-y4))-((oy1-oy2)*(x3-x4));
  if(divider != 0)
  {
    xr = ( ((ox1*oy2)-(oy1*ox2)) * (x3-x4) -( (ox1-ox2) * ((x3*y4) - (y3*x4)) ) )/divider;
    yr = ( ((ox1*oy2)-(oy1*ox2)) * (y3-y4) -( (oy1-oy2) * ((x3*y4) - (y3*x4)) ) )/divider;
  }

  result.x = xr;
  result.y = yr;

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
