#include "LevelSelectState.h"
#include "GameState.h"
#include <vector>

LevelSelectState::LevelSelectState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS, std::string* lvl, std::vector<bool>* lvlImg)
{
  levelImages = lvlImg;
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
      if(line != "") {levelArray.push_back(line);}
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
  int currentLevelImage = 0;
  for(int i = levelPage*36; (i < (levelPage+1)) || (i < levelArray.size()) * 36; i++)
  {
    int xMod = (i%6)*200;
    int yMod = ((i/6)%4)*150;
    if(levelImages->at(i) == true)
    {
      (*textureArray)[TEX_FIRST_LEVEL_IMAGE + currentLevelImage]->render(40 + xMod, 40 + yMod);
      currentLevelImage++;
    }
    else
    {
      (*textureArray)[TEX_404]->render(40 + xMod, 40 + yMod);
    }
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0);
    drawRectangle(mDisplay->getRenderer(), 40 + xMod, 40 + yMod, 220 + xMod, 150 + yMod);
    mWriter->render(levelArray[i], xMod + 60, yMod + 160);
  }
  // page SELECT
  // level images
}

void LevelSelectState::changeState(int s)
{
  *currentState = s;
}
