#ifndef FUNC_04062019
#define FUNC_04062019

#include "Display.h"
#include "Point.h"
#include <cmath>

void drawCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius);
void rotatePoint(double angle, Point * origin, Point center); // rotate a point (origin) around a (center) point


#endif
