#include "LevelSelectState.h"
#include "GameState.h"
#include <vector>

LevelSelectState::LevelSelectState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS, std::string* lvl)
{
  loadableLevel = lvl;
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  mWriter = texS;
  init();
}

LevelSelectState::~LevelSelectState()
{}

void LevelSelectState::init()
{
  std::ifstream levelList;
  levelList.open("LevelList.txt");
  if(levelList.is_open())
  {
    std::string line;
    while ( std::getline(levelList, line) )
    {
      levelArray.push_back(line);
    }
    for(int i = 0; i < levelArray.size(); i++)
    {
      std::cout << levelArray[i] << std::endl;
    }
  }
}

void LevelSelectState::freeMem()
{
  printf("FREEDOM! (LevelSelectState)\n");
	for(int i = 0; i < buttonArray.size(); i++)
	{
		delete (buttonArray[i]);
    buttonArray[i] = nullptr;
	}
	buttonArray.clear();
}

void LevelSelectState::handleEvents(SDL_Event* e)
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

void LevelSelectState::update(){}

void LevelSelectState::render()
{
  for(int i = 0; i < 36/*levelArray.size()*/; i++)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0);
    int xMod = (i%6)*200;
    int yMod = ((i/6)%4)*150;
    drawRectangle(mDisplay->getRenderer(), 40 + xMod, 40 + yMod, 220 + xMod, 150 + yMod);
  }
}

void LevelSelectState::changeState(int s)
{
  *currentState = s;
}
