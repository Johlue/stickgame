#ifndef MENUSTATE_19032019
#define MENUSTATE_19032019

#include "GameState.h"
#include "Display.h"
#include "ImageTexture.h"
#include <vector>

class MenuState : public GameState
{
public:
    MenuState(Display* dis, std::vector<ImageTexture*>* texA);
    ~MenuState();

    void init();
    void freeMem();

    // deal with user input
    void handleEvents();
    // do frame update stuff
    void update();
    // draw the things
    void render();
    //tells the GameEngine to change game states
    void changeState(int s);
  private:
    std::vector<ImageTexture*>* textureArray;

};

#endif
