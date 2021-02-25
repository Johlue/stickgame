#ifndef GAMEOBJECT_03052019
#define GAMEOBJECT_03052019

#include "ImageTexture.h"
#include <SDL.h>
#include <Display.h>
#include <iostream>
#include "CollisionData.h"
#include <cmath>
#include "Point.h"
#include "Vector2D.h"
#include <vector>
#include "func.h"
#include "Animation.h"
#include <stdlib.h>
#include <random>

// identifier for what type of object it is
enum ObjectTypes
{
  GAMEOBJECT = 0,
  PLAYER = 1,
  BOUNDARY = 2,
  HAZARD = 3,
  TURRET = 4,
  BULLET = 5,
  PLAYERATTACK = 6,
  WALKER = 7,
  SWITCH = 8,
  EXIT = 9
};
// Parent to all gameobjects
class GameObject
{
public:
  GameObject();
  // x location, y location, width, heigth, pointer to display
  GameObject(int xl, int yl, int w, int h, Display* display);
  ~GameObject();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual bool render(int cameraX, int cameraY, int priority);

  double getX();
  double getY();

  int getId();
  void setId(int o_id);

  int getWidth();
  int getHeight();

  bool getActivated();

  bool isAlive();
  void kill();
  bool isOnScreen();
  int getType();
  // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
  virtual int activateThisObject(bool on);
protected:
  bool onScreen = true;
  bool alive = true;
  int type = 0;
  int id = -1;
  bool activated = false;

  double x;
  double y;
  int width;
  int height;

  std::vector<ImageTexture*>* textureArray;

  Display* mDisplay = nullptr;
};

#endif
