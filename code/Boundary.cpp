#include "Boundary.h"

Boundary::Boundary(){}
Boundary::Boundary(double x_1, double y_1, double x_2, double y_2, Display* display)
{
  mDisplay = display;
  x = x_1;
  y = y_1;
  x2 = x_2;
  y2 = y_2;
}
Boundary::~Boundary(){}

void Boundary::update(){}
void Boundary::handleEvent(SDL_Event* e){}
void Boundary::render()
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, x2, y2);
}

// xn and ny values can be whatever since they aren't used at all
SDL_Point Boundary::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
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

  SDL_Point result{xr, yr};
  return result;
}
