#ifndef WALKER_16082019
#define WALKER_16082019

#include "GameObject.h"
#include "Boundary.h"
#include "Player.h"
#include "Bullet.h"

enum AIs{
  MELEE, //medium speed, weak
  MELEE_QUICK, // fast, weak, jumps
  MELEE_STRONG, //slow, hits like a truck
  RANGED, // pistol meh shooting speed / power
  RANGED_QUICK, // smg, fast shooting, meh power
  RANGED_MINIGUN, // minigun(duh), fast strong shooting with cooldown, moves slowly
  RANGED_HYPERBEAM // has the players gigalazer, medium move speed, slow obvious chargeup, instant death damage
  };

enum AIwalks{
  STANDING, // stands still and only turns around if detects player and the player goes behind walker
  INSTANTTURN, // turns as soon as edge is detected
  WAIT // waits 2 seconds at edge of floor before turning around
};

class Walker : public GameObject
{
public:
  Walker();
  // x location, y location, width, heigth, AI, walkAI, pointer to display
  Walker(int x, int y, int combatAI, int movementAI, Display* disp, std::vector<GameObject*>* objs, std::vector<ImageTexture*>* texs, int direct);
  ~Walker();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  void damaged(CollisionData cd);
  CollisionData lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4);
  void knockedBack(int knockback, int dmg);

  int activateThisObject(bool on);

protected:
  bool fallingCheck(); // check if there's floor underneath, and if not start falling
  void fallingCollisionCheck(); // if falling check if collided with floor
  bool floorEndCheck(); // check if the floor ends in front of you
  bool wallCheck();     //  see if wall is in front
  bool detectPlayer();  // try and find the player
  double xVel = 0; double yVel = 0;
  int direction = -1; // 1 = right, -1 = left;
  int hp = 400;
  bool falling = false;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  std::vector<Animation*> mAnimations;
  Boundary* floorBeneath = nullptr; // the floor that your currently standing on
  int playerid = 9999999;
  bool playerDetected = false; // has the player been seen
  double detectionRange = 500.0; // how far can this guy see
  int playerMemory = 600; // how long the walker can remember having detected the player
  int playerMemoryRemaining = 0; // how many frames remaining until walker forgets the player
  int waiting = 0; // waiting at the edge of reality(aka the floor)
  int AI = RANGED; // combat ai
  int AIwalk = WAIT; // movement ai (sort of)
  double moveSpeed = 2;
  double combatSpeed = 2;
  int damage = 8;

  int flinched = 0;

  int meleeCooldown = 0; // total amount of time until a second melee attack can be unleashed
  int meleeCooldownRemaining = 0; // time remaining until next attack
  int meleeTell = 60; // amount of time spent posing until actually attacking
  int meleeTellRemaining = 0; // time until end of posing
  int meleeAttack = 30; // amount of time the melee attack animation lasts for, (afterwards movement is possible again)
  int meleeAttackRemaining = 0;
  bool meleeAttackInitiated = false;
  int meleeRange = 15; // how close to player to perform melee attack

  int quickMeleeRange = 80; // how close to player to jump for quick ai
  bool jumping = false;
  double jumpSpeed = 5;

  int initialShotDelay = 60;
  int initialShotDelay_t = 60;
  int betweenShotsDelay = 20;
  int betweenShotsDelay_t = 0;
  int clipSize = 4;
  int shotsRemaining = 4;
  int reloadSpeed = 60;
  int reloadSpeed_t = 60;
  int minigunSpin = 0;
  int minigunSpinSpeed = 0;
  int minigunFrame = 0;
  double gunSpread = 0;
  double gunAngle = 0;
  Point gunPoint;
  Point gunCenter;
  void rangedAIshoot(); // shooting function for the ranged Ai type
  void aimAt(double target, double rotateSpeed);  // rotate gunangle towards a target, at a speed
  void rotate(double ang);

  void meleeAttackSlow(); // attack for MELEE
  void meleeAttackQuick(); // attack for MELEE_QUICK

};

#endif
