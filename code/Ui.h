#ifndef UI_28052019
#define UI_28052019

#include "ImageTexture.h"
#include "Display.h"
#include "Player.h"
#include <SDL.h>
#include <iostream>

class Ui
{
public:
  Ui();
  Ui(Display* display);
  ~Ui();
  void update();
  void render();

  Player * getPlayer();
  void setDisplay(Display* disp);
  void setPlayer(Player * newPlayer);
  void setDeadPlayer(bool dead);

protected:
  Player * player;
  bool playerDead = false;
  Display * mDisplay;
};

#endif
