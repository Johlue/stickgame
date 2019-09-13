#ifndef OBJECTMENU_30082019
#define OBJECTMENU_30082019

#include <vector>
#include "ImageTexture.h"
#include "EditorObject.h"
#include <iostream>
#include <SDL.h>

enum mStates{CLOSED, ENEMIES, OBJECTS};

class ObjectMenu
{
public:
  ObjectMenu();
  void render();
  bool handleEvents(SDL_Event* e); // returns true if a successful click happened
  void setTextureArray(std::vector<ImageTexture*>* tA);
  void setPointers(EditorObject * ceo, int * co); // set all necessary pointers (except texarray, for some reason)
protected:
  bool mouseEvent(SDL_MouseButtonEvent& b);// returns true if a successful click happened
  int mState = CLOSED; // is it open or closed and what open if it is open
  EditorObject * currentEditorObject; // object chosen for parameter editing
  int * createObject = nullptr; // type of creatable object
  std::vector<ImageTexture*>* textureArray = nullptr;
  int x = 470; int y = 10; int mWidth = 160; int mHeight = 172/4;
  int squareWidth = 39; int squareHeight = 59;
};

#endif
