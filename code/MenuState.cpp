#include "MenuState.h"
#include "GameState.h"
#include <vector>

MenuState::MenuState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS, std::vector<int>* kbs)
{
  keybindings = kbs;
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  mWriter = texS;
  init();
}

MenuState::~MenuState()
{}

void MenuState::init()
{
  // create new buttons
  buttonArray.push_back( new MenuButton(160, 40, textureArray->at(TEX_MENUBUTTONS), START));     // Start
  buttonArray.push_back( new MenuButton(160, 490, textureArray->at(TEX_MENUBUTTONS), QUIT)); // ???
  buttonArray.push_back( new MenuButton(160, 190, textureArray->at(TEX_MENUBUTTONS), EDIT));   // ???
  buttonArray.push_back( new MenuButton(160, 340, textureArray->at(TEX_MENUBUTTONS), LEVEL_SELECT));   // ???
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
  if(keybindCustomization)
  {

  }
  else
  {
    for(int i = 0; i < buttonArray.size(); i++)
    {
      if(buttonArray[i]->handleEvent(e) == START)
      {
        changeState(PLAYSTATE);
      }
      if(buttonArray[i]->handleEvent(e) == EDIT)
      {
        changeState(LEVELEDITSTATE);
      }
      if(buttonArray[i]->handleEvent(e) == LEVEL_SELECT)
      {
        changeState(LEVELSELECTSTATE);
      }
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
  if(keybindCustomization)
  {

  }
  else
  {
    for(int i = 0; i < buttonArray.size(); i++)
    {
      buttonArray[i]->render();
    }
  }
/*
  (*mSymbols)[0]->render(30, 30);
  (*mSymbols)[2]->render(45, 30);
  (*mSymbols)[5]->render(60, 30);
  (*mSymbols)[9]->render(75, 30);
  (*mSymbols)[13]->render(90, 30);*/
}

void MenuState::changeState(int s)
{
  *currentState = s;
}
