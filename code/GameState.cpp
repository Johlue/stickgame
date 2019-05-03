#include "GameState.h"
#include <vector>

GameState::GameState()
{}

GameState::GameState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{}

GameState::~GameState()
{}


  void GameState::init()
  {}

  void GameState::freeMem()
  {}

  void GameState::handleEvents(SDL_Event* e)
  {}

  void GameState::update()
  {}

  void GameState::render()
  {}

// this is where all the gamestates are inherited from
void GameState::changeState(int s)
{
  *currentState = s;
}
