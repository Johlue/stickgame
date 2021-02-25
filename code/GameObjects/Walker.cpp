#include "Walker.h"

enum walker_anims{WALKER_NORMAL_STAND = 0, WALKER_NORMAL_RUN, WALKER_LARGE_STAND, WALKER_LARGE_RUN, WALKER_SWORD_STILL, WALKER_SWORD_CHARGE, WALKER_SWORD_ATTACK,
  WALKER_BALL_STILL, WALKER_BALL_CHARGE, WALKER_BALL_ATTACK, WALKER_DAGGER_STILL, WALKER_DAGGER_ATTACK};

Walker::Walker(){}
Walker::Walker(int o_x, int o_y, int combatAI, int movementAI, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs, int direct)
{
  direction = direct;
  textureArray = texs;
  AI = combatAI;
  AIwalk = movementAI;
  objects = objs;
  x = o_x; y = o_y;
  mDisplay = disp;
  width = 20;
  height = 38;
  type = WALKER;
  gunPoint.x = x + (width/2) + 20;
  gunPoint.y = y + (height/5);
  gunCenter.x = x + (width/2)+0.5;
  gunCenter.y = y + (height/5)+0.5;

  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay)); // normie guy standing
  mAnimations[WALKER_NORMAL_STAND]->addFrame(TEX_ENEMY_NORMAL_BODY, 0);
  mAnimations.push_back(new Animation(15, true, textureArray, mDisplay)); // normie guy runnin
  mAnimations[WALKER_NORMAL_RUN]->addFrame(TEX_ENEMY_NORMAL_BODY, 1);
  mAnimations[WALKER_NORMAL_RUN]->addFrame(TEX_ENEMY_NORMAL_BODY, 2);
  mAnimations[WALKER_NORMAL_RUN]->addFrame(TEX_ENEMY_NORMAL_BODY, 3);
  mAnimations[WALKER_NORMAL_RUN]->addFrame(TEX_ENEMY_NORMAL_BODY, 4);
  mAnimations[WALKER_NORMAL_RUN]->addFrame(TEX_ENEMY_NORMAL_BODY, 5);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay)); // Big guy standing
  mAnimations[WALKER_LARGE_STAND]->addFrame(TEX_ENEMY_LARGE_BODY, 0);
  mAnimations.push_back(new Animation(15, true, textureArray, mDisplay));  // Big guy walkin
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 1);
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 2);
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 3);
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 4);
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 5);
  mAnimations[WALKER_LARGE_RUN]->addFrame(TEX_ENEMY_LARGE_BODY, 6);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_SWORD_STILL]->addFrame(TEX_ENEMY_SWORD_HAND, 0);
  mAnimations.push_back(new Animation(3, false, textureArray, mDisplay));
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 1);
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 2);
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 3);
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 4);
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 5);
  mAnimations[WALKER_SWORD_CHARGE]->addFrame(TEX_ENEMY_SWORD_HAND, 6);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_SWORD_ATTACK]->addFrame(TEX_ENEMY_SWORD_HAND, 7);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_BALL_STILL]->addFrame(TEX_ENEMY_BALL_HAND, 0);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_BALL_CHARGE]->addFrame(TEX_ENEMY_BALL_HAND, 1);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_BALL_ATTACK]->addFrame(TEX_ENEMY_BALL_HAND, 2);
  mAnimations.push_back(new Animation(15, false, textureArray, mDisplay));
  mAnimations[WALKER_DAGGER_STILL]->addFrame(TEX_ENEMY_DAGGER_HAND, 0);
  mAnimations.push_back(new Animation(20, false, textureArray, mDisplay));
  mAnimations[WALKER_DAGGER_ATTACK]->addFrame(TEX_ENEMY_DAGGER_HAND, 1);
  mAnimations[WALKER_DAGGER_ATTACK]->addFrame(TEX_ENEMY_DAGGER_HAND, 2);

  if(AI == MELEE)
  {
    meleeCooldown = 1;
    meleeTell = 20;
    meleeAttack = 20;
    hp = 60;
  }
  else if(AI == MELEE_QUICK)
  {
    meleeAttack = 0;
    meleeCooldown = 10;
    combatSpeed = 3.5;
    meleeRange = 60;
    hp = 40;
  }
  else if(AI == MELEE_STRONG)
  {
    meleeAttack = 180;
    meleeCooldown = 1;
    meleeTell = 90;
    meleeRange = 999360;
    width = 30;
    height = 60;
    hp = 120;
    moveSpeed = 1;
  }
  else if(AI == RANGED)
  {
    initialShotDelay = 60;
    betweenShotsDelay = 20;
    clipSize = 4;
    reloadSpeed = 60;
    damage = 26;
    hp = 50;
    gunSpread = 0;
  }
  else if(AI == RANGED_QUICK)
  {
    initialShotDelay = 30;
    betweenShotsDelay = 4;
    clipSize = 16;
    reloadSpeed = 90;
    damage = 26;
    hp = 30;
    gunSpread = 2;
  }
  else if(AI == RANGED_MINIGUN)
  {
    width = 30;
    height = 60;
    initialShotDelay = 10;
    betweenShotsDelay = 0;
    clipSize = 9999;
    reloadSpeed = 1;
    damage = 52;
    hp = 100;
    gunSpread = 10;
    gunPoint.x = x + (width/2) + 20;
    gunPoint.y = y + 34;
    gunCenter.x = x + (width/2);
    gunCenter.y = y + 34;
  }
  else if(AI == RANGED_HYPERBEAM){}
  initialShotDelay_t = initialShotDelay;
  reloadSpeed_t = reloadSpeed;
  shotsRemaining = clipSize;
}
Walker::~Walker()
{
  for(int i = 0; i < mAnimations.size(); i++)
  {
    delete mAnimations[i];
    mAnimations[i] = nullptr;
  }
  mAnimations.clear();
}

