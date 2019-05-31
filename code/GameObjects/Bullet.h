#ifndef BULLET_31052019
#define BULLET_31052019

#include "GameObject.h"

class Bullet : public GameObject
{
public:
  Bullet();
  // x location, y location, width, heigth, pointer to display
  Bullet(int xl, int yl, int w, int h, Display* display);
  ~Bullet();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual void render(int cameraX, int cameraY);

  // also other collision is handled by it
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  double xVel;
  double yVel;
};

#endif
