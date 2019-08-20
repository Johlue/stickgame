#include "func.h"

void rotatePoint(double angle, Point * origin, Point center)
{
  angle = (angle ) * (3.14159265359/180); // Convert to radians

  double centerX = center.x;
  double centerY = center.y;

  double rotatedX = (cos(angle) * (origin->x - centerX)) - (sin(angle) * (origin->y - centerY)) + centerX;

  double rotatedY = (sin(angle) * (origin->x - centerX)) + (cos(angle) * (origin->y - centerY)) + centerY;

  origin->x = rotatedX;
  origin->y = rotatedY;

}

void drawCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius)
{
   const double diameter = (radius * 2);

   double x = (radius - 1);
   double y = 0;
   double tx = 1;
   double ty = 1;
   double error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

double pi(){return 3.14159265359;}

bool closeEnough(double a, double b)
{
  if(a < b + 0.05 && a > b -0.05) return true;
  return false;
}

void splitString(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> splitString(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splitString(s, delim, elems);
    return elems;
}

double pythagoras(double a, double b)
{
  pow(a, 2.0); pow(b, 2.0);
  return sqrt(a + b);
}
