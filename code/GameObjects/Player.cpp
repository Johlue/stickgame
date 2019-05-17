#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(){}

Player::Player(double xl, double yl, Display* display, std::vector<GameObject*>* obj)
{
  mDisplay = display;
  SDL_Point renderPoint{0, 0};
  x = xl;
  y = yl;
  width = 16;
  height = 32;
  objects = obj;
  type = PLAYER;
}

Player::~Player(){}


void Player::handleEvent(SDL_Event* e)
{
  switch(e->type)
  {
    case SDL_KEYDOWN:
    switch(e->key.keysym.sym)
    {
      case SDLK_RIGHT:
      movingRight = true;
      break;

      case SDLK_LEFT:
      movingLeft = true;
      break;

      case SDLK_UP:
      movingUp = true;
      break;

      case SDLK_DOWN:
      movingDown = true;
      break;
    }
    break;

    case SDL_KEYUP:
    switch(e->key.keysym.sym)
    {
      case SDLK_RIGHT:
      movingRight = false;
      break;

      case SDLK_LEFT:
      movingLeft = false;
      break;

      case SDLK_UP:
      movingUp = false;
      break;

      case SDLK_DOWN:
      movingDown = false;
      break;
    }
    break;

    case SDL_MOUSEMOTION:
    break;
  }
}

void Player::update()
{
  double xMov = 3, yMov = 3;
  if(movingRight && xVel <= xMov)
  {
    xVel += xMov;
    if(xMov < xVel <= 2*xMov) xVel = xMov;
  }
  else if(movingLeft && xVel >= -xMov)
  {
    xVel -= xMov;
    if(-xMov > xVel >= -2 * xMov) xVel = -xMov;
  }
  else xVel = 0;

  if(movingDown && yVel <= yMov)
  {
    yVel += yMov;
    if(yMov < yVel <= 2*yMov) yVel = yMov;
  }
  else if(movingUp && yVel >= -yMov)
  {
    yVel -= yMov;
    if(-yMov > yVel >= -2 * yMov) yVel = -yMov;
  }
  else yVel = 0;

  bool moving = false;
  if(xVel > 0) moving = true; if(xVel < 0) moving = true; if(yVel < 0) moving = true; if(yVel > 0) moving = true;
  if(moving)
  {
    // return true if a collision happened, and then x and y movement is taken care of in the function
    if(boundaryCollision()) return;
  }
  x += xVel;
  y += yVel;
}

void Player::render()
{
  // line drawn from player to mouse location for testing purposes
  /*
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  int xm, ym;
  SDL_GetMouseState( &xm, &ym );
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, xm, ym);
  */

// placeholder graphics for player
  SDL_Rect rect = { x, y, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);

// collision test rectangle, mouse based
  if(renderPoint.intersect)
  {
    SDL_Rect rect2 = { renderPoint.x-3, renderPoint.y-3, 7, 7};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
}

//TODOS: check which corner is colliding instead of looking at velocities
bool Player::boundaryCollision()
{
  double xm, ym;
  double shortestDistance = 999999.0;
  double tempDistance = 99999.0;
  int closestCorner;
  bool colliding;
  bool up = false, down = false, left = false, right = false;
  CollisionData tempPoint;
  renderPoint.intersect = false;
  for(int i = 0; i < objects->size(); i++)
  {
    // run through all boundary type gameobjects
    if((*objects)[i]->getType() == BOUNDARY)
    {
      for(int i2 = 0; i2 < 4; i2++)
      {
        colliding = false;

        // casting a Boundary so i can use boundary functions
        GameObject *tptr = (*objects)[i];
        Boundary *ptr = dynamic_cast<Boundary*>(tptr);

        colliding = false;
        //positive xvel and left are collision
        if(xVel < 0 && ptr->getRight()) colliding = true;
        if(xVel > 0 && ptr->getLeft()) colliding = true;
        //positive yvel and up are collision
        if(yVel < 0 && ptr->getDown()) colliding = true;
        if(yVel > 0 && ptr->getUp()) colliding = true;

        if(colliding)
        {
          if (i2 == 0)
          {
            xm = x; ym = y;
            tempPoint = (*objects)[i]->lineIntersection(x, y, x+xVel, y+yVel, 1, 1, 1, 1);
          }
          if (i2 == 1)
          {
            xm = x + width; ym = y;
            tempPoint = (*objects)[i]->lineIntersection(x + width, y, x+xVel + width, y+yVel, 1, 1, 1, 1);
          }
          if (i2 == 2)
          {
            xm = x; ym = y + height;
            tempPoint = (*objects)[i]->lineIntersection(x, y + height, x+xVel, y+yVel + height, 1, 1, 1, 1);
          }
          if (i2 == 3)
          {
            xm = x + width; ym = y + height;
            tempPoint = (*objects)[i]->lineIntersection(x + width, y + height, x+xVel + width, y+yVel + height, 1, 1, 1, 1);
          }
        }

        // Collisions happen here
        // if an intersection between the ray and the boundary happens do stuff
        if(tempPoint.intersect)
        {
          double pow1 = pow((xm - tempPoint.x), 2.0);
          double pow2 = pow((ym - tempPoint.y), 2.0);
          tempDistance = sqrt(pow1 + pow2);
          // if intersecting multiple boundaries then check which one is closest and collide with that one
          if(tempDistance < shortestDistance)
          {
            closestCorner = i2;
            up = ptr->getUp();
            down = ptr->getDown();
            right = ptr->getRight();
            left = ptr->getLeft();
            shortestDistance = tempDistance;
            renderPoint.copy(tempPoint);
          }
        }
      }
    }
  }
  std::cout << "shortestDistance: " << shortestDistance << std::endl;
  //renderpoint directions should be affecting things as well
  if (renderPoint.intersect)
  {
    double oldX = x, oldY = y;
    switch(closestCorner)
    {
      case 0: //top left
      x = renderPoint.x;
      y = renderPoint.y;
      break;

      case 1: //top right
      x = renderPoint.x - width;
      y = renderPoint.y;
      break;

      case 2: //bottom left
      x = renderPoint.x;
      y = renderPoint.y - height;
      break;

      case 3: //bottom right
      x = renderPoint.x - width;
      y = renderPoint.y - height;
      break;
    }
    // if it's not sloped then you don't stop the motion to the non-colliding direction
    if(!renderPoint.slope)
    {
      if(renderPoint.right || renderPoint.left)
      {
        y = oldY + yVel;
      }
      else if(renderPoint.up || renderPoint.down)
      {
        x = oldX + xVel;
      }
    }
    return true;
  }
  return false;
}
