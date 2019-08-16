#include "Walker.h"

Walker::Walker(){}
Walker::Walker(int o_x, int o_y, Display* disp, std::vector<GameObject*>* objs)
{
  objects = objs;
  x = o_x; y = o_y;
  mDisplay = disp;
  width = 20;
  height = 40;
}
Walker::~Walker(){}

void Walker::handleEvent(SDL_Event* e){}
void Walker::update()
{
  if(!falling)
  {
    if(fallingCheck()) falling = true;
  }
  if(falling && yVel < 5) yVel += .05;
  x += xVel;
  y += yVel;
}
void Walker::render(int cameraX, int cameraY)
{
  SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
}

bool Walker::fallingCheck()
{
  if(!falling) // no point checking if already falling
  {
    CollisionData cd;
    for(int i = 0; i < objects->size(); i++)
    {
      Boundary* ptr;
      if((*objects)[i]->getType() == BOUNDARY)
      {
        ptr = dynamic_cast<Boundary*>((*objects)[i]);
        if(ptr->getUp())
        {
          cd = ptr->lineIntersection(x, y + height - 1, x, y + height,0,0,0,0);
          if(!cd.intersect)
          {
            cd = ptr->lineIntersection(x + width, y + height - 1, x + width, y + height,0,0,0,0);
            if(!cd.intersect)
            {
              return true; // if neither line intersects with a floor then yes you are falling
            }
          }
        }
      }
    }
  }
  return false;
}
