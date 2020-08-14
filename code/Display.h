#ifndef DISPLAY_26032019
#define DISPLAY_26032019

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Display
{
public:
  // creates runs init with these variables
  Display(std::string windowName, int posX, int posY, int width, int height);
  // destroys window and renderer and frees memory
  ~Display();
  // free memory
  void freeMem();
  // creates window and renderer according to set parameters
  bool init(std::string windowName, int posX, int posY, int width, int height);

  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();

  int getHeight();
  int getWidth();
private:
  SDL_Window* mWindow = nullptr;
  SDL_Renderer* mRenderer = nullptr;
  int m_height; int m_width;
};


#endif
