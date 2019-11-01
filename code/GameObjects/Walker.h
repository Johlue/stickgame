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
  Walker(int x, int y, int combatAI, int movementAI, Display* disp, std::vector<GameObject*>* objs);
  ~Walker();

  void handleEvent(SDL_Event* e);
  void update();
  void render(int cameraX, int cameraY);

  void damaged(CollisionData cd);

protected:
  bool fallingCheck(); // check if there's floor underneath, and if not start falling
  void fallingCollisionCheck(); // if falling check if collided with floor
  bool floorEndCheck(); // check if the floor ends in front of you
  bool wallCheck();     //  see if wall is in front
  bool detectPlayer();  // try and find the player
  double xVel = 0; double yVel = 0;
  int direction = 1; // 1 = right, -1 = left;
  int hp = 40;
  bool falling = false;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  Boundary* floorBeneath = nullptr; // the floor that your currently standing on
  int playerid = 9999999;
  bool playerDetected = false; // has the player been seen
  double detectionRange = 200.0; // how far can this guy see
  int playerMemory = 600; // how long the walker can remember having detected the player
  int playerMemoryRemaining = 0; // how many frames remaining until walker forgets the player
  int waiting = 0; // waiting at the edge of reality(aka the floor)
  int AI = RANGED; // combat ai
  int AIwalk = WAIT; // movement ai (sort of)
  double moveSpeed = 2;
  double combatSpeed = 2;

  int meleeCooldown = 120; // total amount of time until a second melee attack can be unleashed
  int meleeCooldownRemaining = 0; // time remaining until next attack
  int meleeTell = 60; // amount of time spent posing until actually attacking
  int meleeTellRemaining = 0; // time until end of posing
  int meleeAttack = 30; // amount of time the melee attack animation lasts for, (afterwards movement is possible again)
  int meleeAttackRemaning = 0;
  bool meleeAttackInitiated = false;

  int initialShotDelay = 60;
  int initialShotDelay_t = 60;
  int betweenShotsDelay = 20;
  int betweenShotsDelay_t = 0;
  int clipSize = 4;
  int shotsRemaining = 4;
  int reloadSpeed = 60;
  int reloadSpeed_t = 60;
  double gunAngle = 0;
  Point gunPoint;
  void rangedAIshoot(); // shooting function for the ranged Ai type
  void aimAt(double target, double rotateSpeed);  // rotate gunangle towards a target, at a speed
  void rotate(double ang);

  void meleeAttackF();

};

#endif
