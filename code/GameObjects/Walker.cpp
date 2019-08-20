#include "Walker.h"

Walker::Walker(){}
Walker::Walker(int o_x, int o_y, Display* disp, std::vector<GameObject*>* objs)
{
  objects = objs;
  x = o_x; y = o_y;
  mDisplay = disp;
  width = 20;
  height = 40;
  type = WALKER;
}
Walker::~Walker(){}

void Walker::handleEvent(SDL_Event* e){}
void Walker::update()
{
  // check if playrid is valid, if not fix it
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


  if(playerid != 9999999) //don't do things if playerid is not valid
  {
    if(!falling)
    {
      if(fallingCheck()) falling = true;
    }
    if(falling && yVel < 5) yVel += .05;


    if(falling) fallingCollisionCheck();
    if(!falling)
    {
      xVel = 2;
      if(floorBeneath != nullptr)
      {
        if(floorEndCheck())
        {
          // check if you should turn around and then do turn around if you should turn around
          direction = direction * (-1);
        }
      }
    }

    if(wallCheck()) direction = direction * (-1);

    if(detectPlayer()) std::cout << "playerDetected!" << std::endl;

    x += xVel * direction;
    y += yVel;

  }
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
            } else floorBeneath = ptr;
          } else floorBeneath = ptr;
        }
      }
    }
  }
  return false;
}

  // if falling then check for ground impancts and stop falling in case something like that happens
void Walker::fallingCollisionCheck()
{
  CollisionData cd;
  for(int i = 0; i < objects->size() ; i++)
  {
    Boundary* ptr;
    if((*objects)[i]->getType() == BOUNDARY)
    {
      ptr = dynamic_cast<Boundary*>((*objects)[i]);
      if(ptr->getUp())
      {
        cd = ptr->lineIntersection(x, y + height - 1, x, y + height + yVel,0,0,0,0);
        if(cd.intersect)
        {
          yVel = 0;
          y = ptr->getY() - height;
          falling = false;
          floorBeneath = ptr;
          return;
        }
        cd = ptr->lineIntersection(x + width, y + height - 1, x + width, y + height + yVel,0,0,0,0);
        if(cd.intersect)
        {
          yVel = 0;
          y = ptr->getY() - height;
          falling = false;
          floorBeneath = ptr;
          return;
        }
      }
    }
  }
}

// if there's a hole in front of you then turn around
bool Walker::floorEndCheck()
{
  int xloc;
  if(direction == 1) xloc = x + width + 2;
  if(direction == -1) xloc = x - 2;
  CollisionData cd = floorBeneath->lineIntersection(xloc, y + height - 1, xloc, y + height + 2,0,0,0,0);
  if(cd.intersect) return false;
  return true;
}

bool Walker::wallCheck()
{
  if(xVel != 0)
  {
    CollisionData cd;
    for(int i = 0; i < objects->size() ; i++)
    {
      Boundary* ptr;
      if((*objects)[i]->getType() == BOUNDARY)
      {
        ptr = dynamic_cast<Boundary*>((*objects)[i]);
        if(direction > 0)
        {
          if(ptr->getLeft())
          {
            cd = ptr->lineIntersection(x + width - 1, y, x + width + xVel + 1, y,0,0,0,0);
            if(cd.intersect)
            {
              return true;
            }
            cd = ptr->lineIntersection(x + width - 1, y + height - 1, x + width + xVel + 1, y + height - 1 ,0,0,0,0);
            if(cd.intersect)
            {
              return true;
            }
          }
        }
        else if(direction < 0)
        {
          if(ptr->getRight())
          {
            cd = ptr->lineIntersection(x + 1, y, x - xVel - 1, y,0,0,0,0);
            if(cd.intersect)
            {
              return true;
            }
            cd = ptr->lineIntersection(x + 1, y + height - 1, x - xVel - 1, y + height - 1 ,0,0,0,0);
            if(cd.intersect)
            {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

bool Walker::detectPlayer()
{
  // facing the right direction
  if((direction == 1 && (*objects)[playerid]->getX() > x) || (direction == -1 && (*objects)[playerid]->getX() < x))
  {
     // 45 degrees or less angle
    if(abs((*objects)[playerid]->getY() - y) < abs((*objects)[playerid]->getX() - x + (width/2)))
    {
      std::cout << (*objects)[playerid]->getX() - (x+(width/2));
      // is player close enough
      if(abs((*objects)[playerid]->getX() - (x+(width/2))) <= detectionRange)
      {
        return true;
      }
    }
  }
  return false;
}
