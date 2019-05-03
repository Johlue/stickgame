#include "PlayState.h"

PlayState::PlayState()
{}

PlayState::PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
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
{}
