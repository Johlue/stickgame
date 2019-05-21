#ifndef HAZARD_21052019
#define HAZARD_21052019

#include "GameObject.h"


enum HazardTypes
{
  SPIKE = 0
};
enum HazardDirection
{
  UP = 0,
  DOWN = 1,
  RIGHT = 2,
  LEFT = 3
};
// a dangerous object, deals damage or maybe some status effects if I ever figure those out
// spike and lazer wallz and whatnot
class Hazard : public GameObject
{
public:
  Hazard();
  // x location, y location, width, heigth, pointer to display
  Hazard(int xl, int yl, int w, int h, int hazardtype, int direction, Display* display);
  ~Hazard();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual void render();

  // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  int hazardType;
  int damage;
  int knockback;
  int direction;
};

#endif
