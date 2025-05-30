#ifndef BOUNDARY_10052019
#define BOUNDARY_10052019

#include "GameObject.h"
#include <iostream>

enum collisionReturns {BOUNDARY_COLLISION, BOUNDARY_DISTANCE_LONG, BOUNDARY_NON_DIRECTIONAL, BOUNDARY_GO_THROUGH, BOUNDARY_X, BOUNDARY_Y};

// this is a wall/ceiling/floor to ram into
class Boundary : public GameObject
{
public:
  Boundary();
  // up and down should not be true at the same time, as well as right and left
  Boundary(double x_1, double y_1, double x_2, double y_2, Display* display, bool up, bool down, bool right, bool left);
  ~Boundary();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  bool getUp();
  bool getDown();
  bool getRight();
  bool getLeft();

  double getX2();
  double getY2();

  void setGoThrough(bool gt);
  bool getGoThrough();

  int collisionCheck(double ox1, double oy1, double ox2, double oy2, int checktype);
  //last 4 values are irrelevant since they are not used, first 4 are two points of the other line being checked
  CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
  int activateThisObject(bool on);
protected:
  double x2;
  double y2;
  bool sloped = false;
  bool facingUp;
  bool facingDown;
  bool facingRight;
  bool facingLeft;
  double speed = 1;
  bool goThrough = false; // it's intangible and doesn't interfere with things
};

#endif
