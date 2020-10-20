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

  gunPoint.x = (width/2) + 10;
  gunPoint.y = (height/5);

  // Animations and their shenanigans
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[STAND]->addFrame(TEX_PLAYER_BODY, 0);
  mAnimations.push_back(new Animation(15, true, textureArray, mDisplay));
  mAnimations[WALK]->addFrame(TEX_PLAYER_BODY, 1);
  mAnimations[WALK]->addFrame(TEX_PLAYER_BODY, 2);
  mAnimations[WALK]->addFrame(TEX_PLAYER_BODY, 3);
  mAnimations[WALK]->addFrame(TEX_PLAYER_BODY, 4);
  mAnimations[WALK]->addFrame(TEX_PLAYER_BODY, 5);
}

Player::~Player()
{
  for(int i = 0; i < mAnimations.size(); i++)
  {
    delete mAnimations[i];
    mAnimations[i] = nullptr;
  }
  mAnimations.clear();
}

double Player::getX(){return x;}
double Player::getY(){return y;}
int Player::getHP(){return hp;}
int Player::getAmmo(){return ammo;}

void Player::handleEvent(SDL_Event* e)
{
    switch(e->type)
    {
      case SDL_KEYDOWN:
      if(stunned < 1) // can't begin moving if stunned
      {
        switch(e->key.keysym.sym)
        {
          case SDLK_RIGHT:
          movingRight = true;
          aimingForward = true;
          facingRight = true;
          break;

          case SDLK_LEFT:
          movingLeft = true;
          aimingForward = true;
          facingRight = false;
          break;

          case SDLK_UP:
          aimingUp = true;
          break;

          case SDLK_DOWN:
          aimingDown = true;
          break;

          case SDLK_j: // for now jump button
          if(!falling)
          {
            jumping = true;
            falling = true;
          }
          break;

          case SDLK_l: // for now shoot button
          {
            Vector2D bulletVector((gunAngle) * (3.14159265359/180), 10); //angle and speed of bullet
            objects->push_back(new Bullet(gunPoint.x + x, gunPoint.y + y, bulletVector, mDisplay, objects, true, 10, 1));
          }
          break;

          case SDLK_k: // for now melee button
          if(meleeCooldown > 0) break;
          // do an attack (add animation later)
          {
            int slashHeight = 40;
            int slashWidth = 40;
            if(facingRight) objects->push_back(new Slash(&x, &y, width, height/2 - slashHeight/2, slashWidth, slashHeight, 1, true, objects, mDisplay));
            else objects->push_back(new Slash(&x, &y, -slashWidth, height/2 - slashHeight/2, slashWidth, slashHeight,-1, true, objects, mDisplay));
            meleeCooldown = 30;
          }
          break;
        }
      }

      break;

      case SDL_KEYUP:
      switch(e->key.keysym.sym)
      {
        case SDLK_RIGHT:
        movingRight = false;
        aimingForward = false;
        break;

        case SDLK_LEFT:
        movingLeft = false;
        aimingForward = false;
        break;

        case SDLK_UP:
        aimingUp = false;
        break;

        case SDLK_DOWN:
        aimingDown = false;
        break;

        case SDLK_j:
        jumping = false;
        break;
      }
      break;

      case SDL_MOUSEMOTION:
      break;
  }
}

