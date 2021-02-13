#include "LevelExit.h"

LevelExit::LevelExit(){}
LevelExit::LevelExit(int xl, int yl, std::string name, bool active, Display* display, std::vector<ImageTexture*>* texs)
{
  textureArray = texs;
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
    if(activated){(*textureArray)[TEX_EXIT_DOOR]->render(x - 20 - cameraX, y - cameraY, 1);}
    else{(*textureArray)[TEX_EXIT_DOOR]->render(x - 20 - cameraX, y - cameraY, 0);}
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
