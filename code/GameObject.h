#ifndef GAMEOBJECT_03052019
#define GAMEOBJECT_03052019

#include <SDL.h>

class GameObject
{
public:
  GameObject();
  GameObject(int xl, int yl, int w, int h);
  ~GameObject();

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual void render();
private:
  int x;
  int y;
  int width;
  int height;

};

#endif