void Player::update()
{
  if(hp <= 0) //DESU happens
  {
    //TODO death animations and stuff
    *alive = false;
  }

  // aimingu!
  double target;
  if(!((aimingUp && aimingDown) || (!aimingUp && !aimingDown && !aimingForward)))
  {
    if(aimingUp && !aimingForward) target = 360-90;
    if(aimingUp && aimingForward) target = 360-45;
    if(!aimingUp && !aimingDown && aimingForward) target = 0;
    if(aimingDown && aimingForward) target = 45;
    if(aimingDown && !aimingForward) target = 90;

    if(facingRight == false) target = 180 - target;

    double rotateSpeed = 360; // rotate speed is excessively high because it'll get corrected to target anyway

    double zerodPangle = target - gunAngle;

    if(zerodPangle < 0) zerodPangle += 360;

    if(zerodPangle > rotateSpeed || zerodPangle < -rotateSpeed)
    {
      if(zerodPangle > 180) rotate(-rotateSpeed);
      else rotate(rotateSpeed);
    }
    else rotate(zerodPangle);
/*
    Point p; p.x = 0; p.y = 0;
    rotatePoint(6, &gunPoint, p);
    gunAngle += 6;*/
    if(gunAngle >= 360) gunAngle -= 360;
    else if(gunAngle < 0) gunAngle += 360;

  }

  if(meleeCooldown > 0) meleeCooldown--;

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
  if(iframes > 0) iframes -= 1;

  Point pt; pt.x = -9999; pt.y = -9999;
  if(moving)
  {
    pt = movementCollisionCheck();
  }

  if(pt.x == -9999) {x += xVel;}
  else
  {
    if(xVel > 0)      {x = pt.x - width;}
    else if(xVel < 0) {x = pt.x;}
  }
  if(pt.y == -9999){y += yVel;}
  else
  {
    if(yVel > 0)      {y = pt.y - height;}
    else if(yVel < 0) {y = pt.y;}
  }

  //if(y > 2000) hp -= 1000000;

}

bool Player::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 8)
  {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(!facingRight) flip = SDL_FLIP_HORIZONTAL;
    cameraY -= 1; // to get the player level with the ground

    // placeholder graphics for gun
    /*
    SDL_Rect rect = {x + gunPoint.x - cameraX, y + gunPoint.y - cameraY, 2, 2};
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 102, 102, 0);
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
    */

    //gun graphics
    if(aimingUp && !aimingForward) gunFrame = 0;
    else if(aimingUp && aimingForward) gunFrame = 1;
    else if(!aimingUp && aimingForward && !aimingDown) gunFrame = 2;
    else if(aimingForward && aimingDown) gunFrame = 3;
    else if(!aimingForward && aimingDown) gunFrame = 4;

    (*textureArray)[TEX_PLAYER_GUN]->render(x - 8 - cameraX, y - cameraY, gunFrame, NULL, NULL, NULL, flip);

    if(iframes > 0)
    {
      mAnimations[STAND]->setTransparency(63, 1);
      (*textureArray)[TEX_PLAYER_GUN]->setBlendMode(SDL_BLENDMODE_BLEND);
      (*textureArray)[TEX_PLAYER_GUN]->setAlpha(63);
    }

    if(xVel < 1 && yVel > -1 && xVel > -1 && yVel < 1)
    {
      mAnimations[STAND]->render(x, y, cameraX, cameraY, flip);
      mAnimations[STAND]->update();
      mAnimations[WALK]->reset();
    }
    else
    {
      mAnimations[WALK]->render(x, y, cameraX, cameraY, flip);
      mAnimations[WALK]->update();
    }

  // collision test rectangle, mouse based
    if(renderPoint.intersect)
    {
      SDL_Rect rect2 = { renderPoint.x-3 - cameraX, renderPoint.y-3 - cameraY, 7, 7};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
    }
    if(iframes <= 0)
    {
      mAnimations[STAND]->setTransparency(255, 1);
      (*textureArray)[TEX_PLAYER_GUN]->setBlendMode(SDL_BLENDMODE_BLEND);
      (*textureArray)[TEX_PLAYER_GUN]->setAlpha(255);
    }
    return true;
  }
  return false;
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
        for(int i2 = 0; i2 < width; i2++)
        {
          tempPoint.copy(bptr->lineIntersection(x + i2, y + height - 1, x + i2, y + height + 2,0,0,0,0));
          if(tempPoint.intersect)
          {
            y = bptr->getY() - height - .01;
            return false;
          }
        }
      }
    }
  }
  return true;
}

