#include "Turret.h"

Turret::Turret(){type = TURRET;}
Turret::Turret(int xl, int yl, int cAI, int mAI, Display* display, std::vector<GameObject*>* obj)
{
  objects = obj;
  type = TURRET;
  x = xl;
  y = yl;

  combatAI = cAI;
  movementAI = mAI;

  switch(combatAI)
  {
    case TA_GUN_ACCURATE:
    break;
    case TA_GUN_SEMI_SPREAD:
    shootingAngle = 8;
    shotFrequency = 15;
    break;
    case TA_GUN_FULL_SPREAD:
    shootingAngle = 8;
    shotFrequency = 60;
    break;
  }

  cooldown = shotFrequency;

  cannonTopLeft.x = x - 4;
  cannonTopLeft.y = y - 20;
  cannonTopRight.x = x + 4;
  cannonTopRight.y = y - 20;
  cannonBottomLeft.x = x - 4;
  cannonBottomLeft.y = y - 9;
  cannonBottomRight.x = x + 4;
  cannonBottomRight.y = y - 9;

  mDisplay = display;
}
Turret::~Turret(){}

void Turret::move(double xo, double yo)
{
  x += xo;
  y += yo;
  cannonTopLeft.x += xo;
  cannonTopLeft.y += yo;
  cannonTopRight.x += xo;
  cannonTopRight.y += yo;
  cannonBottomLeft.x += xo;
  cannonBottomLeft.y += yo;
  cannonBottomRight.x += xo;
  cannonBottomRight.y += yo;
}

void Turret::rotate(double angl)
{
  Point p; // this is the centerpoint of rotation
  p.x = x; p.y = y;
  rotatePoint(angl, &cannonTopLeft, p);
  rotatePoint(angl, &cannonTopRight, p);
  rotatePoint(angl, &cannonBottomLeft, p);
  rotatePoint(angl, &cannonBottomRight, p);
  angle += angl;
}

void Turret::handleEvent(SDL_Event* e){}
void Turret::update()
{
  if(hp <= 0) alive = false;

  while(angle > 360){angle -= 360;}
  while (angle <= 0){angle += 360;}
  cooldown -= 1;

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
    CollisionData cd;
    double distanceToPlayer = sqrt(pow(x - (*objects)[playerid]->getX(), 2) + pow(y - (*objects)[playerid]->getY(), 2));
    if(distanceToPlayer > detectionRange) return; // stop doing things if player is too far
    if(movementAI == TM_NOCLIP) turretMove(); // no need to check for line of sight while noclipping
    bool lineofsight = true;
    for(int i2 = 0; i2 < objects->size(); i2++)
    {
      if((*objects)[i2]->getType() == BOUNDARY)
      {
        cd = (*objects)[i2]->lineIntersection(x, y,(*objects)[playerid]->getX() + 8,(*objects)[playerid]->getY() + 16,1,1,1,1); // chekc if turret can see player
        if(cd.intersect)
        {
          lineofsight = false;
          break;
        }
      }
    }

    if(lineofsight) //if player is visible shoot and or rotate turret
    {
      double angleToPlayer = atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+16)-y);
      //radians
      angleToPlayer = angleToPlayer * (180.0/3.14159265359) + 180; // degrees
      std::cout << angleToPlayer << "aiming" <<"\n";

      double zerodPangle = angleToPlayer - angle;

      if(zerodPangle < 0) zerodPangle += 360;

      if(zerodPangle > rotationspeed || zerodPangle < -rotationspeed)
      {
        if(zerodPangle > 180) rotate(-rotationspeed);
        else rotate(rotationspeed);
      }
      else rotate(zerodPangle);

      if(zerodPangle < shootingAngle && zerodPangle > -shootingAngle && cooldown < 1 && lineofsight)
      // might change the 4s to rotation speed or something like that later
      {
        shoot();
      }

      if(movementAI != TM_NOCLIP) turretMove(); // move after checking los, unless TM_NOCLIP since that one is done earlier

    }
  }
}

