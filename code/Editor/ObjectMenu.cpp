#include "ObjectMenu.h"

ObjectMenu::ObjectMenu()
{}

void ObjectMenu::render()
{
  if(mState == CLOSED || mState == OBJECTS) (*textureArray)[2]->render(x, y, 1);
  else (*textureArray)[2]->render(x, y, 0);

  if(mState == CLOSED || mState == ENEMIES) (*textureArray)[2]->render(x, y+50, 3);
  else (*textureArray)[2]->render(x, y+50, 2);

}

void ObjectMenu::handleEvents(SDL_Event* e)
{
  if(e->type == SDL_MOUSEBUTTONUP )
  {
    mouseEvent(e->button);
  }
}


void ObjectMenu::setTextureArray(std::vector<ImageTexture*>* tA)
{
  textureArray = tA;
}

void ObjectMenu::mouseEvent(SDL_MouseButtonEvent& b)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );

  if(b.button == SDL_BUTTON_LEFT)
  {
    //Check if mouse is NOT outside button
    if( !( mx < x ||  mx > x + mWidth || my < y || my > y + mHeight)  )
    {
      if(mState == CLOSED || mState == OBJECTS) mState = ENEMIES;
      else if(mState == ENEMIES) mState = CLOSED;
    }
    else if(  !(mx < x ||  mx > x + mWidth || my < y + 50 || my > y + 50 + mHeight)  )
    {
      if(mState == CLOSED || mState == ENEMIES) mState = OBJECTS;
      else if(mState == OBJECTS) mState = CLOSED;
    }
  }
}
