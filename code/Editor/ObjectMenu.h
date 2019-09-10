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
  ObjectMenu(EditorObject * ceo);
  void render();
  void handleEvents(SDL_Event* e);
  void setTextureArray(std::vector<ImageTexture*>* tA);
protected:
  void mouseEvent(SDL_MouseButtonEvent& b);
  int mState = CLOSED; // is it open or closed and what open if it is open
  EditorObject * currentEditorObject;
  std::vector<ImageTexture*>* textureArray = nullptr;
  int x = 470; int y = 10; int mWidth = 160; int mHeight = 172/4;
};

#endif
