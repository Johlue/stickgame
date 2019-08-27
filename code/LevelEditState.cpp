#include "LevelEditState.h"


LevelEditState::LevelEditState()
{}

LevelEditState::LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{}

LevelEditState::~LevelEditState()
{}


void LevelEditState::init()
{}

void LevelEditState::freeMem()
{}

void LevelEditState::handleEvents(SDL_Event* e)
{}

void LevelEditState::update()
{}

void LevelEditState::render()
{}

void LevelEditState::changeState(int s)
{
  *currentState = s;
}
