#ifndef SLASH_06082019
#define SLASH_06082019

#include "GameObject.h"
#include "Walker.h"
#include "Turret.h"
#include "Player.h"
#include <iostream>

// melee attack of the player
class Slash : public GameObject
{
public:
  Slash();
  // rx and ry are relative to player location (x = player x + prx)
  Slash(double * o_x, double * o_y, int rx, int ry, int width, int height, int direction, bool playerSlash,std::vector<GameObject*>* objs, Display* display);
  ~Slash();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  double getX();
  double getY();

  bool isAlive();
  bool isOnScreen();
  int getType();
  // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  bool damageDealt = false; // becomes true upon dealing damage to something, can't deal damage again afterwards
  int rx, ry;
  double * ox; double * oy; // pointers to the owners x and y locations
  int direction = 1;
  int playerid = 9999999;
  bool playerOwned;
  int lifetime = 20;
  int damage = 20;
  int iframes = 40;
  double knockback = 3;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
};

#endif
