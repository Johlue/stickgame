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
  maxPage = ((levelArray.size()-1) / 24) + 1;
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

      case SDLK_RIGHT:
      if(levelPage < maxPage){levelPage++;}
      break;

      case SDLK_LEFT:
      if(levelPage > 1){levelPage--;}
      break;
    }
  }
  if(e->type == SDL_MOUSEBUTTONUP)
  {
    int x, y;
    SDL_GetMouseState( &x, &y );

    for(int i = (levelPage-1)*24; (i < (levelPage*24)) && (i < levelArray.size()); i++)
    {
      int xMod = (i%6)*200;
      int yMod = ((i/6)%4)*150;

  		if(!(x < 40 + xMod ||  x > 40 + xMod + 160 || y < 40+ yMod || y > 40 + yMod + 110))
      {
        std::cout << i << std::endl;
        *loadableLevel = "levels/" + levelArray[i] + ".txt";
        *currentState = PLAYSTATE;
      }
    }
  }
}

void LevelSelectState::update(){}

void LevelSelectState::render()
{
  int currentLevelImage = 0;
  for(int i = (levelPage-1)*24; (i < (levelPage*24)) && (i < levelArray.size()); i++)
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
  std::string pages = levelPage + " / " + maxPage;
  mWriter->render(std::to_string(levelPage) + " / " + std::to_string(maxPage), 500, 620);
}

void LevelSelectState::changeState(int s)
{
  *currentState = s;
}
