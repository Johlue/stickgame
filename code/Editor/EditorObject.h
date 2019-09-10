#ifndef EDITOROBJECT_30082019
#define EDITOROBJECT_30082019

#include "GameObject.h"
#include <SDL.h>

enum EO_types
{
  EO_NONE, EO_BOUNDARY, EO_WALKER_M, EO_TURRET, EO_SPIKE //add other stuff later
};

class EditorObject
{
public:
  EditorObject();
  EditorObject(int typ, int xl, int yl, int w, int h);
  bool handleEvents(SDL_Event* e);
  void render(int camX, int camY);
  void update();
protected:
  bool mouseEvent(SDL_MouseButtonEvent& b);
  int x; int y; int width; int height;
  int stringLength; // how many separated letters in a string
  int type; //as in object type
};

#endif
