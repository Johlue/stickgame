#ifndef PLAYERSLASH_06082019
#define PLAYERSLASH_06082019

#include "GameObject.h"
#include <iostream>

// melee attack of the player
class PlayerSlash : public GameObject
{
public:
  PlayerSlash();
  // rx and ry are relative to player location (x = player x + prx)
  PlayerSlash(int rx, int ry, int width, int height, std::vector<GameObject*>* objs, Display* display);
  ~PlayerSlash();

  void handleEvent(SDL_Event* e);
  void update();
  void render(int cameraX, int cameraY);

  double getX();
  double getY();

  bool isAlive();
  bool isOnScreen();
  int getType();
  // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  int rx, ry;
  int playerid = 9999999;
  int lifetime = 20;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
};

#endif
