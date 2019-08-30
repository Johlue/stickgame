#ifndef GAMEENGINE_02042019
#define GAMEENGINE_02042019

#include <iostream>
#include <vector>
#include <string>
#include "Display.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "LevelEditState.h"

class GameEngine
{
public:
  //TODO: texture reserve area for use of textures
  GameEngine(Display* display);
  ~GameEngine();
  void init(); // does constructor things
  void freeMem();
  void loadImageTexture(std::string name, int spriteRow, int spriteCol); //loads a texture file with this many row and cols

  void handleEvents(SDL_Event* e);
  void update();
  void render();

  void setState(int s); // i think this is useless now

  void quit();

private:
  // is the game paused or not (though I might make a pause state instead of using this)
  bool mRunning;
  // which state is currently running
  int currentState = 0;
  std::vector<GameState*> states;
  // contains textures and is going to be given to gamestates so they... can use... them...
  std::vector<ImageTexture*> mTextures;
  Display* mDisplay = nullptr;
};

#endif
