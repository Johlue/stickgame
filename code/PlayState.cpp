#include "PlayState.h"
#include <iostream>

PlayState::PlayState()
{}

PlayState::PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  //TODO some other stuff
  init();
}

PlayState::~PlayState()
{}

void PlayState::init()
{}

void PlayState::freeMem()
{}

void PlayState::update()
{}

void PlayState::render()
{}

void PlayState::handleEvents(SDL_Event* e)
{
  if(e->type == SDL_KEYDOWN)
  {
    if(e->key.keysym.sym == SDLK_ESCAPE)
    {
      *currentState = MENUSTATE;
    }
  }
}
