#include "Boss.h"

Boss::Boss(){}
Boss::Boss(int ox, int oy, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs)
{
  textureArray = texs;
  mDisplay = disp;
  objects = objs;
  x = ox;
  y = oy;
}

void Boss::handleEvent(SDL_Event* e){}
void Boss::update()
{
  if(playerid > objects->size() - 1) playerid = 9999999;
  else if((*objects)[playerid]->getType() != PLAYER) playerid = 9999999;

  if(playerid == 9999999)
  {
    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == PLAYER)
      {
        playerid = i;
        break;
      }
    }
  }

  if(playerid == 9999999) //don't do things if playerid is not valid
  {return;}

  if(actionState == BAS_UNAWARE) // don't do things if player isn't around
  {
    if((*objects)[playerid]->getY() > y){actionState = BAS_NORMAL;} // activate self if players y position is below own
    else{return;}
  }
}

bool Boss::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 8)
  {
    SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
    SDL_Rect recta1 = {x - cameraX, y + 10 - cameraY, width, height - 10};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &recta1);
    SDL_Rect recta2 = {x + width/2 - 5 - cameraX, y - cameraY, 10, 10};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &recta2);
    return true;
  }
  return false;
}
Boss::~Boss()
{
  for(int i = 0; i < mAnimations.size(); i++)
  {
    delete mAnimations[i];
    mAnimations[i] = nullptr;
  }
  mAnimations.clear();
}

SDL_Rect Boss::getHurtBox()
{
  SDL_Rect recta = {x, y + 10, width, height - 10};
  return recta;
}

SDL_Rect Boss::getCritBox()
{
  SDL_Rect recta = {x + width/2 - 5, y, 10, 10};
  return recta;
}
