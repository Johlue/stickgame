#include "Player.h"
#include <iostream>
#include <cmath>

enum Animations {STAND = 0, WALK = 1};

Player::Player(){}

Player::Player(double xl, double yl, bool * life, Display* display, std::vector<GameObject*>* obj, std::vector<ImageTexture*>* texs)// : walkAnimation(15, true, textureArray, mDisplay), standAnimation(15, true, textureArray, mDisplay)
{
  textureArray = texs;
  mDisplay = display;
  SDL_Point renderPoint{0, 0};
  x = xl;
  y = yl;
  width = 16;
  height = 32;
  objects = obj;
  alive = life;
  type = PLAYER;

  // Animations and their shenanigans
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[STAND]->addFrame(1, 0);
  mAnimations.push_back(new Animation(15, true, textureArray, mDisplay));
  mAnimations[WALK]->addFrame(1, 2);
  mAnimations[WALK]->addFrame(1, 3);
}

Player::~Player()
{
  for(int i = 0; i < mAnimations.size(); i++)
  {
    delete mAnimations[i];
  }
  mAnimations.clear();
}

double Player::getX(){return x;}
double Player::getY(){return y;}
int Player::getHP(){return hp;}
int Player::getAmmo(){return ammo;}

void Player::handleEvent(SDL_Event* e)
{
  if(stunned < 1)
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
        if(!falling)
        {
          jumping = true;
          falling = true;
        }
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
        jumping = false;
        break;
      }
      break;

      case SDL_MOUSEMOTION:
      break;
    }
  }
}

void Player::update()
{
  if(hp <= 0) //DESU happens
  {
    //TODO death animations and stuff
    *alive = false;
  }
  //std::cout << "yLoc: " << y << " jumping: " << jumping << " falling: " << falling << std::endl;
  if(!jumping) falling = fallingCheck(); // is the player falling or not
  if(!falling)
  {
    knockback = false;
    currentJump = 0;
    jumpEnded = false;
  }
  if(stunned > 0) stunned--;
  double xMov = 3, yMov = 3;
  if(!knockback)
  {
    // start moving when buttons are pressed, if not knockbacked
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

    if(jumping)
    {
      yVel = -3 - gravity;
      currentJump += 1;
      if(currentJump > maxJump) jumping = false;
    }
/**
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
    */
  }

  if(!falling) yVel = 0;
  else
  {
    //add gravity to yVel if falling
    if(yVel < terminalVelocity) yVel += gravity;
    // reduce yVel to termVel if too high;
    if(yVel > terminalVelocity + gravity) yVel -= gravity;
  }

  bool moving = false;
  if(falling) moving = true;
  if(xVel > 0) moving = true; if(xVel < 0) moving = true; if(yVel < 0) moving = true; if(yVel > 0) moving = true;
  collisionCheck();
  if(moving)
  {
    // return true if a collision happened, and then x and y movement is taken care of in the function
    if(movementCollisionCheck()) return;
  }
  x += xVel;
  y += yVel;

  if(iframes > 0) iframes -= 1;
}

void Player::render(int cameraX, int cameraY)
{

// placeholder graphics for player
/*
  SDL_Rect rect = { x - cameraX, y - cameraY, width, height};
  if(iframes < 1) SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF ); //no iframes atm
  else SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 102, 102, 0);
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);

  //now with real graphics
  (*textureArray)[1]->render(x - cameraX, y - cameraY, 0);
*/
  if(iframes > 0)
  {
    mAnimations[STAND]->setTransparency(63, 1);
  }

  if(xVel < 1 && yVel > -1 && xVel > -1 && yVel < 1)
  {
    mAnimations[STAND]->render(x, y, cameraX, cameraY);
    mAnimations[STAND]->update();
    mAnimations[WALK]->reset();
  }
  else
  {
    mAnimations[WALK]->render(x, y, cameraX, cameraY);
    mAnimations[WALK]->update();
  }

// collision test rectangle, mouse based
  if(renderPoint.intersect)
  {
    SDL_Rect rect2 = { renderPoint.x-3 - cameraX, renderPoint.y-3 - cameraY, 7, 7};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
  if(iframes > 0)
  {
    mAnimations[STAND]->setTransparency(255, 1);
  }
}

bool Player::fallingCheck()
{
  // checks if theres any up facing boundaries directly under the player
  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == BOUNDARY)
    {
      Boundary * bptr;
      bptr = dynamic_cast<Boundary*>((*objects)[i]);
      CollisionData tempPoint;
      if(bptr->getUp())
      {
        tempPoint.copy(bptr->lineIntersection(x, y + 31, x, y + 33,0,0,0,0));
        if(tempPoint.intersect)
        {
          // if there is a collision with the ground set the player on that object
          y = bptr->getY() - 32;
          return false;
        }
        tempPoint.copy(bptr->lineIntersection(x+16, y + 31, x+16, y + 33,0,0,0,0));
        if(tempPoint.intersect)
        {
          y = bptr->getY() - 32;
          return false;
        }
      }
    }
  }
  return true;
}

