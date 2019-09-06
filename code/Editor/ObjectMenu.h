#ifndef OBJECTMENU_30082019
#define OBJECTMENU_30082019

#include <vector>
#include "ImageTexture.h"
#include <iostream>

enum mStates{CLOSED, ENEMIES, OBJECTS};

class ObjectMenu
{
public:
  ObjectMenu();
  void render();
  void handleEvents();
  void setTextureArray(std::vector<ImageTexture*>* tA);
protected:
  int mState = CLOSED; // is it open or closed and what open if it is open
  std::vector<ImageTexture*>* textureArray = nullptr;
  int x = 250; int y = 200;
};

#endif
