#ifndef LEVELBUTTON_26112020
#define LEVELBUTTON_26112020

#include <SDL.h> // for SDL_Point
#include <vector>
#include "ImageTexture.h"

class LevelButton
{
public:
  //enum for current texture

  // create button at x, y
  LevelButton(int x, int y, ImageTexture* it, std::string lvlName);
  ~LevelButton();

  void render();
  // returns a number and depending on what it is MenuState does different things
  bool handleEvent(SDL_Event* e);

  std::string getLevelName();
private:
  int x; int y;
  // intending to have some sort of texture reserve in the game engine or maybe in main
  ImageTexture* mTexture = nullptr;
  int width = 120;
  int height = 80;
  // determines what the button does and maybe TODO what sprites it uses
  std::string levelName;
};

#endif