void Turret::turretMove()
{
  switch(movementAI)
  {
    case TM_STATIONARY:
    break;

    case TM_FLIGHT:
    // flies but not through walls
    {
      Vector2D moveVector((angle-90) * (3.14159265359/180), moveSpeed);
      bool cx, cy;
      cx = collisionCheck(moveVector.x, 0);
      cy = collisionCheck(0, moveVector.y);
      if(!cx && !cy) move(moveVector.x, moveVector.y);
      else if(!cx && cy) move(moveVector.x, 0);
      else if(cx && !cy) move(0, moveVector.y);
    }
    break;

    case TM_NOCLIP:
    // flies and also goes through wall
    {
      double angleToPlayer = atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+16)-y);
      //radians
      angleToPlayer = angleToPlayer * (180.0/3.14159265359) + 180; // degrees
      Vector2D moveVector(x, y, ((*objects)[playerid]->getX()+8), ((*objects)[playerid]->getY()+16), moveSpeed);
      std::cout << angleToPlayer << "movement" <<"\n";
      move(moveVector.x, moveVector.y);
      std::cout << "x: " << x << " y: " << y << "\n";
    }
    break;

    case TM_GROUNDSPIN:
    // moves across the ground, is affected by gravity, and can't move unless in contact with the floor
    break;

  }
}

bool Turret::collisionCheck(double xm, double ym)
{
  if(moveSpeed == 0) return false;
  CollisionData cd;
  for(int i = 0; i < objects->size(); i++)
  {
    Boundary* ptr;
    if((*objects)[i]->getType() == BOUNDARY)
    {
      ptr = dynamic_cast<Boundary*>((*objects)[i]);
      if(xm > 0.0)
      {
        if(ptr->getLeft())
        {
          cd = ptr->lineIntersection(x + radius, y, x + radius + xm, y,0,0,0,0);
          if(cd.intersect) return true;
        }
      }
      else if(xm < 0.0)
      {
        if(ptr->getRight())
        {
          cd = ptr->lineIntersection(x - radius, y, x - radius + xm, y,0,0,0,0);
          if(cd.intersect) return true;
        }
      }
      if(ym > 0.0)
      {
        if(ptr->getUp())
        {
          cd = ptr->lineIntersection(x, y + radius, x, y + radius + ym,0,0,0,0);
          if(cd.intersect) return true;
        }
      }
      else if(ym < 0.0)
      {
        if(ptr->getDown())
        {
          cd = ptr->lineIntersection(x, y - radius, x, y - radius + ym,0,0,0,0);
          if(cd.intersect) return true;
        }
      }
    }
  }
}

void Turret::shoot()
{
  cooldown = shotFrequency;
  int randomInt;
  int randomInt2;
  //shoot
  switch(combatAI)
  {
    case TA_GUN_ACCURATE:
    {
    Vector2D bulletVector((angle-90) * (3.14159265359/180), bulletSpeed);
    objects->push_back(new Bullet(x, y, bulletVector, mDisplay, objects, false, 10, 2));
    }
    break;

    case TA_GUN_SEMI_SPREAD:
    {
    randomInt = rand() % 11 - 5;
    Vector2D bulletVector((angle-90+randomInt ) * (3.14159265359/180), bulletSpeed);
    objects->push_back(new Bullet(x, y, bulletVector, mDisplay, objects, false, 10, 2));
    }
    break;

    case TA_GUN_FULL_SPREAD:
    {
      for(int i = 0; i < 14; i++)
      {
        randomInt = rand() % 31 - 15;
        randomInt2 = rand() % 3 - 1;
        Vector2D bulletVector((angle-90+randomInt) * (3.14159265359/180), bulletSpeed + randomInt2);
        objects->push_back(new Bullet(x, y, bulletVector, mDisplay, objects, false, 10, 2));
      }
    }
    break;
  }
}

void Turret::damaged(CollisionData cd)
{
  int direct = -1;
  hp -= cd.damage;
  if(cd.right) direct = 1;
  //knockedBack(direct, 1);
}

int Turret::getRadius(){return radius;}

bool Turret::render(int cameraX, int cameraY, int priority)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, 10);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonBottomLeft.x - cameraX, cannonBottomLeft.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonBottomRight.x - cameraX, cannonBottomRight.y - cameraY);
  //draw a ball at x, y
  // rotating cannon pipe thing
    //or do the classic: draw 8 lines next to each other version
    // ACTUALLY, I could just use the line rotation thingy from the hazard triangle for this
  return true;
}

CollisionData Turret::lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4)
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
      x3 = x-radius;
      y3 = y-radius;
      x4 = x-radius;
      y4 = y+radius;
    }
    else if(i == 1) // top
    {
      x3 = x-radius;
      y3 = y-radius;
      x4 = x+radius;
      y4 = y-radius;
    }
    else if(i == 2) // bottom
    {
      x3 = x+radius;
      y3 = y+radius;
      x4 = x-radius;
      y4 = y+radius;
    }
    else if(i == 3) // right
    {
      x3 = x+radius;
      y3 = y-radius;
      x4 = x+radius;
      y4 = y+radius;
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
