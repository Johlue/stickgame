#include "Boss.h"

Boss::Boss(){}
Boss::Boss(int ox, int oy, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs)
{
  textureArray = texs;
  mDisplay = disp;
  objects = objs;
  type = BOSS;
  x = ox;
  y = oy;
  center = {x + width/2, y + 20};
  shotgunTarget = {center.x - 150, center.y};

  int wallLeft = -1000000; int wallRight = 1000000;
  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == BOUNDARY)
    {
      Boundary * ptr;
      ptr = dynamic_cast<Boundary*>((*objects)[i]);

      CollisionData cd;
      cd = ptr->lineIntersection(x, y, x - 1000000, y,0,0,0,0);
      if(cd.x > wallLeft && cd.intersect){wallLeft = cd.x;}
      cd = ptr->lineIntersection(x, y, x + 1000000, y,0,0,0,0);
      if(cd.x < wallRight && cd.intersect){wallRight = cd.x;}

      cd = ptr->lineIntersection(x, y + (height/2), x - 1000000, y + (height/2),0,0,0,0);
      if(cd.x > wallLeft && cd.intersect){wallLeft = cd.x;}
      cd = ptr->lineIntersection(x, y + (height/2), x + 1000000, y + (height/2),0,0,0,0);
      if(cd.x < wallRight && cd.intersect){wallRight = cd.x;}

      cd = ptr->lineIntersection(x, y + height, x - 1000000, y + height,0,0,0,0);
      if(cd.x > wallLeft && cd.intersect){wallLeft = cd.x;}
      cd = ptr->lineIntersection(x, y + height, x + 1000000, y + height,0,0,0,0);
      if(cd.x < wallRight && cd.intersect){wallRight = cd.x;}
    }
  }

  leftWall = wallLeft;
  rightWall = wallRight;


  mAnimations.push_back(new Animation(2, false, textureArray, mDisplay));
  mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 36);
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 35);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 34-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 31);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 30-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 27);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 26-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 23);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 22-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 19);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 18-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 15);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 14-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 11);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 10-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 7);}/*
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 6-i);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 3);}
  for(int i = 0; i < 3; i++){mAnimations[0]->addFrame(TEX_BOSS_MEGAGUNS, 2-i);}*/

  mAnimations.push_back(new Animation(2, false, textureArray, mDisplay));
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 7);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 8+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 11);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 12+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 15);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 16+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 19);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 20+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 23);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 24+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 27);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 28+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 31);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 32+i);}
  for(int i = 0; i < 2; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 34);}
  for(int i = 0; i < 3; i++){mAnimations[1]->addFrame(TEX_BOSS_MEGAGUNS, 35+i);}
}

void Boss::handleEvent(SDL_Event* e)
{}
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
    if((*objects)[playerid]->getY() > y - 160){actionState = BAS_NORMAL;} // activate self if players y position is below own
    else{return;}
  }

  if(hp <= 0){actionState = BAS_DEAD; shieldState = BSH_DEAD;}

  if(actionState == BAS_DEAD)
  {
    deathTime += 2;
    // some post death stuff maybe?
    return;
  }

  // actual actions go here
  center = {x + width/2, y + 20};

  if((hp < 155 && megagunPhase == 0) || (hp < 55 && megagunPhase == 1))
  {
    actionState = BAS_MEGAGUN;
    shieldState = BSH_MEGAGUN;
    shieldHealth += 400;
    megagunPhase += 1;
  }

  updateMovement();
  updateShield();

  if(actionState == BAS_MEGAGUN)
  {
    aimAt(0, 2);
    updateMegagun();
    if(megagunTime <= 0){actionState = BAS_NORMAL; shieldState = BSH_ACTIVE; megagunTime = 600; mAnimations[0]->reset(); mAnimations[1]->reset();}
  }
  if(actionState == BAS_NORMAL)
  {
    updateShotgun();
    chargeTimer--;
  }
}

void Boss::updateMegagun()
{
  megagunTime--;
  // animation for opening guns
  if(megagunTime > 120 && megagunTime < 480)
  {
    //speeds 3-5, 5 to 34 shots to angle ratio
      // gun barrel end points: left side: -111, 124 | -119, 93 | -122 62 | -120, 30 | -110, 1 | right side: leftX+296 leftY
    if((megagunTime+20)%60 == 0){megagunVolley( -151, 104, 4, 50, 3, 270 - 22.5);}
    if((megagunTime+40)%60 == 0){megagunVolley( -159, 73, 6, 70, 3, 270 - (22.5/2));}
    if(megagunTime%60 == 0){megagunVolley( -162, 45, 8, 100, 3, 270);}
    if((megagunTime+40)%60 == 0){megagunVolley( -160, 10, 6, 70, 3, 270 + (22.5/2));}
    if((megagunTime+20)%60 == 0){megagunVolley( -150, -21, 4, 50, 3, 270 + 22.5);}

  }
  // animation for closing guns
}

