#ifndef SWITCH_20102020
#define SWITCH_20102020

#include "GameObject.h"
#include <iostream>

class Switch : public GameObject
{
public:
  Switch();
  Switch(double o_x, double o_y, Display* display, std::vector<GameObject*>* obj, bool once = false, int reactivTime = 0);
  ~Switch();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  void activate(bool reactivate = false);
protected:
  bool onlyOnce = false;

  int reactivationTime = 0;
  int reactivationTimeRemaining = -1;

  std::vector<int> activatableObjects;

  std::vector<GameObject*>* objects = nullptr;
};


#endif
