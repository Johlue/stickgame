#ifndef EDITOROBJECT_30082019
#define EDITOROBJECT_30082019

#include "GameObject.h"
#include <SDL.h>

class EditorObject
{
public:
  EditorObject();
  bool handleEvents(SDL_Event* e);
  void render(int camX, int camY);
  void update();
protected:
  void mouseEvent(SDL_MouseButtonEvent& b);
  int x; int y; int width; int height;
  int stringLength; // how many separated letters in a string
  int type; //as in object type
};

#endif
