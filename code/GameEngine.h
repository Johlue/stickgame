#ifndef GAMEENGINE_02042019
#define GAMEENGINE_02042019

#include <iostream>
#include <vector>
#include "Display.h"
#include "GameState.h"
#include "MenuState.h"

class GameEngine
{
public:
  //TODO: texture reserve area for use of textures
  GameEngine(Display* display);
  ~GameEngine();
  void init(); //TODO: display into this? or move the whole thing into gameengine, should probs do that
  void freeMem();

  void handleEvents(SDL_Event* e);
  void update();
  void render();

  void setState(int s);

  void quit();

private:
  bool mRunning;
  int currentState = 0;
  std::vector<GameState*> states;
  // contains textures and is going to be given to gamestates so they... can use... them...
  std::vector<ImageTexture*> mTextures;
  Display* mDisplay = nullptr;
};

#endif
