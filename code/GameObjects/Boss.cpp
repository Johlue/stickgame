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
}

void Boss::handleEvent(SDL_Event* e){}
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
    if((*objects)[playerid]->getY() > y){actionState = BAS_NORMAL;} // activate self if players y position is below own
    else{return;}
  }

  // actual actions go here
  center = {x + width/2, y + 20};

  updateShotgun();

  if(chainballSpin)
  {
    for(int i = 0; i < objects->size(); i++)
    {
      if((*objects)[i]->getType() == BULLET && sqrt(pow(center.x - ((*objects)[i]->getX()), 2) + pow(center.y - ((*objects)[i]->getY()), 2)) < chainballRadius)
      {
        (*objects)[i]->kill();
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
        volley(5, 40, 5);
        shotgunVolley++;
        shotgunVolleyTime = 10;
      }
      else if(shotgunVolley == 1)
      {
        volley(6, 48, 4.5);
        shotgunVolley++;
        shotgunVolleyTime = 10;
      }
      else if(shotgunVolley == 2)
      {
        volley(7, 56, 4);
        shotgunVolley++;
        shotgunVolleyTime = 10;
      }
      else if(shotgunVolley == 3)
      {
        volley(9, 64, 3.5);
        shotgunVolley++;
        shotgunVolleyTime = 10;
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
    std::cout << i-(shotNumber/2) << " " << (maxAngle/shotNumber) << " " << ((i-(shotNumber/2))*(maxAngle/shotNumber)) << std::endl;
    objects->push_back(new Bullet(shotgunTarget.x, shotgunTarget.y, bulletVector, mDisplay, objects, false, shotgunDamage, 2));
  }
}

bool Boss::render(int cameraX, int cameraY, int priority)
{
  if(priority >= 8)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 100, 255, SDL_ALPHA_OPAQUE);
    drawCircle(mDisplay->getRenderer(), center.x - cameraX, center.y - cameraY, chainballRadius);
    SDL_Rect rect2 = { x - cameraX, y - cameraY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
    SDL_Rect recthurtbox = {x - cameraX, y + 10 - cameraY, width, height - 10};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &recthurtbox);
    SDL_Rect rectcritbox = {x + width/2 - 5 - cameraX, y - cameraY, 10, 10};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rectcritbox);
    SDL_Rect rectshotguncenter = { center.x - cameraX, center.y - cameraY, 5, 5};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rectshotguncenter);
    SDL_Rect rectshotguntarget = { shotgunTarget.x - cameraX, shotgunTarget.y - cameraY, 5, 5};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rectshotguntarget);
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
  else rotateShotgun(zerodPangle);
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
