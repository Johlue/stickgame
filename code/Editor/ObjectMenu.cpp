#include "ObjectMenu.h"

ObjectMenu::ObjectMenu()
{}

void ObjectMenu::render()
{
  if(mState == CLOSED || mState == OBJECTS) (*textureArray)[2]->render(x, y, 3);
  else (*textureArray)[2]->render(x, y, 2);

  if(mState == CLOSED || mState == ENEMIES) (*textureArray)[2]->render(x, y+50, 1);
  else (*textureArray)[2]->render(x, y+50, 0);

  if(mState == ENEMIES) (*textureArray)[3]->render(x, y+100, 0);
  else if(mState == OBJECTS) (*textureArray)[4]->render(x, y+100, 0);
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
    if(mState == OBJECTS)
    {
      if(  !(mx < x ||  mx > x + squareWidth || my < y + 100 || my > y + 100 + squareHeight))
        *createObject = EO_BOUNDARY;
      else if(  !(mx < x + squareWidth ||  mx > x + squareWidth*2 || my < y + 100 || my > y + 100 + squareHeight))
        *createObject = EO_SPIKE;
    }
    else if (mState == ENEMIES)
    {
      if(  !(mx < x ||  mx > x + squareWidth || my < y + 100 || my > y + 100 + squareHeight))
        *createObject = EO_WALKER_M;
    }
  }
  else if(b.button == SDL_BUTTON_RIGHT) *createObject = EO_NONE;
}

void ObjectMenu::setPointers(EditorObject * ceo, int * co)
{
  currentEditorObject = ceo;
  createObject = co;
}
