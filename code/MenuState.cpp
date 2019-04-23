#include "MenuState.h"
#include "GameState.h"
#include "MenuButton.h"
#include <vector>

MenuState::MenuState(Display* dis, std::vector<ImageTexture*>* texA)
{
  textureArray = texA;
  init();
}

MenuState::~MenuState()
{}

void MenuState::init()
{
//  MenuButton()
}

void MenuState::freeMem()
{
  printf("FREEDOM! (MenuState)\n");
  textureArray = nullptr;
}

void MenuState::handleEvents()
{}

void MenuState::update()
{}

void MenuState::render()
{}

void MenuState::changeState(int s)
{
  *currentState = s;
}
