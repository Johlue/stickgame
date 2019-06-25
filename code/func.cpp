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