void Boss::megagunVolley(double xloc, double yloc, int shotNumber, double maxAngle, double shotSpeed, double initialAngle)
{
  for(int i = 0; i < shotNumber; i++)
  {
    Vector2D bulletVector(((initialAngle + ((i-(shotNumber/2))*(maxAngle/shotNumber)))-90) * (3.14159265359/180), shotSpeed); //angle and speed of bullet
    objects->push_back(new Bullet(center.x + xloc, yloc + center.y, bulletVector, mDisplay, objects, false, megagunDamage, 1));
    Vector2D bulletVector2((((-initialAngle + 360) + ((i-(shotNumber/2))*(maxAngle/shotNumber)))-90) * (3.14159265359/180), shotSpeed); //angle and speed of bullet
    objects->push_back(new Bullet(center.x - xloc, yloc + center.y, bulletVector2, mDisplay, objects, false, megagunDamage, 1));
  }
}

void Boss::updateMovement()
{
  if(actionState == BAS_NORMAL)
  {
    if((*objects)[playerid]->getX() > center.x){xVel = moveSpeed;}
    else if((*objects)[playerid]->getX() < center.x){xVel = -moveSpeed;}
    chargeTimer--;
    if(chargeTimer <= 0 && shieldRechargeTime < 60)
    {
      actionState = BAS_CHARGE;
      chargeTimer = 600;
    }
  }
  if(actionState == BAS_CHARGE)
  {
    chargePrepTime--;
    xVel = 0;
    if(chargePrepTime == 0)
    {
      if((*objects)[playerid]->getX() > center.x){chargeDirection = 1;} else {chargeDirection = -1;}
    }
    if(chargePrepTime <= 0)
    {
      xVel = chargeDirection * chargeSpeed;
      shieldState = BSH_ATTACK;
    }
    if(x <= leftWall+chargeSpeed || x + width >= rightWall-chargeSpeed)
    {
      xVel = 0;
      actionState = BAS_NORMAL;
      chargePrepTime = 90;
      if(shotgunTime < 60) shotgunTime = 60;
    }
  }
  if(actionState == BAS_MEGAGUN){xVel = 0; yVel = 0;}
  move(xVel, yVel);
}

void Boss::move(double xm, double ym)
{
  if((x > leftWall && xm < 0) || (x < rightWall && xm > 0))
  {
    x += xm; y += ym;
    center.x += xm; center.y += ym;
    shotgunTarget.x += xm; shotgunTarget.y += ym;
  }
}

