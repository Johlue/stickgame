#include "EditorObject.h"

EditorObject::EditorObject(){}

EditorObject::EditorObject(int typ, int xl, int yl, Display * disp)
{
  type = typ;
  x = xl;
  y = yl;
  mDisplay = disp;
}

void EditorObject::update(){}

bool EditorObject::handleEvents(SDL_Event * e)
{
  if(e->type == SDL_MOUSEBUTTONUP )
  {
    return mouseEvent(e->button);
  }
  return false;
}

void EditorObject::render(int camX, int camY)
{
  SDL_Rect rect2 = { x - camX, y - camY, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), type * 50, type * 33, type * 100, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
}

bool EditorObject::mouseEvent(SDL_MouseButtonEvent& b)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );

  if(b.button == SDL_BUTTON_LEFT)
  {
    if( !( mx < x ||  mx > x + width || my < y || my > y + height)  )
    {
      return true;
    }
  }
  return false;
}

void EditorObject::setIndex(int i){index = i;}
int EditorObject::getIndex(){return index;}
