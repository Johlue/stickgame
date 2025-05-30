#ifndef UI_28052019
#define UI_28052019

#include "ImageTexture.h"
#include "Display.h"
#include "Player.h"
#include <SDL.h>
#include <iostream>
#include "Writer.h"

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
  void setWriter(Writer* writ);
  void setPlayer(Player * newPlayer);
  void setDeadPlayer(bool dead);

  void setBoss(Boss * newBoss);
  void deleteBoss();

protected:
  Player * player;
  Boss * boss = nullptr;

  bool playerDead = false;
  Display * mDisplay;
  Writer* mWriter;
};

#endif
