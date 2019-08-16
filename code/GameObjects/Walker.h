#ifndef WALKER_16082019
#define WALKER_16082019

#include "GameObject.h"
#include "Boundary.h"
#include "Player.h"

class Walker : public GameObject
{
public:
  Walker();
  // x location, y location, width, heigth, pointer to display
  Walker(int x, int y, Display* disp, std::vector<GameObject*>* objs);
  ~Walker();

  void handleEvent(SDL_Event* e);
  void update();
  void render(int cameraX, int cameraY);

protected:
  bool fallingCheck();
  void fallingCollisionCheck();
  bool turnAroundCheck();
  double xVel = 0; double yVel = 0;
  int direction = 1; // 1 = right, -1 = left;
  bool falling = false;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  Boundary* floorBeneath = nullptr;
};

#endif
