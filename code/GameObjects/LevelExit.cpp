#include "LevelExit.h"

LevelExit::LevelExit(){}
LevelExit::LevelExit(int xl, int yl, std::string name, bool active, Display* display)
{
  type = EXIT;
  x = xl;
  y = yl;
  width = 40;
  height = 100;
  exitName = name;
  activated = active;
  mDisplay = display;
}
LevelExit::~LevelExit(){}

void LevelExit::handleEvent(SDL_Event* e){}
void LevelExit::update(){}
bool LevelExit::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 7)
  {
    if(activated){SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 255, 0xFF);}
    else{SDL_SetRenderDrawColor(mDisplay->getRenderer(), 100, 100, 100, 0xFF);}

    SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
    return true;
  }
  return false;
}

int LevelExit::activateThisObject(bool on)
{
  if(activated != on)
  {
    activated = !activated;
    // the TODOs must be protected
  }
}

std::string LevelExit::getExitName()
{
  return exitName;
}

CollisionData LevelExit::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
