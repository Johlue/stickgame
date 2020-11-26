#include "LevelButton.h"

LevelButton::LevelButton(int ox, int oy, ImageTexture* it, std::string lvlName)
{
  x = ox;
  y = oy;
  mTexture = it;
  levelName = lvlName;
}
LevelButton::~LevelButton()
{
  mTexture = nullptr;
}

void LevelButton::render()
{
  /*SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, x + width, y);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, x, y + height);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x + width, y + height, x + width, y);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x + width, y + height, y + height);*/
}
bool LevelButton::handleEvent(SDL_Event* e){}

std::string LevelButton::getLevelName(){return levelName;}
