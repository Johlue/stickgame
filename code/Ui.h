#ifndef UI_28052019
#define UI_28052019

#include "ImageTexture.h"
#include "Display.h"
#include "Player.h"
#include <SDL.h>

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

protected:
  Player * player;
  Display * mDisplay;
};

#endif
