#include "GameEngine.h"
#include "Display.h"

enum GameStates
{
  MENUSTATE = 0,
  PLAYSTATE = 1,
  OTHERSTATE = 2
};

GameEngine::GameEngine(Display* display)
{
  mTextures.push_back(new ImageTexture());
  //TODO all the things, basically create a display and initialize gamestates and whatever
  std::vector<GameState*> states;
  mDisplay = display;
  init();
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
  states.push_back(new MenuState(mDisplay, &mTextures));
  mRunning = true;
  currentState = 0;
  // create gamestates and i guess initialize them or whatever, the display is already in another place so who cares
}

void GameEngine::freeMem()
{
  //TODO: go through gamestate vector and freeMem all of the things
  mTextures[0]->freeTexture();
  delete mTextures[0];
  states[0]->freeMem();
  delete states[0];
}

void GameEngine::handleEvents()
{
  states[currentState]->handleEvents();
}

void GameEngine::update()
{
  states[currentState]->update();
}

void GameEngine::render()
{
  states[currentState]->render();
}

void GameEngine::setState(int s)
{
  currentState = s;
}

void GameEngine::quit()
{
  freeMem(); //...seems a bit redundant
}
