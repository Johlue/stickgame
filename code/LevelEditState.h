#ifndef LEVELEDITSTATE_27082019
#define LEVELEDITSTATE_27082019

#include "GameState.h"

class LevelEditState : public GameState
{
public:
  LevelEditState();
  // Display pointer, vector necessary textures, pointer to the active gamestate
  LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
  ~LevelEditState();

  void init();
  void freeMem();

  // deal with user input
  void handleEvents(SDL_Event* e);
  // do frame update stuff
  void update();
  // draw the things
  void render();

  //tells the GameEngine to change game states
  void changeState(int s);
protected:
};

#endif
