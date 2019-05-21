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
  double shortestDistanceX = 999999.0;
  double shortestDistanceY = 999999.0;
  double tempDistance = 99999.0;
  int closestCorner;
  // does a collision happen on either axis
  bool collidingX;
  bool collidingY;
  bool up = false, down = false, left = false, right = false;
  CollisionData tempPoint;
  // closest points of collision for x and y axis
  CollisionData collisionPointX;
  CollisionData collisionPointY;
  collisionPointX.intersect = false;
  collisionPointY.intersect = false;

  for(int i = 0; i < objects->size(); i++)
  {
    // run through all boundary type gameobjects
    if((*objects)[i]->getType() == BOUNDARY)
    {
      for(int i2 = 0; i2 < 4; i2++)
      {
        collidingX = false;
        collidingY = false;

        // casting a Boundary so i can use boundary functions
        GameObject *tptr = (*objects)[i];
        Boundary *ptr = dynamic_cast<Boundary*>(tptr);

        //positive xvel and left are collision
        if(xVel < 0 && ptr->getRight()) collidingX = true;
        if(xVel > 0 && ptr->getLeft()) collidingX = true;
        //positive yvel and up are collision
        if(yVel < 0 && ptr->getDown()) collidingY = true;
        if(yVel > 0 && ptr->getUp()) collidingY = true;

        // check for intersections
        if(collidingX || collidingY)
        {
          if (i2 == 0) // top left
          {
            xm = x; ym = y;
            tempPoint = (*objects)[i]->lineIntersection(x, y, x+xVel, y+yVel, 1, 1, 1, 1);
          }
          if (i2 == 1) // top right
          {
            xm = x + width; ym = y;
            tempPoint = (*objects)[i]->lineIntersection(x + width, y, x+xVel + width, y+yVel, 1, 1, 1, 1);
          }
          if (i2 == 2) //bottom left
          {
            xm = x; ym = y + height;
            tempPoint = (*objects)[i]->lineIntersection(x, y + height, x+xVel, y+yVel + height, 1, 1, 1, 1);
          }
          if (i2 == 3) // bottom right
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
          if(collidingX && tempDistance < shortestDistanceX)
          {
            closestCorner = i2;
            up = ptr->getUp();
            down = ptr->getDown();
            right = ptr->getRight();
            left = ptr->getLeft();
            shortestDistanceX = tempDistance;
            collisionPointX.copy(tempPoint);
          }
          if(collidingY && tempDistance < shortestDistanceY)
          {
            closestCorner = i2;
            up = ptr->getUp();
            down = ptr->getDown();
            right = ptr->getRight();
            left = ptr->getLeft();
            shortestDistanceY = tempDistance;
            collisionPointY.copy(tempPoint);
          }
        }
      }
    }
  } // this is where collision checking ends
  std::cout << "X: " << x << std::endl;
  std::cout << "Y: " << y << std::endl;
  //use the correct corner for the collision
  if (collisionPointX.intersect || collisionPointY.intersect)
  {
    double oldX = x, oldY = y;
    if(collisionPointX.intersect)
    {
      if(collisionPointX.right) x = collisionPointX.x;
      else if(collisionPointX.left) x = collisionPointX.x - width;
    }
    if(collisionPointY.intersect)
    {
      if(collisionPointY.down) y = collisionPointY.y;
      else if(collisionPointY.up) y = collisionPointY.y - height;
    }
    if(collisionPointX.intersect && collisionPointY.intersect) std::cout << "xColyCol\n";
    /**switch(closestCorner)
    {
      case 0: //top left
      x = collisionPointX.x;
      y = collisionPointY.y;
      break;

      case 1: //top right
      x = collisionPointX.x - width;
      y = collisionPointY.y;
      break;

      case 2: //bottom left
      x = collisionPointX.x;
      y = collisionPointY.y - height;
      break;

      case 3: //bottom right
      x = collisionPointX.x - width;
      y = collisionPointY.y - height;
      break;
    }*/
    // if it's not sloped then you don't stop the motion to the non-colliding direction
    //if(!renderPoint.slope)
    // if xvel is positive and x is less than old x, do normal movement
    if(xVel > 0 && x < oldX) x = oldX + xVel;
    if(xVel < 0 && x > oldX) x = oldX + xVel;
    if(yVel > 0 && y < oldY) y = oldY + yVel;
    if(yVel < 0 && y > oldY) y = oldY + yVel;
    if(!(collisionPointX.intersect && collisionPointY.intersect))
    {
      if(shortestDistanceX < 999998.0)
      {
        y = oldY + yVel;
      }
      else if(shortestDistanceY < 999998.0)
      {
        x = oldX + xVel;
      }
    }
    return true;
  }
  return false;
}
