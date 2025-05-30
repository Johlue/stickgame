#ifndef MENUBUTTON_02042019
#define MENUBUTTON_02042019

#include <SDL.h> // for SDL_Point
#include <vector>
#include "ImageTexture.h"

enum Texture{NORMAL = 0, HIGHLIGHTED = 1, PRESSED = 2};
enum ButtonType{START = 0, QUIT = 1, EDIT = 2, LEVEL_SELECT = 3, KEYBIND_CUSTOMIZING = 4}; //TODO loads and whatnot

class MenuButton
{
public:
  //enum for current texture

  // create button at x, y
  MenuButton(int x, int y, ImageTexture* it, int type, int width = 320, int height = 100);
  ~MenuButton();

  void render();
  // returns a number and depending on what it is MenuState does different things
  int handleEvent(SDL_Event* e);
private:
  SDL_Point mPosition;
  // intending to have some sort of texture reserve in the game engine or maybe in main
  ImageTexture* mTexture = nullptr;
  int currentTexture;
  int mWidth;
  int mHeight;
  int mCurrentSprite = 0;
  // determines what the button does and maybe TODO what sprites it uses
  int mButtonType;
};

#endif
