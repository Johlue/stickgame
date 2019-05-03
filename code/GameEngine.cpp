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
  // load a texture to the thingy
  mTextures[0]->setRenderer(display->getRenderer());
  if(!mTextures[0]->loadFromFile("button.png"))
  {
    // fail check
    printf("Failed to load button sprite texture!\n");
  }
  mTextures[0]->useSpriteSheet(2, 2);

  std::vector<GameState*> states;
  std::cout << std::endl << currentState << std::endl;
  mDisplay = display;
  init();
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
  states.push_back(new MenuState(mDisplay, &mTextures, &currentState));
  mRunning = true;
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

void GameEngine::handleEvents(SDL_Event* e)
{
  //printf("e");
  states[currentState]->handleEvents(e);
}

void GameEngine::update()
{
  //printf("u");
  states[currentState]->update();
}

void GameEngine::render()
{
  //std::cout << currentState;
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