bool Player::roofCheck()
{
  // checks if theres any down facing boundaries directly above the player
  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == BOUNDARY)
    {
      Boundary * bptr;
      bptr = dynamic_cast<Boundary*>((*objects)[i]);
      CollisionData tempPoint;
      if(bptr->getDown())
      {
        tempPoint.copy(bptr->lineIntersection(x, y - 1, x, y + 1,0,0,0,0));
        if(tempPoint.intersect)
        {
          // if there is a collision with the roof, stop jumping and moving up
          jumping = false;
          if(yVel < 0) yVel = 0;
          return false;
        }
        tempPoint.copy(bptr->lineIntersection(x+16, y - 1, x+16, y + 1,0,0,0,0));
        if(tempPoint.intersect)
        {
          // if there is a collision with the roof, stop jumping and moving up
          jumping = false;
          if(yVel < 0) yVel = 0;
          return false;
        }
      }
    }
  }
  return true;
}

void Player::collisionCheck()
{
  Hazard * hazardPtr;
  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == HAZARD)
    {
      // check if yer standing in fire or something
      hazardPtr = dynamic_cast<Hazard*>((*objects)[i]);
      if(iframes < 1) hazardCollision(hazardPtr);
      else break;
    }
  }
}

bool Player::movementCollisionCheck()
{
  double shortestDistanceX = 999999.0;
  double shortestDistanceY = 999999.0;
  // does a collision happen on either axis
  bool collidingX;
  bool collidingY;
  CollisionData tempPoint;
  // closest points of collision for x and y axis
  CollisionData collisionPointX;
  CollisionData collisionPointY;
  collisionPointX.intersect = false;
  collisionPointY.intersect = false;
  Boundary * ptr;

    // run through all gameobjects, and do stuff depending on their type
  for(int i = 0; i < objects->size(); i++)
  {
    GameObject *tptr = (*objects)[i]; //pointer to store the current object for casting purposes
    switch ((*objects)[i]->getType()) {
      case BOUNDARY:
      // colliding with the walls
      //convert object to appropriate type
      ptr = dynamic_cast<Boundary*>(tptr);
      boundaryCollision(ptr, &tempPoint, &collidingX, &collidingY, &collisionPointX, &collisionPointY, &shortestDistanceX, &shortestDistanceY);
      break;

    }

  } // this is where collision checking ends
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
      if(collisionPointY.down)
      {
        y = collisionPointY.y;
        //yVel = 0; // if colliding with a down facing boundary(a ceiling) then stop upward momentum, and jumping
        //jumping = false;
      }
      else if(collisionPointY.up) y = collisionPointY.y - height;
    }
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
    roofCheck();
    return true;
  }
  return false;
}

