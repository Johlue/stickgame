#include "Turret.h"

Turret::Turret(){type = TURRET;}
Turret::Turret(int xl, int yl, int cAI, int mAI, Display* display, std::vector<GameObject*>* obj, bool oinvincible, int ohp, bool activ)
{
  objects = obj;
  type = TURRET;
  x = xl;
  y = yl;

  activated = activ;

  combatAI = cAI;
  movementAI = mAI;

  hp = ohp;
  invincible = oinvincible;
  maxHP = hp;

  switch(combatAI)
  {
    case TA_GUN_ACCURATE:
    cannonTopLeft.x = x - 3;
    cannonTopLeft.y = y - 24;
    cannonTopRight.x = x + 3;
    cannonTopRight.y = y - 24;
    cannonBottomLeft.x = x - 3;
    cannonBottomLeft.y = y - 10;
    cannonBottomRight.x = x + 3;
    cannonBottomRight.y = y - 10;

    bulletSpawn.x = x;
    bulletSpawn.y = y - 18;

    distanceFromPlayer = 140;
    break;
    case TA_GUN_SEMI_SPREAD:
    shootingAngle = 8;
    shotFrequency = 15;

    cannonTopLeft.x = x - 4;
    cannonTopLeft.y = y - 20;
    cannonTopRight.x = x + 4;
    cannonTopRight.y = y - 20;
    cannonBottomLeft.x = x - 4;
    cannonBottomLeft.y = y - 9;
    cannonBottomRight.x = x + 4;
    cannonBottomRight.y = y - 9;

    cannonBottomMiddle.x = x;
    cannonBottomMiddle.y = y - 10;
    cannonTopMiddle.x = x;
    cannonTopMiddle.y = cannonTopRight.y;

    bulletSpawn.x = x;
    bulletSpawn.y = y - 12;

    distanceFromPlayer = 120;
    break;
    case TA_GUN_FULL_SPREAD:
    shootingAngle = 8;
    shotFrequency = 60;

    cannonTopLeft.x = x - 8;
    cannonTopLeft.y = y - 19;
    cannonTopRight.x = x + 8;
    cannonTopRight.y = y - 19;
    cannonBottomLeft.x = x - 6;
    cannonBottomLeft.y = y - 8;
    cannonBottomRight.x = x + 6;
    cannonBottomRight.y = y - 8;

    bulletSpawn.x = x;
    bulletSpawn.y = y - 12;

    distanceFromPlayer = 90;
    break;

    case TA_BEYBLADE:
    cannonTopMiddle.x = x;
    cannonTopMiddle.y = y - (bladeRadius);
    cannonBottomLeft.x = x - 4;
    cannonBottomLeft.y = y - 9;
    cannonBottomRight.x = x + 4;
    cannonBottomRight.y = y - 9;

    distanceFromPlayer = 10;
    break;
  }


  cooldown = shotFrequency;

  prepareCrackGraphics();

  mDisplay = display;
}
Turret::~Turret(){}

void Turret::prepareCrackGraphics()
{
  Point p; // this is the centerpoint of rotation
  p.x = x; p.y = y;

  crack1_1.x = x;
  crack1_1.y = y - radius + 1;
  crack1_2.x = x;
  crack1_2.y = y - radius + 4;
  crack1_3.x = x - 3;
  crack1_3.y = y - radius + 8;
  crack1_4.x = x + 5;
  crack1_4.y = y - radius + 6;
  crack2_1.x = x;
  crack2_1.y = y - radius;
  rotatePoint(120, &crack2_1, p);
  crack2_2.x = x + 2;
  crack2_2.y = y - radius + 5;
  rotatePoint(120, &crack2_2, p);
  crack2_3.x = x - 5;
  crack2_3.y = y - radius + 8;
  rotatePoint(120, &crack2_3, p);
  crack2_4.x = x + 7;
  crack2_4.y = y - radius + 7;
  rotatePoint(120, &crack2_4, p);
  crack3_1.x = x;
  crack3_1.y = y - radius;
  rotatePoint(240, &crack3_1, p);
  crack3_2.x = x;
  crack3_2.y = y - radius + 3;
  rotatePoint(240, &crack3_2, p);
  crack3_3.x = x - 4;
  crack3_3.y = y - radius + 6;
  rotatePoint(240, &crack3_3, p);
}

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
  cannonTopMiddle.x += xo;
  cannonTopMiddle.y += yo;
  cannonBottomMiddle.x += xo;
  cannonBottomMiddle.y += yo;

  bulletSpawn.x += xo;
  bulletSpawn.y += yo;

  crack1_1.x += xo;
  crack1_1.y += yo;
  crack1_2.x += xo;
  crack1_2.y += yo;
  crack1_3.x += xo;
  crack1_3.y += yo;
  crack1_4.x += xo;
  crack1_4.y += yo;
  crack2_1.x += xo;
  crack2_1.y += yo;
  crack2_2.x += xo;
  crack2_2.y += yo;
  crack2_3.x += xo;
  crack2_3.y += yo;
  crack2_4.x += xo;
  crack2_4.y += yo;
  crack3_1.x += xo;
  crack3_1.y += yo;
  crack3_2.x += xo;
  crack3_2.y += yo;
  crack3_3.x += xo;
  crack3_3.y += yo;
}

