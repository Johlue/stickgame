#include "Walker.h"

Walker::Walker(){}
Walker::Walker(int o_x, int o_y, int combatAI, int movementAI, Display* disp, std::vector<GameObject*>* objs)
{
  AI = combatAI;
  AIwalk = movementAI;
  objects = objs;
  x = o_x; y = o_y;
  mDisplay = disp;
  width = 20;
  height = 40;
  type = WALKER;
  gunPoint.x = x + (width/2) + 20;
  gunPoint.y = y + (height/5);
}
Walker::~Walker(){}

void Walker::handleEvent(SDL_Event* e){}
void Walker::update()
{
  if(hp <= 0) alive = false;
  while(gunAngle > 360) {gunAngle -= 360;}
  while(gunAngle < 0) {gunAngle += 360;}
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
    }

    if(wallCheck()) direction = direction * (-1);

    if(AIwalk == STANDING) xVel = 0;

    if(detectPlayer()) // look for the player
    {
       playerDetected = true;
       playerMemoryRemaining = playerMemory;
       switch(AI)
       {
         case RANGED:

         if(!((direction == 1 && (*objects)[playerid]->getX()+8 > x) || (direction == -1 && (*objects)[playerid]->getX()+8 < x)))
         {
           direction = direction * -1; // turn around if player is behind
         }
         //radians
         aimAt(((atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+8)-y)) * (180.0/3.14159265359)) + 180 - 90, 4);
         rangedAIshoot();
         break;

         case MELEE:
         //
         break;

       }
    }
    else
    {
      switch(AI)
      {
        int passiveAngle;// row row rowtate your gun
        case RANGED:

        if(!playerDetected) aimAt(90+(-20 * direction), 4); // point gun down if walker is not alert
        else aimAt(90 + (-90 * direction), 4); // point forward if alert

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

    x += xVel * direction;
    gunPoint.x += xVel * direction;
    y += yVel;
    gunPoint.y += yVel * direction;

  }
}
void Walker::render(int cameraX, int cameraY)
{
  SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  SDL_Rect rect3 = {gunPoint.x - cameraX, gunPoint.y - cameraY, 3, 3};
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect3);
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
  if(playerDetected)
  {
    if(std::abs((*objects)[playerid]->getX()+8 - (x+(width/2))) <= detectionRange
        && std::abs((*objects)[playerid]->getY()+16 - (y+(height/6))) <= detectionRange)
    {
      return true;
    }
  }
  // facing the right direction
  if((direction == 1 && (*objects)[playerid]->getX()+8 > x) || (direction == -1 && (*objects)[playerid]->getX()+8 < x))
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
  xVel = 0;
  if(initialShotDelay_t > 0) initialShotDelay_t--; //wait for itinialshot
  else
  {
    if(betweenShotsDelay_t <= 0 && shotsRemaining > 0) // SHOOT!
    {
      Vector2D bulletVector((gunAngle) * (3.14159265359/180), 10); //angle and speed of bullet
      objects->push_back(new Bullet(gunPoint.x, gunPoint.y, bulletVector, mDisplay, objects, false, 4));
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

void Walker::damaged(CollisionData cd)
{
  int direct = -1;
  hp -= cd.damage;
  if(cd.right) direct = 1;
  //knockedBack(direct, 1);
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
  rotatePoint(angl, &gunPoint, p);
  gunAngle += angl;
}
