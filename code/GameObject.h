#ifndef GAMEOBJECT_03052019
#define GAMEOBJECT_03052019

#include <SDL.h>
#include <Display.h>

// Parent to all gameobjects
class GameObject
{
public:
  GameObject();
  // x location, y location, width, heigth, pointer to display
  GameObject(int xl, int yl, int w, int h, Display* display);
  ~GameObject();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual void render();
protected:
  double x;
  double y;
  int width;
  int height;

  Display* mDisplay = nullptr;
};

#endif