bool Player::roofCheck(int collidableIndex)
{
  // checks if theres any down facing boundaries directly above the player
  for(int i = 0; i < width; i++)
  {
    Boundary * bptr;
    bptr = dynamic_cast<Boundary*>((*objects)[collidableIndex]);
    CollisionData tempPoint;
    if(bptr->getDown())
    {
      tempPoint.copy(bptr->lineIntersection(x + i, y - 1, x + i, y + 1,0,0,0,0));
      if(tempPoint.intersect)
      {
        // if there is a collision with the roof, stop jumping and moving up
        jumping = false;
        if(yVel < 0) yVel = 0;
        return false;
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

Point Player::movementCollisionCheck()
{
  Point pt; pt.x = -9999; pt.y = -9999;
  Point tpt;

  if(xVel == 0 && yVel == 0) {return pt;}

  std::vector<int> collidables;

  collidables = getCollidableBoundaries();

  if(collidables.size() == 0) {return pt;} // no collisions happened

  double collisionX;
  if(xVel > 0) {collisionX = x + width;}
  else {collisionX = x;}

  double collisionY;
  if(yVel > 0) {collisionY = y + height;}
  else {collisionY = y;}

  //actually colliding
  for(int i = 0; i < collidables.size(); i++)
  {
    tpt = boundaryCollision(collidables);
    if(tpt.x != -9999)
    {
      if(pt.x == -9999){pt.x = tpt.x;}
      else if(std::abs(pt.x - collisionX) > std::abs(tpt.x - collisionX))
      {
        pt.x = tpt.x;
      }
    }
    if(tpt.y != -9999)
    {
      if(pt.y == -9999){pt.y = tpt.y;}
      else if(std::abs(pt.y - collisionY) > std::abs(tpt.y - collisionY))
      {
        pt.y = tpt.y;
      }
    }
    if(yVel < 0) {roofCheck(collidables[i]);}
  }

  return pt;
}

Point Player::boundaryCollision(std::vector<int> collidables)
{
  Boundary * ptr;
  double xMod = 0;
  double yMod = 0;
  if(xVel > 0) xMod = width;
  if(yVel > 0) yMod = height;
  double xm = x + xMod;
  double ym = y + yMod;
  bool done = false;
  double tx; double ty;

  Point returnPoint;
  returnPoint.x = -9999; returnPoint.y = -9999;

  CollisionData cd;

  for(int i = 0; i < collidables.size(); i++)
  {
    ptr = dynamic_cast<Boundary*>((*objects)[collidables[i]]);
    for(int i2 = 0; i2 < height; i2++)
    {
      if(xVel == 0) {break;}

      cd = ptr->lineIntersection(xm, y + i2, xm +xVel, y + i2 + yVel,0,0,0,0);
      tx = cd.x;

      if(tx > -9999 && (ptr->getRight() || ptr->getLeft()))
      {
        returnPoint.x = tx;
        break;
      }
    }
    for(int i2 = 0; i2 < width; i2++)
    {
      if(yVel == 0) {break;}

      cd = ptr->lineIntersection(x + i2, ym, x + i2 + xVel, ym + yVel,0,0,0,0);
      ty = cd.y;

      if(ty > -9999 && (ptr->getDown() || ptr->getUp()))
      {
        returnPoint.y = ty;
        break;
      }
    }
  }

  return returnPoint;
}

std::vector<int> Player::getCollidableBoundaries()
{
  Boundary * ptr;
  double xMod = 0;
  double yMod = 0;
  if(xVel > 0) xMod = width;
  if(yVel > 0) yMod = height;
  double xm = x + xMod;
  double ym = y + yMod;
  bool done = false;
  std::vector<int> collidables;

  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == BOUNDARY)
    {
      done = false;
      ptr = dynamic_cast<Boundary*>((*objects)[i]);

      // check for uncollidable boundaries
      if(ptr->collisionCheck(0,0,0,0,BOUNDARY_X) == BOUNDARY_GO_THROUGH
      || ptr->collisionCheck(0,0,0,0,BOUNDARY_X) == BOUNDARY_NON_DIRECTIONAL
      || (xVel > 0 && ptr->getRight()) || (xVel < 0 && ptr->getLeft())
      || (yVel > 0 && ptr->getDown())  || (yVel < 0 && ptr->getUp()))
      {
        done = true;
      }

      // y checks
      for(int i2 = 0; i2 < width; i2++)
      {
        if(done){break;}
        if(ptr->collisionCheck(xm+i2, ym, xm+xVel, ym+yVel, BOUNDARY_Y) == BOUNDARY_COLLISION)
        {
          collidables.push_back(i);
          done = true;
        }
      }
      // x checks
      for(int i3 = 0; i3 < height; i3++)
      {
        if(done) {break;}
        if(ptr->collisionCheck(xm, ym+i3, xm+xVel, ym+yVel, BOUNDARY_X) == BOUNDARY_COLLISION)
        {
          collidables.push_back(i);
          done = true;
        }
      }
    }
  }

  return collidables;
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
      damaged(hurtPoint);
      break; //stop checking because you're now iframed and can't take further damage
    }
  }
}

