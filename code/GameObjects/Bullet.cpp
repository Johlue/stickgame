#include "Bullet.h"

Bullet::Bullet(){type = BULLET;}
Bullet::Bullet(int xl, int yl, Vector2D move, Display* display, std::vector<GameObject*>* obj, bool players, int dmg, double kb)
{
  type = BULLET;
  knockback = kb;
  x = xl;
  y = yl;
  movement = move;
  mDisplay = display;
  damage = dmg;
  objects = obj;
  playerBullet = players;
}
Bullet::~Bullet(){}

void Bullet::handleEvent(SDL_Event* e){}
void Bullet::update()
{
  x += movement.x;
  y += movement.y;
  lifeTime -= 1;
  if(lifeTime < 1) alive = false;

//collisions
  for(int i = 0; i < objects->size(); i++)
  {
    if ((*objects)[i]->getType() == BOUNDARY)
    {
      CollisionData cd;
      cd.copy((*objects)[i]->lineIntersection(x, y, x+movement.x, y+movement.y,0,0,0,0));
      if(cd.intersect)
      {
        if(movement.y >= 0  && cd.up)
        {
          alive = false;
          break;
        }
        if(movement.y <= 0  && cd.down)
        {
          alive = false;
          break;
        }
        if(movement.x <= 0  && cd.right)
        {
          alive = false;
          break;
        }
        if(movement.x >= 0  && cd.left)
        {
          alive = false;
          break;
        }
      }
    }
    if(playerBullet && (*objects)[i]->getType() == WALKER) // hitting an enemy with a player bullet
    {
      if(x >= (*objects)[i]->getX() && x <= (*objects)[i]->getX()+(*objects)[i]->getWidth()
      && y >= (*objects)[i]->getY() && y <= (*objects)[i]->getY()+(*objects)[i]->getHeight())
      {
        CollisionData cd;
        cd.damage = damage;
        cd.iframes = iframes;
        cd.knockback = knockback;
        if(movement.x > 0) cd.knockback = -knockback;

        Walker * wlk;
        wlk = dynamic_cast<Walker*>((*objects)[i]);
        wlk->damaged(cd);

        alive = false;
      }
    }
    else if(playerBullet && (*objects)[i]->getType() == TURRET)
    {
      CollisionData cd;
      Turret * ptr;
      ptr = dynamic_cast<Turret*>((*objects)[i]);
      if(x >= ptr->getX() - ptr->getRadius() && x <= ptr->getX() + ptr->getRadius()
        && y >= ptr->getY() - ptr->getRadius() && y <= ptr->getY() + ptr->getRadius())
        {
          cd.damage = damage;
          cd.knockback = knockback;
          cd.iframes = iframes;
          if(movement.x > 0) cd.knockback = -knockback;

          ptr->damaged(cd);

          alive = false;
        }
    }
    else if(playerBullet && (*objects)[i]->getType() == BOSS)
    {
      CollisionData cd;
      Boss * ptr;
      ptr = dynamic_cast<Boss*>((*objects)[i]);
      if(x >= ptr->getCritBox().x && x <= ptr->getCritBox().x + ptr->getCritBox().w && y >= ptr->getCritBox().y && y <= ptr->getCritBox().y + ptr->getCritBox().h)
      {ptr->damaged(10); alive = false;}
      if(x >= ptr->getHurtBox().x && x <= ptr->getHurtBox().x + ptr->getHurtBox().w && y >= ptr->getHurtBox().y && y <= ptr->getHurtBox().y + ptr->getHurtBox().h)
      {ptr->damaged(1); alive = false;}
    }
    else if((*objects)[i]->getType() == PLAYER && !playerBullet) // hitting a player with an enemy bullet
    {
      CollisionData cd;
      // if bullet is inside player object do damage, and iframes and knockback and whatever else
      if(x >= (*objects)[i]->getX() && x <= (*objects)[i]->getX()+16 && y >= (*objects)[i]->getY() && y <= (*objects)[i]->getY()+32)
      {
        Player * ptr;
        ptr = dynamic_cast<Player*>((*objects)[i]);
        cd.damage = damage;
        cd.knockback = knockback;
        cd.iframes = iframes;

        if(movement.x > 0) cd.knockback = -knockback;

        ptr->damaged(cd);
      }
    }
  }
}
bool Bullet::render(int cameraX, int cameraY, int priority)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - cameraX, y - cameraY, 3);
  // black sphere maybe with white inside
  return true;
}

int Bullet::activateThisObject(bool on){}

CollisionData Bullet::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
