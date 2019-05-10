#ifndef BOUNDARY_10052019
#define BOUNDARY_10052019

#include "GameObject.h"
#include <iostream>

// this is a wall/ceiling/floor to ram into
class Boundary : public GameObject
{
public:
  Boundary();
  Boundary(double x_1, double y_1, double x_2, double y_2, Display* display);
  ~Boundary();

  void handleEvent(SDL_Event* e);
  void update();
  void render();
  //last 4 values are irrelevant since they are not used, first 4 are two points of the other line being checked
  CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  double x2;
  double y2;
};

#endif
