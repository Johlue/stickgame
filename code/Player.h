#ifndef PLAYER_07052019
#define PLAYER_07052019

#include "GameObject.h"

class Player : public GameObject
{
public:
  Player();
  // x location, y location, pointer to display
  Player(int xl, int yl, Display* display);
  ~Player();

  void handleEvent(SDL_Event* e);
  void update();
  void render();
protected:
  bool movingRight = false;
  bool movingLeft = false;
};


#endif