void Boss::updateShield()
{
  if(shieldState == BSH_ACTIVE)
  {
    shieldHealth++;
    if(shieldHealth > shieldHealthMax) {shieldHealth = shieldHealthMax;}

    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == BULLET && sqrt(pow(center.x - ((*objects)[i]->getX()), 2) + pow(center.y - ((*objects)[i]->getY()), 2)) < shieldRadius)
      {
        (*objects)[i]->kill();
        shieldHealth -= 60;
      }
    }
    if(shieldHealth <= 0)
    {
      shieldState = BSH_DEPLETED;
    }
    else
    {
      if(sqrt(pow(center.x - ((*objects)[playerid]->getX()+8), 2) + pow(center.y - ((*objects)[playerid]->getY()+16), 2)) < 160)
      {
        shieldState = BSH_ATTACK;
      }
    }
  }

  else if(shieldState == BSH_DEPLETED)
  {
    shieldDepletedTime--;
    if(shieldDepletedTime <= 0)
    {
      shieldState = BSH_RECHARGE;
      shieldDepletedTime = 300;
    }
  }

  else if(shieldState == BSH_RECHARGE)
  {
    shieldHealth += 20;
    shieldRechargeTime--;
    if(shieldRechargeTime <= 0)
    {
      shieldRechargeTime = 90;
      shieldState = BSH_ACTIVE;
    }

    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == BULLET && sqrt(pow(center.x - ((*objects)[i]->getX()), 2) + pow(center.y - ((*objects)[i]->getY()), 2)) < shieldRadius)
      {
        (*objects)[i]->kill();
        shieldHealth -= 100;
      }
    }

    if(shieldHealth > shieldHealthMax){shieldHealth = shieldHealthMax;}
    if(shieldHealth < 0){shieldHealth = 0;}
  }

  else if(shieldState == BSH_ATTACK)
  {
    shieldAttackRadius += 5;
    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == BULLET && sqrt(pow(center.x - ((*objects)[i]->getX()), 2) + pow(center.y - ((*objects)[i]->getY()), 2)) < shieldAttackRadius)
      {
        (*objects)[i]->kill();
        shieldHealth -= 100;
      }
    }
    if(sqrt(pow(center.x - ((*objects)[playerid]->getX()+8), 2) + pow(center.y - ((*objects)[playerid]->getY()+16), 2)) < shieldAttackRadius)
    {
      CollisionData cd;

      Player * ptr;
      ptr = dynamic_cast<Player*>((*objects)[playerid]);
      cd.damage = shieldHealth/5;
      if(cd.damage < 20){cd.damage = 20;}
      cd.knockback = 20;
      if(ptr->getX() > center.x){cd.knockback = -20;}
      cd.iframes = 90;

      ptr->damaged(cd);
    }
    if(shieldAttackRadius >= shieldAttackRadiusMax)
    {
      shieldAttackRadius = 0;
      shieldState = BSH_POST_ATTACK;
    }
  }

  else if(shieldState == BSH_POST_ATTACK)
  {
    shieldPostAttackTime--;
    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == BULLET && sqrt(pow(center.x - ((*objects)[i]->getX()), 2) + pow(center.y - ((*objects)[i]->getY()), 2)) < shieldRadius)
      {
        (*objects)[i]->kill();
        shieldHealth -= 100;
      }
    }
    if(sqrt(pow(center.x - ((*objects)[playerid]->getX()+8), 2) + pow(center.y - ((*objects)[playerid]->getY()+16), 2)) < shieldRadius)
    {
      CollisionData cd;

      Player * ptr;
      ptr = dynamic_cast<Player*>((*objects)[playerid]);
      cd.damage = shieldHealth/10;
      if(cd.damage < 10){cd.damage = 10;}
      cd.knockback = 20;
      if(ptr->getX() > center.x){cd.knockback = -20;}
      cd.iframes = 90;

      ptr->damaged(cd);
    }
    if(shieldPostAttackTime <= 0)
    {
      shieldState = BSH_ACTIVE;
      shieldPostAttackTime = 120;
    }
    if(shieldHealth <= 0)
    {
      shieldState = BSH_DEPLETED;
      shieldPostAttackTime = 120;
    }
  }
  else if(shieldState == BSH_MEGAGUN)
  {
    shieldHealth += 6;
    if(shieldHealth > shieldHealthMax) {shieldHealth = shieldHealthMax;}
    if(shieldHealth > 0)
    {
      for(int i = 0; i < objects->size(); i++)
      {
        if((*objects)[i]->getType() == BULLET && (*objects)[i]->getX() > center.x - shieldRadius && (*objects)[i]->getX() < center.x + shieldRadius)
        {
          (*objects)[i]->kill();
          shieldHealth -= 100;
        }
      }
      if((*objects)[playerid]->getX() > center.x - shieldRadius - 15 && (*objects)[playerid]->getX() < center.x + shieldRadius + 15)
      {
        CollisionData cd;

        Player * ptr;
        ptr = dynamic_cast<Player*>((*objects)[playerid]);
        cd.damage = shieldHealth/40;
        if(cd.damage < 10){cd.damage = 10;}
        cd.knockback = 20;
        if(ptr->getX() > center.x){cd.knockback = -20;}
        cd.iframes = 90;

        ptr->damaged(cd);
      }
    }
  }
}

void Boss::updateShotgun()
{
  aimAt(((atan2( center.x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+8)-center.y)) * (180.0/3.14159265359)) + 180, 2);

  if(shotgunTime <= 0)
  {
    if(shotgunVolleyTime <= 0)
    {
      if(shotgunVolley == 0)
      {
        volley(3, 20, 5);
        shotgunVolley++;
        shotgunVolleyTime = 20;
      }
      else if(shotgunVolley == 1)
      {
        volley(4, 27, 4.5);
        shotgunVolley++;
        shotgunVolleyTime = 20;
      }
      else if(shotgunVolley == 2)
      {
        volley(5, 34, 4);
        shotgunVolley++;
        shotgunVolleyTime = 20;
      }
      else if(shotgunVolley == 3)
      {
        volley(6, 41, 3.5);
        shotgunVolley++;
        shotgunVolleyTime = 20;
      }
      else if(shotgunVolley <= 4){shotgunVolleyTime = 10; shotgunVolley = 0; shotgunTime = 300;} // reset times after shooting
    }
    else{shotgunVolleyTime--;}
  }
  else{shotgunTime--;}
}

