#include "LevelEditState.h"


LevelEditState::LevelEditState()
{}

LevelEditState::LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  std::cout << "how ";
  currentState = cs;
  std::cout << "far ";
  mDisplay = dis;
  std::cout << "do we ";
  textureArray = texA;
  std::cout << "get";
}

LevelEditState::~LevelEditState()
{}


void LevelEditState::init()
{}

void LevelEditState::freeMem()
{}

void LevelEditState::handleEvents(SDL_Event* e)
{
  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_ESCAPE:
      *currentState = MENUSTATE;
      break;
    }
  }
}

void LevelEditState::update()
{

}

void LevelEditState::render()
{

}

void LevelEditState::changeState(int s)
{
  *currentState = s;
}
