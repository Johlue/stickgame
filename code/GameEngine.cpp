#include "GameEngine.h"
#include "Display.h"

GameEngine::GameEngine(Display* display)
{

  mDisplay = display;
  //TODO all the things, basically create a display and initialize gamestates and whatever
  // load a texture to the thingy
  loadImageTexture("menuButtons.png", 1, 9);
  loadImageTexture("chara.png", 10, 10);
  /*
  mTextures.push_back(new ImageTexture());
  mTextures[0]->setRenderer(display->getRenderer());
  if(!mTextures[0]->loadFromFile("menuButtons.png"))
  {
    // fail check
    printf("Failed to load button sprite texture!\n");
  }
  mTextures[0]->useSpriteSheet(1, 9);*/


  std::vector<GameState*> states;
  std::cout << std::endl << currentState << std::endl;
  init();
}

GameEngine::~GameEngine()
{

}

void GameEngine::loadImageTexture(std::string name, int spriteRow, int spriteCol)
{
  mTextures.push_back(new ImageTexture());
  mTextures.back()->setRenderer(mDisplay->getRenderer());
  if(!mTextures.back()->loadFromFile(name)) std::cout << "Failed to load texture: " << name << std::endl;
  if(spriteRow > 1 && spriteCol > 1) mTextures.back()->useSpriteSheet(spriteRow, spriteCol);
}

void GameEngine::init()
{
  states.push_back(new MenuState(mDisplay, &mTextures, &currentState));
  states.push_back(new PlayState(mDisplay, &mTextures, &currentState));
  states.push_back(new LevelEditState(mDisplay, &mTextures, &currentState));
  std::cout << states.size() << std::endl;
  mRunning = true;
  currentState = MENUSTATE;
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