void Player::knockedBack(int direction, int force)
{
  falling = true;
  knockback = true;
  xVel = force * direction;
  yVel = -1 - (force * .3);
  if(force < 0) yVel = -1 - (-force * .3);
  y -= 2;
  falling = true;
}

void Player::damaged(CollisionData hurt)
{
  // all ongoing actions are cancelled
  int direct = -1;
  if(iframes <= 0)
  {
    hp -= hurt.damage;
    iframes = hurt.iframes;
    knockedBack(direct, hurt.knockback);
  }
}

void Player::rotate(double angl) // rotate by angl degrees
{
  int w1 = (width/2)+0.5; int h1 = (height/5)+0.5;
  Point p; // this is the centerpoint of rotation
  p.x = w1; p.y = h1;
  rotatePoint(angl, &gunPoint, p);
  gunAngle += angl;
}

CollisionData Player::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
{
  double x3, y3; //first point of checkable line
  double x4, y4; //second point of checkable line

  double xr = -9999;
  double yr = -9999;

  CollisionData result{xr, yr};
  result.intersect = false;

  // check for each line in rectangle shape
  for(int i = 0; i < 4; i++)
  {
    // run collision for each of the lines in the objects
    if(i == 0) // left
    {
      x3 = x;
      y3 = y;
      x4 = x;
      y4 = y + height;
    }
    else if(i == 1) // top
    {
      x3 = x;
      y3 = y;
      x4 = x + width;
      y4 = y;
    }
    else if(i == 2) // bottom
    {
      x3 = x;
      y3 = y + height;
      x4 = x + width;
      y4 = y + height;
    }
    else if(i == 3) // right
    {
      x3 = x + width;
      y3 = y;
      x4 = x + width;
      y4 = y + height;
    }
    double divider = ((ox1-ox2)*(y3-y4))-((oy1-oy2)*(x3-x4));
    if(divider != 0)
    {
      xr = ( ((ox1*oy2)-(oy1*ox2)) * (x3-x4) -( (ox1-ox2) * ((x3*y4) - (y3*x4)) ) )/divider;
      yr = ( ((ox1*oy2)-(oy1*ox2)) * (y3-y4) -( (oy1-oy2) * ((x3*y4) - (y3*x4)) ) )/divider;
    }

    result.x = xr;
    result.y = yr;

    double pow1 = pow((ox1 - ox2), 2.0);
    double pow2 = pow((oy1 - oy2), 2.0);
    double originDistance = sqrt(pow1 + pow2);

    pow1 = pow((ox1 - xr), 2.0);
    pow2 = pow((oy1 - yr), 2.0);
    double intersectionDistance = sqrt(pow1 + pow2);
    if(
      // intersection point is inside the origin line
      (((ox1 >= xr && ox2 <= xr) || (ox2 >= xr && ox1 <= xr)) && ((oy1 >= yr && oy2 <= yr) || (oy2 >= yr && oy1 <= yr)))
      &&
      // intersection point is inside current triangle line
      //MIGHT BE BROKEN
      (((x3 >= xr && x4 <= xr) || (x4 >= xr && x3 <= xr)) && ((y3 >= yr && y4 <= yr) || (y4 >= yr && y3 <= yr)))
      ) result.intersect = true;
  }
  return result;
}