void Turret::rotate(double angl)
{
  Point p; // this is the centerpoint of rotation
  p.x = x; p.y = y;
  rotatePoint(angl, &cannonTopLeft, p);
  rotatePoint(angl, &cannonTopRight, p);
  rotatePoint(angl, &cannonBottomLeft, p);
  rotatePoint(angl, &cannonBottomRight, p);
  rotatePoint(angl, &cannonBottomMiddle, p);
  rotatePoint(angl, &cannonTopMiddle, p);
  rotatePoint(angl, &bulletSpawn, p);
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
    if(combatAI == TA_BEYBLADE) shoot();

    CollisionData cd;
    double distanceToPlayer = sqrt(pow(x - (*objects)[playerid]->getX(), 2) + pow(y - (*objects)[playerid]->getY(), 2));
    if(distanceToPlayer > detectionRange) return; // stop doing things if player is too far

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

    turretMove(distanceToPlayer, lineofsight); // prelos movement

    if(lineofsight && activated) //if player is visible shoot and or rotate turret
    {
      double angleToPlayer = atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+16)-y);
      //radians
      angleToPlayer = angleToPlayer * (180.0/3.14159265359) + 180; // degrees

      double zerodPangle = angleToPlayer - angle;

      if(zerodPangle < 0) zerodPangle += 360;

      if(zerodPangle > rotationspeed || zerodPangle < -rotationspeed)
      {
        if(zerodPangle > 180) rotate(-rotationspeed);
        else rotate(rotationspeed);
      }
      else rotate(zerodPangle);

      if(zerodPangle < shootingAngle && zerodPangle > -shootingAngle && cooldown < 1 && lineofsight && combatAI != TA_BEYBLADE)
      // might change the 4s to rotation speed or something like that later
      {
        shoot();
      }
    }
  }
}

