#ifndef LEVELSELECTSTATE_26112020
#define LEVELSELECTSTATE_26112020

#include "GameState.h"
#include "Display.h"
#include "ImageTexture.h"
#include "MenuButton.h"
#include <vector>

class LevelSelectState : public GameState
{
public:
    LevelSelectState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS, std::string* lvl);
    ~LevelSelectState();

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

    std::string* loadableLevel;

};

#endif