void Boss::volley(int shotNumber, double maxAngle, double shotSpeed)
{
  for(int i = 0; i < shotNumber; i++)
  {
    Vector2D bulletVector(((shotgunAim + ((i-(shotNumber/2))*(maxAngle/shotNumber)))-90) * (3.14159265359/180), shotSpeed); //angle and speed of bullet
    objects->push_back(new Bullet(shotgunTarget.x, shotgunTarget.y, bulletVector, mDisplay, objects, false, shotgunDamage, 2));
  }
}

bool Boss::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 8)
  {
    if(shieldState == BSH_ACTIVE)
    {
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 100, 255, SDL_ALPHA_OPAQUE);
      if(shieldHealth > 800)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius - (shieldHealth%2));
      }
      if(shieldHealth > 400)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-5 - (shieldHealth%2));
      }
      if(shieldHealth > 0)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-10 - (shieldHealth%2));
      }
    }
    if(shieldState == BSH_RECHARGE)
    {
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 100, 255, SDL_ALPHA_OPAQUE);
      if(shieldHealth > 800)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius - (shieldRechargeTime%4));
      }
      if(shieldHealth > 400)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-5 - (shieldRechargeTime%4));
      }
      if(shieldHealth > 0)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-10 - (shieldRechargeTime%4));
      }
    }
    if(shieldState == BSH_ATTACK)
    {
      int sar = shieldAttackRadius;
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
      if(shieldHealth > 800)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldAttackRadius - ((sar%15)/3));
      }
      if(shieldHealth > 400)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldAttackRadius-5 - ((sar%15)/3));
      }
      if(shieldHealth > 0)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldAttackRadius-10 - ((sar%15)/3));
      }
    }
    if(shieldState == BSH_POST_ATTACK)
    {
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
      if(shieldHealth > 800)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius - (shieldPostAttackTime%2));
      }
      if(shieldHealth > 400)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-5 - (shieldPostAttackTime%2));
      }
      if(shieldHealth > 0)
      {
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, shieldRadius-10 - (shieldPostAttackTime%2));
      }
    }
    if(shieldState == BSH_MEGAGUN)
    {
      double rn1 = randomDouble(-5, 5);
      double rn2 = randomDouble(-5, 5);
      double rn3 = randomDouble(-5, 5);
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
      double yl1 = y + height - cameraY; double yl2 = y - 290 - cameraY;
      if(shieldHealth > 800)
      {
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x - shieldRadius - rn2 - cameraX, yl1, center.x - shieldRadius - rn2 - cameraX, yl2);
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x + shieldRadius + rn2 - cameraX, yl1, center.x + shieldRadius + rn2 - cameraX, yl2);
      }
      if(shieldHealth > 400)
      {
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x - shieldRadius-5 - rn2 - cameraX, yl1, center.x - shieldRadius-5 - rn2 - cameraX, yl2);
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x + shieldRadius-5 + rn2 - cameraX, yl1, center.x + shieldRadius-5 + rn2 - cameraX, yl2);
      }
      if(shieldHealth > 0)
      {
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x - shieldRadius-10 - rn2 - cameraX, yl1, center.x - shieldRadius-10 - rn2 - cameraX, yl2);
        SDL_RenderDrawLine(mDisplay->getRenderer(), center.x + shieldRadius-10 + rn2 - cameraX, yl1, center.x + shieldRadius-10 + rn2 - cameraX, yl2);
      }
    }

    SDL_Point cntr = {8, 8};
    (*textureArray)[TEX_BOSS_BODY]->render(x - cameraX, y - cameraY, 0);
    SDL_Point megagunCenter = {-23, 13};
    if(actionState == BAS_MEGAGUN)
    {
      int timePassed = 600 - megagunTime;

      // door opening animation
      int doorOpenness = timePassed*2;
      if(doorOpenness > 74){doorOpenness = 74;}
      SDL_Rect openDoors1 = {x + 10 - cameraX, y + 28 - cameraY, 6, doorOpenness};
      SDL_Rect openDoors2 = {x + 63 - cameraX, y + 28 - cameraY, 6, doorOpenness};
      if(timePassed < 560)
      {
        SDL_SetRenderDrawColor(mDisplay->getRenderer(),0,0,0,0xFF);
        SDL_RenderFillRect(mDisplay->getRenderer(), &openDoors1);
        SDL_RenderFillRect(mDisplay->getRenderer(), &openDoors2);
      }
      // gun unveiling animation
      if(timePassed > 40 && timePassed < 480)
      {
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 22.5/2, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, -22.5/2, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 22.5, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, -22.5, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 0, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180+(22.5/2), megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180-(22.5/2), megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180+22.5, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180-22.5, megagunCenter);
        mAnimations[0]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180, megagunCenter);
        mAnimations[0]->update();
        (*textureArray)[TEX_BOSS_BODY]->render(x - cameraX, y - cameraY, 1);
      }
      // gun reveiling animation
      if(timePassed >= 480 && timePassed < 560)
      {
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 22.5/2, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, -22.5/2, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 22.5, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, -22.5, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 0, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180+(22.5/2), megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180-(22.5/2), megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180+22.5, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180-22.5, megagunCenter);
        mAnimations[1]->render(center.x + 23, center.y + 32, cameraX, cameraY, SDL_FLIP_NONE, 180, megagunCenter);
        mAnimations[1]->update();
        (*textureArray)[TEX_BOSS_BODY]->render(x - cameraX, y - cameraY, 1);
      }
      if(timePassed >= 560)
      {
        doorOpenness = (600 - timePassed) * 2;
        if(doorOpenness > 74){doorOpenness = 74;}
        if(doorOpenness < 0){doorOpenness = 0;}
        openDoors1 = {x + 10 - cameraX, y + 28 - cameraY, 6, doorOpenness};
        openDoors2 = {x + 63 - cameraX, y + 28 - cameraY, 6, doorOpenness};
        SDL_SetRenderDrawColor(mDisplay->getRenderer(),0,0,0,0xFF);
        SDL_RenderFillRect(mDisplay->getRenderer(), &openDoors1);
        SDL_RenderFillRect(mDisplay->getRenderer(), &openDoors2);
      }
    }
    (*textureArray)[TEX_BOSS_GUN]->render(center.x - 8 - cameraX, center.y - 8 - cameraY, 0, NULL, shotgunAim - 90, &cntr);
    int tmp = x/5; tmp = tmp%4;
    for(int i = 0; i < 6; i++)
    {
      (*textureArray)[TEX_BOSS_WHEEL]->render(x + 1 + (i*13) - cameraX, y + 146 - cameraY, 3-tmp );
    }

    if(BAS_DEAD)
    {
      for(int i = 0; i < deathTime / 10; i++)
      {
        double rn1 = randomDouble(-5, 5);
        SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, deathTime - rn1 + (i * 10));
      }
      SDL_Rect dethrect = {0,0,mDisplay->getWidth(), mDisplay->getHeight()};
      int dtm = std::min(deathTime, 255);
      SDL_SetRenderDrawBlendMode(mDisplay->getRenderer(), SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, dtm);
      SDL_RenderFillRect(mDisplay->getRenderer(), &dethrect);
    }

    return true;
  }
  return false;
}

void Boss::aimAt(double target, double rotateSpeed)
{

  double zerodPangle = target - shotgunAim;

  if(zerodPangle < 0) zerodPangle += 360;
  if(zerodPangle > 360) zerodPangle -= 360;

  if(zerodPangle > rotateSpeed || zerodPangle < -rotateSpeed)
  {
    if(zerodPangle > 180) rotateShotgun(-rotateSpeed);
    else rotateShotgun(rotateSpeed);
  }
}

void Boss::rotateShotgun(double angl) // rotate by angl degrees
{
  rotatePoint(angl, &shotgunTarget, center);
  shotgunAim += angl;
  while(shotgunAim > 360) {if(shotgunAim > 360) {shotgunAim -= 360;}}
  while(shotgunAim < 0) {if(shotgunAim < 0) {shotgunAim += 360;}}
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

void Boss::damaged(int dmg)
{
  hp -= dmg;
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

int Boss::getHP(){return hp;}
int Boss::getShieldHP(){return shieldHealth;}
int Boss::getActionState(){return actionState;}
int Boss::getDeathTime(){return deathTime;}
