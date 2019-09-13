#include "EditorObject.h"

EditorObject::EditorObject(){}

EditorObject::EditorObject(int typ, int xl, int yl, int w, int h)
{
  type = typ;
  x = xl;
  y = yl;
  width = w;
  height = h;
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

void EditorObject::render(int camX, int camY){}

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
