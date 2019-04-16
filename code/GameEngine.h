#ifndef GAMEENGINE_02042019
#define GAMEENGINE_02042019

#include <iostream>
#include <vector>
#include "Display.h"
#include "GameState.h"

class GameState;

class GameEngine
{
public:
  //TODO: texture reserve area for use of textures
  GameEngine(Display* display);
  ~GameEngine();
  void init(); //TODO: display into this? or move the whole thing into gameengine, should probs do that
  void freeMem();

  void handleEvents();
  void update();
  void render();

  void setState(int s);

  void quit();

private:
  bool mRunning;
  int currentState;
  std::vector<GameState*> states;
  Display* mDisplay = nullptr;
};

#endif
