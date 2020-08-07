#include "GameEngine.h"
#include "Display.h"

GameEngine::GameEngine(Display* display, Writer* writer)
{

  mDisplay = display;
  //TODO all the things, basically create a display and initialize gamestates and whatever
  // load a texture to the thingy
  loadImageTexture("menuButtons.png", 1, 9);            // 0
  loadImageTexture("chara.png", 10, 10);                // 1
  loadImageTexture("LevelEditMenu1.png", 1, 4);         // 2
  loadImageTexture("LevelEditMenuEnemies.png", 1, 1);   // 3
  loadImageTexture("LevelEditMenuObjects.png", 1, 1);   // 4
  loadImageTexture("GigalazerCircleInside.png", 1, 1);  // 5
  loadImageTexture("GigalazerCircleOutside.png", 1, 1); // 6
  loadImageTexture("GigalazerSquareInside.png", 1, 1);  // 7
  loadImageTexture("GigalazerSquareOutside.png", 1, 1); // 8
  loadImageTexture("MOUSE_CREATE.png", 1, 1);           // 9
  loadImageTexture("MOUSE_DRAG.png", 1, 1);             // 10
  loadImageTexture("MOUSE_EDIT.png", 1, 1);             // 11
  /*
  mTextures.push_back(new ImageTexture());
  mTextures[0]->setRenderer(display->getRenderer());
  if(!mTextures[0]->loadFromFile("menuButtons.png"))
  {
    // fail check
    printf("Failed to load button sprite texture!\n");
  }
  mTextures[0]->useSpriteSheet(1, 9);*/
  mWriter = writer;

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
  if(spriteRow > 1 || spriteCol > 1) mTextures.back()->useSpriteSheet(spriteRow, spriteCol);
}

void GameEngine::init()
{
  states.push_back(new MenuState(mDisplay, &mTextures, &currentState, mWriter));
  states.push_back(new PlayState(mDisplay, &mTextures, &currentState, mWriter));
  states.push_back(new LevelEditState(mDisplay, &mTextures, &currentState, mWriter));
  //std::cout << states.size() << std::endl;
  mRunning = true;
  currentState = MENUSTATE;
  // create gamestates and i guess initialize them or whatever, the display is already in another place so who cares
}

void GameEngine::freeMem()
{
  //TODO: go through gamestate vector and freeMem all of the things
  for(int i = 0; i < mTextures.size(); i++)
  {
    mTextures[i]->freeTexture();
    delete mTextures[i];
    mTextures[i] = nullptr;
  }
  mTextures.clear();
  for(int i = 0; i < states.size(); i++)
  {
    states[i]->freeMem();
    delete states[i];
    states[i] = nullptr;
  }
  states.clear();
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
