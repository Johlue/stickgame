#ifndef SWITCH_20102020
#define SWITCH_20102020

#include "GameObject.h"
#include <iostream>

enum SwitchTypes
{
  SWITCH_WALL, SWITCH_FLOOR
};

class Switch : public GameObject
{
public:
  Switch();
  Switch(double o_x, double o_y, Display* display, std::vector<GameObject*>* obj, int switch_Type, bool once = false, int reactivTime = 0);
  ~Switch();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  void addActivatable(int o_id);

  void activate(bool reactivate = false);
protected:
  bool onlyOnce = false;

  int switchType = SWITCH_WALL;

  bool activated = false;

  int reactivationTime = 0;
  int reactivationTimeRemaining = -1;

  std::vector<int> activatableObjects;

  std::vector<GameObject*>* objects = nullptr;
};


#endif
