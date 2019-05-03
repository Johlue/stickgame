#include "MenuState.h"
#include "GameState.h"
#include <vector>

MenuState::MenuState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
  textureArray = texA;
  init();
}

MenuState::~MenuState()
{}

void MenuState::init()
{
  // create new buttons
  buttonArray.push_back( new MenuButton(0, 0, textureArray->at(0), 0));     // Start
  buttonArray.push_back( new MenuButton(350, 220, textureArray->at(0), 1)); // ???
  buttonArray.push_back( new MenuButton(0, 220, textureArray->at(0), 2));   // ???
}

void MenuState::freeMem()
{
  printf("FREEDOM! (MenuState)\n");
	for(int i = 0; i < buttonArray.size(); i++)
	{
		delete (buttonArray[i]);
	}
	buttonArray.clear();
}

void MenuState::handleEvents(SDL_Event* e)
{
  for(int i = 0; i < buttonArray.size(); i++)
  {
    if(buttonArray[i]->handleEvent( e ) == 0)
    {
      changeState(1);
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
}

void MenuState::changeState(int s)
{
  *currentState = s;
}