void Player::boundaryCollision(Boundary * ptr, CollisionData * tempPoint, bool * collidingX, bool * collidingY, CollisionData * collisionPointX, CollisionData * collisionPointY, double * shortestDistanceX, double * shortestDistanceY)
{
  bool up = false, down = false, left = false, right = false;
  double xm, ym;
  double tempDistance = 99999.0;
  //required? variables collidingX/Y, collisionPointX/Y, shortestDistanceX/Y
  for(int i2 = 0; i2 < 4; i2++)
  {
    *collidingX = false;
    *collidingY = false;

    // casting a Boundary so i can use boundary functions

    //positive xvel and left are collision
    if(xVel < 0 && ptr->getRight()) *collidingX = true;
    if(xVel > 0 && ptr->getLeft()) *collidingX = true;
    //positive yvel and up are collision
    if(yVel < 0 && ptr->getDown()) *collidingY = true;
    if(yVel > 0 && ptr->getUp()) *collidingY = true;

    // check for intersections
    if(*collidingX || *collidingY)
    {
      if (i2 == 0) // top left
      {
        xm = x; ym = y;
        *tempPoint = ptr->lineIntersection(x, y, x+xVel, y+yVel, 1, 1, 1, 1);
      }
      if (i2 == 1) // top right
      {
        xm = x + width; ym = y;
        *tempPoint = ptr->lineIntersection(x + width, y, x+xVel + width, y+yVel, 1, 1, 1, 1);
      }
      if (i2 == 2) //bottom left
      {
        xm = x; ym = y + height;
        *tempPoint = ptr->lineIntersection(x, y + height, x+xVel, y+yVel + height, 1, 1, 1, 1);
      }
      if (i2 == 3) // bottom right
      {
        xm = x + width; ym = y + height;
        *tempPoint = ptr->lineIntersection(x + width, y + height, x+xVel + width, y+yVel + height, 1, 1, 1, 1);
      }
    }

    // Collisions happen here
    // if an intersection between the ray and the boundary happens do stuff
    if(tempPoint->intersect)
    {
      double pow1 = pow((xm - tempPoint->x), 2.0);
      double pow2 = pow((ym - tempPoint->y), 2.0);
      tempDistance = sqrt(pow1 + pow2);
      // if intersecting multiple boundaries then check which one is closest and collide with that one
      if(*collidingX && tempDistance < *shortestDistanceX)
      {
        up = ptr->getUp();
        down = ptr->getDown();
        right = ptr->getRight();
        left = ptr->getLeft();
        *shortestDistanceX = tempDistance;
        collisionPointX->copy(*tempPoint);
      }
      if(*collidingY && tempDistance < *shortestDistanceY)
      {
        up = ptr->getUp();
        down = ptr->getDown();
        right = ptr->getRight();
        left = ptr->getLeft();
        *shortestDistanceY = tempDistance;
        collisionPointY->copy(*tempPoint);
      }
      // if colliding with an up facing boundary, then falling = false
      // also knockbacking ends upon collision  with the floor
      if(up && (i2 == 2 || i2 == 3))
      {
        if(knockback == true) stunned += 20;
        knockback = false;
        falling = false;
        yVel = 0;
      }
    }
  }
}

void Player::hazardCollision(Hazard * hazardPtr)
{
  CollisionData hurtPoint;
  hurtPoint.intersect = false;
  for(int i = 0; i < 4; i++)
  {
    //check for collisions between the players edges and the hazards edges
    switch (i) {
      case 0:
      hurtPoint = hazardPtr->lineIntersection(x, y, x + width, y,0,0,0,0);
      break;

      case 1:
      hurtPoint = hazardPtr->lineIntersection(x, y, x, y + height,0,0,0,0);
      break;

      case 2:
      hurtPoint = hazardPtr->lineIntersection(x+width, y, x + width, y+height,0,0,0,0);
      break;

      case 3:
      hurtPoint = hazardPtr->lineIntersection(x, y+height, x + width, y+height,0,0,0,0);
      break;
    }
    if(hurtPoint.intersect)
    {
      //damage and knockback happens, also iframes and status and whatever else
      hp -= hurtPoint.damage;
      iframes += hurtPoint.iframes;
      break; //stop checking because you're now iframed and can't take further damage
    }
  }
}

void Player::knockedBack(int direction, int force)
{
  falling = true;
  knockback = true;
  xVel = force * direction;
  yVel = -3 - (force * .3);
}

void Player::damaged(CollisionData hurt)
{
  if(iframes <= 0)
  {
    hp -= hurt.damage;
    iframes = hurt.iframes;
    knockedBack(1, 3);
  }
}
