#ifndef WALKER_16082019
#define WALKER_16082019

#include "GameObject.h"

class Walker : public GameObject
{
public:
  Walker();
  // x location, y location, width, heigth, pointer to display
  Walker(int x, int y, Display* disp);
  ~Walker();

  void handleEvent(SDL_Event* e);
  void update();
  void render(int cameraX, int cameraY);

protected:

};

#endif
