#ifndef CREDITSSTATE_10032021
#define CREDITSSTATE_10032021

#include "Display.h"
#include <vector>
#include "Ui.h"
#include "ImageTexture.h"
#include "GameState.h"
#include "GameObject.h"


class CreditsState : public GameState
{
public:
  CreditsState();
  CreditsState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
  ~CreditsState();

  // deal with user input
  void handleEvents(SDL_Event* e);
  // do frame update stuff
  void update();
  // draw the things
  void render();

protected:
  std::vector<ImageTexture*>* textureArray;
  int timePassed = 0;

};



#endif
