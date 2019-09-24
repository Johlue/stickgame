#include "MenuState.h"
#include "GameState.h"
#include <vector>

MenuState::MenuState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, std::vector<TextTexture*>* texS)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  mSymbols = texS;
  init();
}

MenuState::~MenuState()
{}

void MenuState::init()
{
  // create new buttons
  buttonArray.push_back( new MenuButton(160, 40, textureArray->at(0), 0));     // Start
  buttonArray.push_back( new MenuButton(160, 340, textureArray->at(0), 1)); // ???
  buttonArray.push_back( new MenuButton(160, 190, textureArray->at(0), 2));   // ???
}

void MenuState::freeMem()
{
  printf("FREEDOM! (MenuState)\n");
	for(int i = 0; i < buttonArray.size(); i++)
	{
		delete (buttonArray[i]);
    buttonArray[i] = nullptr;
	}
	buttonArray.clear();
}

void MenuState::handleEvents(SDL_Event* e)
{
  for(int i = 0; i < buttonArray.size(); i++)
  {
    if(buttonArray[i]->handleEvent( e ) == 0)
    {
      changeState(PLAYSTATE);
    }
    if(buttonArray[i]->handleEvent(e) == 2)
    {
      changeState(LEVELEDITSTATE);
    }
  }
}

void MenuState::update()
{
  //temp++;
  //if(temp > 600){changeState(1);}
}

void MenuState::render()
{
  for(int i = 0; i < buttonArray.size(); i++)
  {
    buttonArray[i]->render();
  }
  (*mSymbols)[0]->render(30, 30);
  (*mSymbols)[2]->render(45, 30);
  (*mSymbols)[5]->render(60, 30);
  (*mSymbols)[9]->render(75, 30);
  (*mSymbols)[13]->render(90, 30);
}

void MenuState::changeState(int s)
{
  *currentState = s;
}