void Walker::handleEvent(SDL_Event* e){}
void Walker::update()
{

  if(hp <= 0) alive = false;

  minigunSpin += minigunSpinSpeed;
  if(minigunSpin > 180)
  {
    minigunSpin = 0;
    if(minigunFrame == 0) {minigunFrame = 1;}
    else {minigunFrame = 0;}
  }

  if(flinched > 0)
  {
    flinched--;
  }


  if(meleeTellRemaining > 0) meleeTellRemaining--;
  if(meleeCooldownRemaining > 0 && meleeAttackRemaining <= 0) meleeCooldownRemaining--;
  if(meleeAttackRemaining > 0) meleeAttackRemaining--;

  //std::cout << "mTell: " << meleeTellRemaining << " mAtt: " << meleeAttackRemaining << " mCool: " << meleeCooldownRemaining << std::endl;

  while(gunAngle > 360) {gunAngle -= 360;}
  while(gunAngle < 0) {gunAngle += 360;}
  // check if playerid is valid, if not fix it
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

    double playerCenterX = (*objects)[playerid]->getX() - 8;
    double playerCenterY = (*objects)[playerid]->getY() - 16;

    if(!falling)
    {
      if(fallingCheck()) falling = true;
    }
    if(falling && yVel < 5) yVel += .15;


    if(falling) fallingCollisionCheck();
    if(!falling && flinched < 1)
    {
      xVel = moveSpeed;
      if(playerMemoryRemaining > 0)
      {
        xVel = combatSpeed; // move at combat speed if player is in line of sight
        if(jumping) xVel = jumpSpeed; // jump speed if jumping
      }
      if(direction < 0) xVel = -xVel;

      if(floorBeneath != nullptr)
      {
        if(floorEndCheck())
        {
          // check if you should turn around and then do turn around if you should turn around (depening on AI type)
          switch(AIwalk)
          {
            case WAIT: // if waiting type wait at edge for 2 seconds
            if(waiting < 1) waiting = 120;
            break;

            case INSTANTTURN: // turn around now
            direction = direction * (-1);
            break;

            case STANDING: // don't move nothing bad is going to happen
            break;
          }
        }
      }
      if(AIwalk == WAIT) // waiters need to wait
      {
        waiting--;
        if(waiting == 1)
        {
          direction = direction * -1; // after the waiting is over turn around
        } else if(waiting > 1) xVel = 0;
      }

      if(AIwalk == STANDING)
      {
        xVel = 0;
      }
      if(detectPlayer()) // look for the player
      {
        if(minigunSpinSpeed < 180){minigunSpinSpeed += 1;}

         playerDetected = true;
         playerMemoryRemaining = playerMemory;
         switch(AI)
         {
           case RANGED:
           case RANGED_QUICK:

           if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2))))
           {
             direction = direction * -1; // turn around if player is behind
           }
           //radians
           aimAt(((atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+8)-y)) * (180.0/3.14159265359)) + 180 - 90, 4);
           rangedAIshoot();
           break;

           case RANGED_MINIGUN:
            if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2))))
            {
              direction = direction * -1; // turn around if player is behind
            }
            aimAt(90 + (-90 * direction), 180);
            if(minigunSpinSpeed > 178){rangedAIshoot();}
            break;

           case MELEE:
           if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2)))
            && meleeTellRemaining < 1 && meleeAttackRemaining < 1
            && !falling && flinched < 1)
           {
             direction = direction * -1; // turn around if player is behind
           }

           //if at melee range do an attack
           meleeAttackSlow();
           break;

           case MELEE_STRONG:
           if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2)))
            && meleeTellRemaining < 1 && meleeAttackRemaining < 1
            && !falling && flinched < 1)
           {
             direction = direction * -1; // turn around if player is behind
           } //TODO: some kind of delay me thinks

           //if at melee range do an attack
           meleeAttackSlow();
           break;

           case MELEE_QUICK:
           if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2)))
            && meleeTellRemaining < 1 && meleeAttackRemaining < 1
            && !falling && flinched < 1)
            {
              if(!falling) direction = direction * -1; // turn if player behind, while not midair
            }
            meleeAttackQuick();

           break;

         }
      }
      else
      {
        if(minigunSpinSpeed > 0) {minigunSpinSpeed--;}
        switch(AI)
        {
          int passiveAngle;// row row rowtate your gun
          case RANGED:
          case RANGED_QUICK:

          if(!playerDetected) aimAt(90+(-20 * direction), 4); // point gun down if walker is not alert
          else aimAt(90 + (-90 * direction), 4); // point forward if alert
          break;

          case RANGED_MINIGUN:
          case RANGED_HYPERBEAM:

          aimAt(90 + (-90 * direction), 180);
          break;

          case MELEE:
          if(meleeAttackInitiated) meleeAttackSlow();
          break;
        }
        if(playerDetected)// if player was seen earlier and can't now, start forgetting
        {
          playerMemoryRemaining--;
          //std::cout << "remaining memory: " << playerMemoryRemaining << std::endl;
          if(playerMemoryRemaining < 1)
          {
            playerDetected = false;
            //std::cout << "player forgotten" << std::endl;
          }
        }
        else
        {
          initialShotDelay_t = initialShotDelay; //reset shotdelay due to lack of preparedness
        }
      }
    }

    if(flinched < 1 && AI == MELEE_QUICK && jumping && meleeAttackInitiated)
    {
      meleeAttackQuick();
    }

    if(wallCheck())
    {
      if(playerMemoryRemaining < 540) direction = direction * (-1); // can't see player, turn around
      else xVel = 0; // can see player, just wait
    }




    if(!falling && (meleeAttackRemaining > 0 || meleeTellRemaining > 0) && (AI == MELEE || AI == MELEE_STRONG))
    {
      xVel = 0;
    }

    x += xVel;
    gunPoint.x += xVel;
    gunCenter.x += xVel;
    y += yVel;
    gunPoint.y += yVel;
    gunCenter.y += yVel;

  }
}
bool Walker::render(int cameraX, int cameraY, int priority)
{
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Point center1 = {10, 12};
  if(direction == -1)
  {
    flip = SDL_FLIP_HORIZONTAL;
    center1 = {33 - 10, 12};
  }


  // Body graphics
  bool largeWalker = false;
  if(AI == MELEE_STRONG || AI == RANGED_MINIGUN){largeWalker = true;}

  if(!closeEnough(0, xVel) && !falling)
  {
    if(largeWalker)
    {
      mAnimations[WALKER_LARGE_RUN]->render(x, y, cameraX, cameraY, flip);
      mAnimations[WALKER_LARGE_RUN]->update();
    }
    else
    {
      mAnimations[WALKER_NORMAL_RUN]->render(x, y, cameraX, cameraY, flip);
      mAnimations[WALKER_NORMAL_RUN]->update();
    }

  }
  else
  {
    if(largeWalker)
    {
      mAnimations[WALKER_LARGE_STAND]->render(x, y, cameraX, cameraY, flip);
      mAnimations[WALKER_LARGE_STAND]->update();
      mAnimations[WALKER_LARGE_RUN]->reset();
    }
    else
    {
      mAnimations[WALKER_NORMAL_STAND]->render(x, y, cameraX, cameraY, flip);
      mAnimations[WALKER_NORMAL_STAND]->update();
      mAnimations[WALKER_NORMAL_RUN]->reset();
    }
  }

  // Weapon Graphics
  switch(AI)
  {
    case RANGED:
    if(flip == SDL_FLIP_NONE){(*textureArray)[TEX_ENEMY_PISTOL_HAND]->render(x - cameraX, y - cameraY, 0, NULL, gunAngle, &center1, flip);}
    else{(*textureArray)[TEX_ENEMY_PISTOL_HAND]->render(x - 13 - cameraX, y - cameraY, 0, NULL, gunAngle - 180, &center1, flip);}
    break;

    case RANGED_MINIGUN:
    (*textureArray)[TEX_ENEMY_MINIGUN_HAND]->render(x - 10 - cameraX, y - cameraY, minigunFrame, NULL, NULL, NULL, flip);
    break;

    case RANGED_QUICK:
    if(flip == SDL_FLIP_NONE){(*textureArray)[TEX_ENEMY_SMG_HAND]->render(x - cameraX, y - cameraY, 0, NULL, gunAngle, &center1, flip);}
    else{(*textureArray)[TEX_ENEMY_SMG_HAND]->render(x - 13 - cameraX, y - cameraY, 0, NULL, gunAngle - 180, &center1, flip);}
    break;

    case MELEE:
    if(meleeTellRemaining < 1 && meleeAttackRemaining < 1)
    {
      mAnimations[WALKER_SWORD_STILL]->render(x - 10, y - 20, cameraX, cameraY, flip);
      mAnimations[WALKER_SWORD_STILL]->update();
      mAnimations[WALKER_SWORD_ATTACK]->reset();
      mAnimations[WALKER_SWORD_CHARGE]->reset();
    }
    else if(meleeTellRemaining > 0)
    {

      mAnimations[WALKER_SWORD_CHARGE]->render(x - 10, y - 20, cameraX, cameraY, flip);
      mAnimations[WALKER_SWORD_CHARGE]->update();
    }
    else if(meleeAttackRemaining > 0)
    {

      mAnimations[WALKER_SWORD_ATTACK]->render(x - 10, y - 20, cameraX, cameraY, flip);
      mAnimations[WALKER_SWORD_ATTACK]->update();
      mAnimations[WALKER_SWORD_CHARGE]->reset();
    }
    break;

    case MELEE_STRONG:
    if(meleeTellRemaining < 1 && meleeAttackRemaining < 1)
    {
      mAnimations[WALKER_BALL_STILL]->render(x - 15, y, cameraX, cameraY, flip);
      mAnimations[WALKER_BALL_STILL]->update();
      mAnimations[WALKER_BALL_ATTACK]->reset();
      mAnimations[WALKER_BALL_CHARGE]->reset();
    }
    else if(meleeTellRemaining > 0)
    {

      mAnimations[WALKER_BALL_CHARGE]->render(x - 15, y, cameraX, cameraY, flip);
      mAnimations[WALKER_BALL_CHARGE]->update();
    }
    else if(meleeAttackRemaining > 0)
    {

      mAnimations[WALKER_BALL_ATTACK]->render(x - 15, y, cameraX, cameraY, flip);
      mAnimations[WALKER_BALL_ATTACK]->update();
      mAnimations[WALKER_BALL_CHARGE]->reset();
    }
    break;

    case MELEE_QUICK:
    if(meleeAttackInitiated){mAnimations[WALKER_DAGGER_ATTACK]->reset();}
    if(!jumping)
    {
      mAnimations[WALKER_DAGGER_STILL]->render(x - 10, y, cameraX, cameraY, flip);
      mAnimations[WALKER_DAGGER_STILL]->update();
      mAnimations[WALKER_DAGGER_ATTACK]->reset();
    }
    else
    {

      mAnimations[WALKER_DAGGER_ATTACK]->render(x - 10, y, cameraX, cameraY, flip);
      mAnimations[WALKER_DAGGER_ATTACK]->update();
    }
    break;

  }
  /*
  SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  if(meleeTellRemaining > 0) SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);
  if(meleeAttackRemaining > 0) SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 255, 0xFF);
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  SDL_Rect rect3 = {gunPoint.x - cameraX, gunPoint.y - cameraY, 3, 3};
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect3);*/
  return true;
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
              jumping = false; // if you're not falling then you're not jumping
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
      if(yVel > 0)
      {
        if(ptr->getUp())
        {
          // left corner
          cd = ptr->lineIntersection(x, y + height - 1, x, y + height + yVel,0,0,0,0);
          if(cd.intersect)
          {
            yVel = 0;
            y = ptr->getY() - height;
            falling = false;
            floorBeneath = ptr;
            return;
          }
          // right corner
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
      else if(yVel < 0)
      {
        if(ptr->getDown())
        {
          // left corner
          cd = ptr->lineIntersection(x, y + height - 1, x, y + yVel,0,0,0,0);
          if(cd.intersect)
          {
            yVel = 0;
            y = ptr->getY();
            return;
          }
          // right corner
          cd = ptr->lineIntersection(x + width, y + height - 1, x + width, y + yVel,0,0,0,0);
          if(cd.intersect)
          {
            yVel = 0;
            y = ptr->getY();
            return;
          }
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
        if(xVel > 0)
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
        else if(xVel < 0)
        {
          if(ptr->getRight())
          {
            cd = ptr->lineIntersection(x + 1, y, x + xVel - 1, y,0,0,0,0);
            if(cd.intersect)
            {
              return true;
            }
            cd = ptr->lineIntersection(x + 1, y + height - 1, x + xVel - 1, y + height - 1 ,0,0,0,0);
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
  // check for walls in line of sight
  CollisionData cd;
  for(int i = 0; i < objects->size(); i++)
  {
    if((*objects)[i]->getType() == BOUNDARY)
    {
      if((*objects)[i]->lineIntersection(x + width/2, y + height / 6, (*objects)[playerid]->getX() +8,
      (*objects)[playerid]->getY()+16,0,0,0,0).intersect)
      {
        return false;
      }
    }
  }
  // ignore direction if player already detected
  // also double detection range
  if(playerDetected)
  {
    if(std::abs((*objects)[playerid]->getX()+8 - (x+(width/2))) <= detectionRange * 2
        && std::abs((*objects)[playerid]->getY()+16 - (y+(height/6))) <= detectionRange * 2)
    {
      return true;
    }
  }
  // facing the right direction
  if((direction == 1 && (*objects)[playerid]->getX()+8 > x + (width/2)) || (direction == -1 && (*objects)[playerid]->getX()+8 < x + (width/2)))
  {
     // 45 degrees or less angle
    if(std::abs((*objects)[playerid]->getY()+16 - y) < std::abs((*objects)[playerid]->getX()+8 - x + (width/2)))
    {
      // is player close enough
      if(std::abs((*objects)[playerid]->getX()+8 - (x+(width/2))) <= detectionRange
        && std::abs((*objects)[playerid]->getY()+16 - (y+(height/6))) <= detectionRange)
      {
        return true;
      }
    }
  }
  return false;
}

void Walker::rangedAIshoot()
{
  if(flinched > 0) return;
  if(!falling) xVel = 0;
  if(initialShotDelay_t > 0) initialShotDelay_t--; //wait for itinialshot
  else
  {
    if(betweenShotsDelay_t <= 0 && shotsRemaining > 0) // SHOOT!
    {
      Vector2D bulletVector((gunAngle) * (3.14159265359/180) +
      randomDouble(-gunSpread * (3.14159265359/180), gunSpread * (3.14159265359/180)), 10); //angle and speed of bullet
      objects->push_back(new Bullet(gunPoint.x, gunPoint.y, bulletVector, mDisplay, objects, false, damage, 1));
      shotsRemaining--; // one less bullet
      betweenShotsDelay_t = betweenShotsDelay; // reset shotdelay
    }
    else if(shotsRemaining > 0) betweenShotsDelay_t--;
    else if(shotsRemaining <= 0)
    {
      // if no shots are remaining start reloading, no animation cause I'm lazy
      reloadSpeed_t--;
      if(reloadSpeed_t < 0)
      {
        // once reload is finished add shots back and reset reload time
        shotsRemaining = clipSize;
        reloadSpeed_t = reloadSpeed;
      }
    }
  }
}

void Walker::meleeAttackSlow()
{
  if(flinched > 0) return;
  if( (abs(((*objects)[playerid]->getX()+8) - (x + (width/2))) < meleeRange && // within melee range
  abs(((*objects)[playerid]->getY()+16) - (y + (height/2))) < 100) || meleeAttackInitiated )
  {
    if(meleeCooldownRemaining <= 0) //do nothing if melee attack is on cooldown
    {
      if(meleeTellRemaining < 1)
      {
        // start melee tell animation
        meleeTellRemaining = meleeTell;
        meleeAttackInitiated = true; // start of melee attack
      }
      else if(meleeTellRemaining == 1) // attack if meleeTell has reached its end
      {
        if(meleeAttackRemaining == 0)
        {
          meleeCooldownRemaining = meleeCooldown;
          meleeAttackRemaining = meleeAttack;
          int slashXMod;
          // start melee attack
          if(AI == MELEE_STRONG)
          {
            objects->push_back(new Slash(&x, &y, -10, (height/2) - (40/2), 34, 34, direction, false, objects, mDisplay, textureArray, S_FLAIL, 200)); // height/2 - slashHeight/2 actually
            meleeAttackInitiated = false; // end of melee attack
          }
          else
          {
            if(direction == -1) slashXMod = 13 - width; // -slashwidth actually
            else  slashXMod = width -3;
            objects->push_back(new Slash(&x, &y, slashXMod, -5, width/2, height, direction, false, objects, mDisplay, textureArray)); // height/2 - slashHeight/2 actually
            meleeAttackInitiated = false; // end of melee attack
          }
        }
      }
    }
    if(!falling) xVel = 0; //also don't move, at least for the normal melee AI
  }
}

void Walker::meleeAttackQuick()
{
  if(flinched > 0) return;
  if( (abs(((*objects)[playerid]->getX()+8) - (x + (width/2))) < quickMeleeRange && // within jump range
  abs(((*objects)[playerid]->getY()+16) - (y + (height/2))) < 100) || meleeAttackInitiated )
  {
    if(!jumping)
    {
      // if not jumping and close enough to player start jump
      jumping = true;
      falling = true;
      yVel = -2.3;
      meleeAttackInitiated = true;
      mAnimations[WALKER_DAGGER_ATTACK]->reset();
    }
    if((abs(((*objects)[playerid]->getX()+8) - (x + (width/2))) < meleeRange &&
      meleeAttackInitiated && jumping))
    {
      int slashXMod;
      if(direction == -1) slashXMod = -3 - width; // -slashwidth actually
      else  slashXMod = width + 3;
      objects->push_back(new Slash(&x, &y, slashXMod, (height/2) - (height/4), width, height/2, direction, false, objects, mDisplay, textureArray)); // height/2 - slashHeight/2 actually
      meleeAttackInitiated = false; // end of melee attack
    }
  }
}

void Walker::damaged(CollisionData cd)
{
  playerDetected = true;
  playerMemoryRemaining = playerMemory; // getting shot is fairly noticable after all
  hp -= cd.damage;
  knockedBack(cd.knockback, cd.damage);
}

void Walker::knockedBack(int knockback, int dmg)
{
  if(AI == MELEE_STRONG || AI == RANGED_MINIGUN){return;}
  falling = true;
  flinched = dmg;
  xVel = -knockback;
  yVel = -1 - (std::abs(knockback) * .3);
  y -= 2;
  gunPoint.y -= 2;
  gunCenter.y -= 2;
}

void Walker::aimAt(double target, double rotateSpeed)
{

  double zerodPangle = target - gunAngle;

  if(zerodPangle < 0) zerodPangle += 360;

  if(zerodPangle > rotateSpeed || zerodPangle < -rotateSpeed)
  {
    if(zerodPangle > 180) rotate(-rotateSpeed);
    else rotate(rotateSpeed);
  }
  else rotate(zerodPangle);
}

void Walker::rotate(double angl) // rotate by angl degrees
{
  int w1 = (width/2)+0.5; int h1 = (height/5)+0.5;
  Point p; // this is the centerpoint of rotation
  p.x = x + w1; p.y = y + h1;
  rotatePoint(angl, &gunPoint, gunCenter);
  gunAngle += angl;
}


CollisionData Walker::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
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

int Walker::activateThisObject(bool on){}
