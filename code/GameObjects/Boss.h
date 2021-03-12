#ifndef BOSS_23022021
#define BOSS_23022021

#include "GameObject.h"
#include "Boundary.h"
#include "Player.h"
#include "Bullet.h"
#include "Point.h"

enum bossActionStates
{
  BAS_UNAWARE,
  BAS_NORMAL,
  BAS_CHARGE,
  BAS_MEGAGUN,
  BAS_DEAD
};

enum bossShieldStates
{
  BSH_ACTIVE = 0,
  BSH_DEPLETED = 1,
  BSH_ATTACK = 2,
  BSH_POST_ATTACK = 3,
  BSH_RECHARGE = 4,
  BSH_MEGAGUN = 5,
  BSH_DEAD = 6
};

class Boss : public GameObject
{
public:
Boss();
Boss(int ox, int oy, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs);
~Boss();

void handleEvent(SDL_Event* e);
void update();
  void updateMovement();
    void move(double xm, double ym);
  void updateShotgun();
  void updateMegagun();
  void updateShield();
bool render(int cameraX, int cameraY, int priority);

SDL_Rect getHurtBox();
SDL_Rect getCritBox();

void damaged(int dmg);

int getHP();
int getShieldHP();
int getActionState();
int getDeathTime();

protected:

int width = 80;
int height = 160;
double xVel = 0;
double yVel = 0;
int direction = -1;
Point center = {x + width/2, y + 20};

int hp = 255;

int actionState = BAS_UNAWARE;

double moveSpeed = .6;
double leftWall;
double rightWall;
double chargeSpeed = 15;
int chargeTimer = 600;
int chargePrepTime = 90;
int chargeDirection;

int megagunPhase = 0;
int megagunTime = 600; // 10 seconds, 2 for chargeup and 6 for firing 2 for cooling down
int megagunDamage = 60;

double shotgunAim = 270;
double shotgunRotateSpeed = 2;
Point shotgunTarget = {x + width/2 - 60, y + 20};
int shotgunVolley = 0;
int shotgunVolleyTime = 20;
int shotgunTime = 200;
int shotgunDamage = 40;

double shieldRadius = 140;
int shieldHealth = 1200;
int shieldHealthMax = 1200;
int shieldState = BSH_ACTIVE;
int shieldDepletedTime = 300;
int shieldRechargeTime = 90;

int shieldDamage = 100;
double shieldAttackRadius = 0;
double shieldAttackRadiusMax = 140;
int shieldPostAttackTime = 120;

int deathTime = 0;

int playerid = 9999999;
std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
std::vector<Animation*> mAnimations;

void rotateShotgun(double angl);
void aimAt(double target, double rotateSpeed);
void volley(int shotNumber, double maxAngle, double shotSpeed);
void megagunVolley(double xloc, double yloc, int shotnumber, double maxAngle, double shotSpeed, double initialAngle);

};

#endif
