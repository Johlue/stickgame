#include "EditorObject.h"

EditorObject::EditorObject(){}

EditorObject::EditorObject(int typ, int xl, int yl, Display * disp)
{
  type = typ;
  x = xl;
  y = yl;
  mDisplay = disp;
}

EditorObject::~EditorObject()
{
  if(stringInfo.size() > 0)
  {
    for(int i = 0; i < stringInfo.size(); i++)
    {
      delete stringInfo[i];
      stringInfo[i] = nullptr;
    }
    stringInfo.clear();
  }
}

void EditorObject::update(){}

bool EditorObject::handleEvents(SDL_Event * e, int cameraX, int cameraY)
{
  if(e->type == SDL_MOUSEBUTTONUP )
  {
    return mouseEvent(e->button, cameraX, cameraY);
  }
  return false;
}

void EditorObject::render(int camX, int camY)
{
  if(type == EO_BOUNDARY)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y - camY, x2 - camX, y2 - camY);
  }
  else
  {
    SDL_Rect rect2 = { x - camX, y - camY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), type * 50, type * 33, type * 100, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
}

bool EditorObject::mouseEvent(SDL_MouseButtonEvent& b, int cameraX, int cameraY)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );
  mx += cameraX; my += cameraY;

  if(type == EO_BOUNDARY){mx += 2; my += 2;} // adjust mouse location to make up for wonky hitbox

  if(b.button == SDL_BUTTON_LEFT)
  {
    if( !( mx < x ||  mx > x + width || my < y || my > y + height)  )
    {
      return true;
    }
  }
  return false;
}

void saveLevel(){}

void loadLevel(){}

void EditorObject::setIndex(int i){index = i;}
int EditorObject::getIndex(){return index;}
int EditorObject::getX() {return x;} int EditorObject::getY(){return y;}
int EditorObject::getWidth() {return width;} int EditorObject::getHeight(){return height;}
int EditorObject::getType() {return type;}
void EditorObject::setX2Y2(int xs, int ys)
{
  if(type == EO_BOUNDARY)
  {
    // sets x to the right and x2 to the left, and y to top and y2 to bottom
    if(xs < x) {x2 = x; x = xs;}
    else {x2 = xs;}
    if(ys < y) {y2 = y; y = ys;}
    else {y2 = ys;}
    width = abs(x - x2) + 4;
    height = abs(y - y2) + 4;
    //std::cout << "y: " << y << " x: " << x << " x2: " << x2 << " y2: " << y2 << std::endl;
  }
  else {x2 = xs; y2 = ys;}
}
