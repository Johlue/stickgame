#ifndef PLAYSTATE_03052019
#define PLAYSTATE_03052019

#include "Display.h"
#include <vector>
#include "Ui.h"
#include "ImageTexture.h"
#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include "Boundary.h"
#include "Hazard.h"
#include "Turret.h"
#include "Bullet.h"


class PlayState : public GameState
{
public:
  PlayState();
  PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
  ~PlayState();

  void init();
  void freeMem();

  // deal with user input
  void handleEvents(SDL_Event* e);
  // do frame update stuff
  void update();
  // draw the things
  void render();

private:
  std::vector<ImageTexture*>* textureArray;
  std::vector<GameObject*> objects;
  Ui ui;
  bool playerAlive = true;
  int cameraX;
  int cameraY;

  int levelSizeX;
  int levelSizeY;

  Player * currentPlayer;
  int playerVectorLocation;

};

#endif
