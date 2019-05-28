#ifndef UI_28052019
#define UI_28052019

#include "ImageTexture.h"
#include "Display.h"
#include "Player.h"

class Ui
{
public:
  Ui();
  ~Ui();
  void update();
  void render();

  Player * getPlayer();
  void setPlayer(Player * newPlayer);

protected:
  Player * player;
};

#endif
