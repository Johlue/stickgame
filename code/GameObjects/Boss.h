#ifndef BOSS_23022021
#define BOSS_23022021

#include "GameObject.h"
#include "Boundary.h"
#include "Player.h"
#include "Bullet.h"

enum bossActionStates
{
  BAS_UNAWARE,
  BAS_NORMAL,
  BAS_CHARGE,
  BAS_MINIGUN
};

class Boss : public GameObject
{
public:
Boss();
Boss(int ox, int oy, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs);
~Boss();

void handleEvent(SDL_Event* e);
void update();
bool render(int cameraX, int cameraY, int priority);

SDL_Rect getHurtBox();
SDL_Rect getCritBox();

protected:
int width = 80;
int height = 160;
double xVel = 0;
double yVel = 0;
int direction = -1;

int hp = 255;

int actionState = BAS_UNAWARE;

double moveSpeed = 1;
double chargeSpeed = 5;
int chargeDamage = 254;
int chargeTimer = 0;

double minigunAim = 270;
double minigunSpin = 0;
double shotgunAim = 270;
int shotgunVolley = 0;
int shotgunTime = 0;
int shotgunDamage = 40;

int chainballRadius;
int chainballTime = 0; // this'll probs be split to a billion different parts
int chainballDamage = 100;

int playerid = 9999999;
std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
std::vector<Animation*> mAnimations;

};

#endif
