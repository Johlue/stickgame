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
  EditorObject(int typ, int xl, int yl, Display * disp);
  bool handleEvents(SDL_Event* e);
  void render(int camX, int camY);
  void update();
  void setIndex(int i);
  int getIndex();
  int getX(); int getY(); int getWidth(); int getHeight(); int getType();
  void setX2Y2(int xs, int ys);

protected:
  bool mouseEvent(SDL_MouseButtonEvent& b); // return true if this object was clicked, else return false
  int x; int y; int width = 30; int height = 30;
  int x2; int y2; // for boundary objects
  int stringLength; // how many separated letters in a string
  int type; //as in object type
  Display * mDisplay;
  int index; // the current location of the object in the object vector
};

#endif
