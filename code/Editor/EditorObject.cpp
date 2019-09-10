#include "EditorObject.h"

EditorObject::EditorObject(){}

void EditorObject::update(){}

bool EditorObject::handleEvents(SDL_Event * e)
{
  if(e->type == SDL_MOUSEBUTTONUP )
  {
    mouseEvent(e->button);
  }
  return false;
}

void EditorObject::render(int camX, int camY){}

void EditorObject::mouseEvent(SDL_MouseButtonEvent& b)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );

  if(b.button == SDL_BUTTON_LEFT){}
}
