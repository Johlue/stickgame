#include "GameEngine.h"

GameEngine::GameEngine(Display* display)
{
  //TODO all the things, basically create a display and initialize gamestates and whatever
  mDisplay = display;
  init();
}

void GameEngine::init()
{
  mRunning = true;
  currentState = 0;
  // create gamestates and i guess initialize them or whatever, the display is already in another place so who cares
}

void GameEngine::freeMem()
{
  //TODO: go through gamestate vector and freeMem all of the things
}

void GameEngine::handleEvents()
{
  states[currentState].handleEvents();
}

void GameEngine::update()
{
  states[currentState].update();
}

void GameEngine::render()
{
  states[currentState].render();
}

void GameEngine::setState(int s)
{
  currentState = s;
}

void GameEngine::quit()
{
  freeMem(); //...seems a bit redundant
}
