#ifndef BULLET_31052019
#define BULLET_31052019

#include "GameObject.h"
#include "Player.h"
#include "Walker.h"

class Bullet : public GameObject
{
public:
  Bullet();
  // x location, y location, width, heigth, pointer to display
  Bullet(int xl, int yl, Vector2D move, Display* display, std::vector<GameObject*>* obj, bool players, int dmg, double kb);
  ~Bullet();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual bool render(int cameraX, int cameraY, int priority);

  // also other collision is handled by it
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
  int activateThisObject(bool on);
protected:
  bool playerBullet = false;
  int damage = 4, iframes = 45;
  double knockback = 1;
  Vector2D movement;
  int lifeTime = 300;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
};

#endif
