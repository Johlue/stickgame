#ifndef GAMESTATE_19032019
#define GAMESTATE_19032019

#include "Display.h"
#include <vector>
#include "func.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include "ImageTexture.h"
#include <SDL_ttf.h>
#include "TextTexture.h"
#include "Writer.h"
#include <algorithm>

enum GameStates
{
  MENUSTATE = 0,
  PLAYSTATE = 1,
  LEVELEDITSTATE = 2,
  LEVELSELECTSTATE = 3
};

class GameState
{
public:

  GameState();
  // Display pointer, vector necessary textures, pointer to the active gamestate
  GameState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
  ~GameState();

  virtual void init();
  virtual void freeMem();

  // deal with user input
  virtual void handleEvents(SDL_Event* e);
  // do frame update stuff
  virtual void update();
  // draw the things
  virtual void render();

  //tells the GameEngine to change game states
  void changeState(int s);
protected:
  int* currentState;
  Display* mDisplay = nullptr;
  Writer* mWriter;
};

#endif
