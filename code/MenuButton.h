#ifndef MENUBUTTON_02042019
#define MENUBUTTON_02042019

#include <SDL.h> // for SDL_Point

class MenuButton
{
public:
  //enum for current texture
  enum Texture{NORMAL = 0, HIGHLIGHTED = 1, PRESSED = 2};

  // create button at x, y
  MenuButton(int x, int y);
  ~MenuButton();

  void render();
  void handleEvent(); //TODO: maybe?
private:
  SDL_Point position;
  // intending to have some sort of texture reserve in the game engine or maybe in main
  std::vector<ImageTexture*> textures;
  int currentTexture;
};

#endif
