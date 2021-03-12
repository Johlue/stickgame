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
  buttonArray.push_back( new MenuButton(260, 190, textureArray->at(TEX_MENUBUTTONS), START));     // Start
  buttonArray.push_back( new MenuButton(460, 490, textureArray->at(TEX_MENUBUTTONS), QUIT)); // ???
  buttonArray.push_back( new MenuButton(660, 340, textureArray->at(TEX_MENUBUTTONS), EDIT));   // ???
  buttonArray.push_back( new MenuButton(260, 340, textureArray->at(TEX_MENUBUTTONS), LEVEL_SELECT));   // ???
  buttonArray.push_back( new MenuButton(660, 190, textureArray->at(TEX_MENUBUTTONS), KEYBIND_CUSTOMIZING));
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
    if( e->type == SDL_MOUSEBUTTONUP )
    {
      if(e->button.button == SDL_BUTTON_RIGHT)
      {
        keybindCustomization = false;
        keybindNumber = 0;
      }
    }
    if(e->type == SDL_KEYUP)
    {
      (*keybindings)[keybindNumber] = e->key.keysym.sym;

      keybindNumber++;
      if(keybindNumber >= 6)
      {
        std::ofstream levelfile;
        levelfile.open("keybindings.txt");

        keybindCustomization = false;
        keybindNumber = 0;

        for(int i = 0; i < keybindings->size(); i++)
        {
          levelfile << (*keybindings)[i];
          levelfile << "\n";
        }

        levelfile.close();
      }
    }
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
      if(buttonArray[i]->handleEvent(e) == KEYBIND_CUSTOMIZING)
      {
        keybindCustomization = true;
        keybindNumber = 0;
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
    std::string currentkey = "Press button for: ";
    if(keybindNumber == KB_UP)  {currentkey = currentkey + "UP";}
    if(keybindNumber == KB_DOWN){currentkey = currentkey + "DOWN";}
    if(keybindNumber == KB_RIGHT){currentkey = currentkey + "RIGHT";}
    if(keybindNumber == KB_LEFT){currentkey = currentkey + "LEFT";}
    if(keybindNumber == KB_SHOOT){currentkey = currentkey + "SHOOT";}
    if(keybindNumber == KB_JUMP){currentkey = currentkey + "JUMP";}
    mWriter->render(currentkey, 560, 300);
  }
  for(int i = 0; i < buttonArray.size(); i++)
  {
    buttonArray[i]->render();
  }

  (*textureArray)[TEX_TITLE]->render(0,0,0);

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
