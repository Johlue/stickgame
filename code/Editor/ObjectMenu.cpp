#include "ObjectMenu.h"

ObjectMenu::ObjectMenu()
{
}

void ObjectMenu::render()
{
  if(mState == CLOSED || mState == OBJECTS) (*textureArray)[2]->render(x, y, 1);
  else (*textureArray)[2]->render(x, y, 0);

  if(mState == CLOSED || mState == ENEMIES) (*textureArray)[2]->render(x, y+50, 3);
  else (*textureArray)[2]->render(x, y+50, 2);

}

void ObjectMenu::handleEvents(){}


void ObjectMenu::setTextureArray(std::vector<ImageTexture*>* tA)
{
  textureArray = tA;
}
