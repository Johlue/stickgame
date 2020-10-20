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
#include "Walker.h"


class PlayState : public GameState
{
public:
  PlayState();
  PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS);
  ~PlayState();

  void init();
  void freeMem();

  // deal with user input
  void handleEvents(SDL_Event* e);
  // do frame update stuff
  void update();
  // draw the things
  void render();

  void loadLevel(int id); // load a level based on the contents of a text file

protected:
  void boundaryLoad(std::vector<std::string> bl); //boundary portion of level loading
  void hazardLoad(std::vector<std::string> bl);
  void turretLoad(std::vector<std::string> bl);
  void walkerLoad(std::vector<std::string> bl);

  void deleteLevel();

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

  int objectId = 0;

};

#endif
