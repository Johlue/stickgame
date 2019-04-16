#ifndef GAMEENGINE_02042019
#define GAMEENGINE_02042019

#include <iostream>
#include "Display.h"
#include "GameState.h"

class GameEngine
{
public:
  //TODO: texture reserve area for use of textures
  void init(); //TODO: display into this? or move the whole thing into gameengine, should probs do that
  void freeMem();

  void handleEvents();
  void update();
  void draw();

  void setState(int s);

  void quit();

private:
  bool mRunning;
  int currentState;
  std::vector<GameState*> states;
  Display* mDisplay = nullptr;
};

#endif
