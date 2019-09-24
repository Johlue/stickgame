#include "EditorObject.h"

EditorObject::EditorObject(){}

EditorObject::EditorObject(int typ, int xl, int yl, Display * disp)
{
  type = typ;
  x = xl;
  y = yl;
  mDisplay = disp;
  constructStringInfo();
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

void EditorObject::saveLevel(){}

void EditorObject::loadLevel(){}

void EditorObject::constructStringInfo()
{
  if(type != EO_NONE) // add x and y to the thing if it's not an empty object
  {
    stringInfo.push_back(new EO_String("Type", "type")); // type is added, to not mess up the order of things
    stringInfo.push_back(new EO_String(std::to_string(x), "x"));
    stringInfo.push_back(new EO_String(std::to_string(y), "y"));
  }
  switch(type)
  {
    case EO_NONE:
    stringInfo[0]->value = "None";
    break;

    case EO_BOUNDARY:
    stringInfo[0]->value = "Boundary";
    stringInfo.push_back(new EO_String(std::to_string(0), "x2"));
    stringInfo.push_back(new EO_String(std::to_string(0), "y2"));
    stringInfo.push_back(new EO_String("F", "facing up"));
    stringInfo.push_back(new EO_String("F", "facing down"));
    stringInfo.push_back(new EO_String("F", "facing right"));
    stringInfo.push_back(new EO_String("F", "facing left"));
    break;

    case EO_WALKER_M:
    stringInfo[0]->value = "Walker";
    stringInfo.push_back(new EO_String("MELEE", "combatAI"));
    stringInfo.push_back(new EO_String("WAIT", "walkAI"));
    break;

    case EO_SPIKE:
    stringInfo[0]->value = "Hazard";
    stringInfo.push_back(new EO_String("50", "width"));
    stringInfo.push_back(new EO_String("50", "height"));
    stringInfo.push_back(new EO_String("0", "angle"));
    stringInfo.push_back(new EO_String("50", "damage"));
    stringInfo.push_back(new EO_String("SPIKE", "subtype"));
    break;

    case EO_TURRET:
    stringInfo[0]->value = "Turret";
    break;

  }
}

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
    for(int i= 0; i < stringInfo.size(); i++)
    {
      // reorganize string info
      if(stringInfo[i]->type == "x") stringInfo[i]->value = std::to_string(x);
      if(stringInfo[i]->type == "y") stringInfo[i]->value = std::to_string(y);
      if(stringInfo[i]->type == "x2") stringInfo[i]->value = std::to_string(x2);
      if(stringInfo[i]->type == "y2") {stringInfo[i]->value = std::to_string(y2); break;}
    }
  }
  else {x2 = xs; y2 = ys;}
}
