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

void LevelSelectState::handleEvents(SDL_Event* e){}

void LevelSelectState::update(){}

void LevelSelectState::render(){}

void LevelSelectState::changeState(int s)
{
  *currentState = s;
}
