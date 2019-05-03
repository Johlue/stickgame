#ifndef MENUSTATE_19032019
#define MENUSTATE_19032019

#include "GameState.h"
#include "Display.h"
#include "ImageTexture.h"
#include "MenuButton.h"
#include <vector>

class MenuState : public GameState
{
public:
    MenuState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
    ~MenuState();

    void init();
    void freeMem();

    // deal with user input
    void handleEvents(SDL_Event* e);
    // do frame update stuff
    void update();
    // draw the things
    void render();
    //tells the GameEngine to change game states
    void changeState(int s);
  private:
    // arrays to hold things
    std::vector<ImageTexture*>* textureArray;
    std::vector<MenuButton*> buttonArray;
    // useless test integer
    int temp = 0;

};

#endif