void Turret::turretMove(double distanceToPlayer, bool los)
{
  switch(movementAI)
  {
    case TM_STATIONARY:
    // does not move at all
    break;

    case TM_FLIGHT:
    // flies but not through walls
    if(los && activated)
    {
      Vector2D moveVector((angle-90) * (3.14159265359/180), moveSpeed);
      bool cx, cy;
      if(distanceToPlayer > distanceFromPlayer)
      {
        cx = collisionCheck(moveVector.x, 0);
        cy = collisionCheck(0, moveVector.y);
        if(!cx && !cy) move(moveVector.x, moveVector.y);
        else if(!cx && cy) move(moveVector.x, 0);
        else if(cx && !cy) move(0, moveVector.y);
      }
    }
    break;

    case TM_NOCLIP:
    // flies and also goes through wall
    {
      if(activated)
      {
        double angleToPlayer = atan2( x-((*objects)[playerid]->getX() +8) , ((*objects)[playerid]->getY()+16)-y);
        //radians
        angleToPlayer = angleToPlayer * (180.0/3.14159265359) + 180; // degrees
        Vector2D moveVector(x, y, ((*objects)[playerid]->getX()+8), ((*objects)[playerid]->getY()+16), moveSpeed);
        if(distanceToPlayer > distanceFromPlayer) move(moveVector.x, moveVector.y);
        else if(distanceToPlayer > distanceFromPlayer - 2);
        else move(-moveVector.x, -moveVector.y);
      }
    }
    break;

    case TM_GROUNDSPIN:
    // moves across the ground, is affected by gravity, and can't move unless in contact with the floor
    if(!collisionCheck(0, -1))
    {
      falling = true;
    }
    if(falling)
    {
      fallVelocity += .06;
    }

    Vector2D moveVector(x, y, x+velocity, y+fallVelocity);
    bool cx, cy;
    cx = collisionCheck(moveVector.x, 0);
    cy = collisionCheck(0, moveVector.y);

    if(cx) // if colliding with surface reverse direction and decrease speed
    {
      velocity = (-velocity * 0.6);
      if(velocity > -0.1 && velocity < 0.1) velocity = 0;
    }
    if(cy)
    {
      fallVelocity = (-fallVelocity * 0.6);
      if(fallVelocity > -0.1 && fallVelocity < 0.1) fallVelocity = 0;
    }
    else falling = true;

    if(fallVelocity == 0) falling = false;

    if(!los || !activated) // if player isn't seen slow down
    {
      if(velocity < -0.1) velocity += 0.05;
      else if(velocity > 0.1) velocity -= 0.05;
      else velocity = 0;
    }
    else if(!falling || cy) // while in contact with the ground accelerate towards the player
    {
      if(((*objects)[playerid]->getX()+8) > x) velocity += 0.1;
      else if(((*objects)[playerid]->getX()+8) < x) velocity -= 0.1;
    }

    // no going faster than allowed
    if(velocity > maxVelocity) velocity = maxVelocity;
    if(fallVelocity > maxFallVelocity) fallVelocity = maxFallVelocity;

    move(velocity, fallVelocity);
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
  if(!activated) {return;}
  cooldown = shotFrequency;
  int randomInt;
  int randomInt2;
  //shoot
  switch(combatAI)
  {
    case TA_GUN_ACCURATE:
    {
    Vector2D bulletVector((angle-90) * (3.14159265359/180), bulletSpeed);
    objects->push_back(new Bullet(bulletSpawn.x, bulletSpawn.y, bulletVector, mDisplay, objects, false, damage, knockback));
    }
    break;

    case TA_GUN_SEMI_SPREAD:
    {
    randomInt = rand() % 11 - 5;
    Vector2D bulletVector((angle-90+randomInt ) * (3.14159265359/180), bulletSpeed);
    objects->push_back(new Bullet(bulletSpawn.x, bulletSpawn.y, bulletVector, mDisplay, objects, false, damage, knockback));
    }
    break;

    case TA_GUN_FULL_SPREAD:
    {
      for(int i = 0; i < 14; i++)
      {
        randomInt = rand() % 31 - 15;
        randomInt2 = rand() % 3 - 1;
        Vector2D bulletVector((angle-90+randomInt) * (3.14159265359/180), bulletSpeed + randomInt2);
        objects->push_back(new Bullet(bulletSpawn.x, bulletSpawn.y, bulletVector, mDisplay, objects, false, 10, 2));
      }
    }
    break;

    case TA_BEYBLADE:
    {
      bool hit = false;
      CollisionData cd;
      double pcx = (*objects)[playerid]->getX();
      double pcy = (*objects)[playerid]->getY();
      //intersection check between blade center to player center
      cd = (*objects)[playerid]->lineIntersection(x, y, pcx + 8, pcy + 16,1,1,1,1);
      // if in los and distance to player is less than blade radius
      if(cd.intersect && sqrt(pow(x - ((*objects)[playerid]->getX() + 8), 2) + pow(y - ((*objects)[playerid]->getY() + 16), 2)) < bladeRadius) hit = true;
      //std::cout << cd.intersect << " " << sqrt(pow(x - ((*objects)[playerid]->getX() + 8), 2) + pow(y - ((*objects)[playerid]->getY() + 16), 2)) << " " << bladeRadius << "\n";
      //is center of circle in square
      if(x >= pcx && x <= pcx + 16 && y >= pcy && y <= pcy+32) hit = true;
      if(hit)
      {
        Player * ptr;
        ptr = dynamic_cast<Player*>((*objects)[playerid]);

        cd.damage = damage;
        cd.knockback = knockback;
        if(pcx > x) cd.knockback = -knockback;
        cd.iframes = 120;
        ptr->damaged(cd);
      }
    }
    break;
  }
}

void Turret::damaged(CollisionData cd)
{
  if(invincible) return;
  int direct = -1;
  hp -= cd.damage;
  if(cd.right) direct = 1;
  //knockedBack(direct, 1);
}

int Turret::getRadius(){return radius;}

int Turret::activateThisObject(bool on)
{
  if(on != activated)
  {
    activated = !activated;
    // more TODOs to be protected
  }
}

bool Turret::render(int cameraX, int cameraY, int priority)
{

  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  if(hp <= 35)
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), crack1_1.x - cameraX, crack1_1.y - cameraY, crack1_2.x - cameraX, crack1_2.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), crack2_1.x - cameraX, crack2_1.y - cameraY, crack2_2.x - cameraX, crack2_2.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), crack3_1.x - cameraX, crack3_1.y - cameraY, crack3_2.x - cameraX, crack3_2.y - cameraY);
    if(hp < 25)
    {
      SDL_RenderDrawLine(mDisplay->getRenderer(), crack1_2.x - cameraX, crack1_2.y - cameraY, crack1_3.x - cameraX, crack1_3.y - cameraY);
      SDL_RenderDrawLine(mDisplay->getRenderer(), crack2_2.x - cameraX, crack2_2.y - cameraY, crack2_3.x - cameraX, crack2_3.y - cameraY);
      SDL_RenderDrawLine(mDisplay->getRenderer(), crack3_2.x - cameraX, crack3_2.y - cameraY, crack3_3.x - cameraX, crack3_3.y - cameraY);
      if(hp < 15)
      {
        SDL_RenderDrawLine(mDisplay->getRenderer(), crack1_2.x - cameraX, crack1_2.y - cameraY, crack1_4.x - cameraX, crack1_4.y - cameraY);
        SDL_RenderDrawLine(mDisplay->getRenderer(), crack2_2.x - cameraX, crack2_2.y - cameraY, crack2_4.x - cameraX, crack2_4.y - cameraY);
      }
    }
  }

  // invincible turrets have a grey look to them
  if(invincible)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 100, 255, SDL_ALPHA_OPAQUE);
    drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, radius + 2);
  }

  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, radius);


  if(combatAI != TA_BEYBLADE)
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), cannonBottomLeft.x - cameraX, cannonBottomLeft.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonTopLeft.x - cameraX, cannonTopLeft.y - cameraY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopRight.x - cameraX, cannonTopRight.y - cameraY, cannonBottomRight.x - cameraX, cannonBottomRight.y - cameraY);
    if(combatAI == TA_GUN_SEMI_SPREAD)
    {
      SDL_RenderDrawLine(mDisplay->getRenderer(), cannonTopMiddle.x - cameraX, cannonTopMiddle.y - cameraY, cannonBottomMiddle.x - cameraX, cannonBottomMiddle.y - cameraY);
    }
  }
  else
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    Point p; // this is the centerpoint of rotation
    p.x = x; p.y = y;
    for(int i = 0; i < 9; i++)
    {
      rotatePoint((360/6), &cannonBottomLeft, p);
      rotatePoint((360/6), &cannonBottomRight, p);
      rotatePoint((360/6), &cannonTopMiddle, p);
      SDL_RenderDrawLine(mDisplay->getRenderer(), cannonBottomLeft.x - cameraX, cannonBottomLeft.y - cameraY, cannonTopMiddle.x - cameraX, cannonTopMiddle.y - cameraY);
      SDL_RenderDrawLine(mDisplay->getRenderer(), cannonBottomRight.x - cameraX, cannonBottomRight.y - cameraY, cannonTopMiddle.x - cameraX, cannonTopMiddle.y - cameraY);
    }
    if(activated)
    {
      rotatePoint(18, &cannonBottomLeft, p);
      rotatePoint(18, &cannonBottomRight, p);
      rotatePoint(18, &cannonTopMiddle, p);
      spinReset++;
      if(spinReset > 360/18)
      {
        cannonTopMiddle.x = x;
        cannonTopMiddle.y = y - (bladeRadius);
        cannonBottomLeft.x = x - 4;
        cannonBottomLeft.y = y - 9;
        cannonBottomRight.x = x + 4;
        cannonBottomRight.y = y - 9;
        spinReset = 0;
      }
    }
  }
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
