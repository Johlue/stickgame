#ifndef TURRET_31052019
#define TURRET_31052019

#include "GameObject.h"
#include "Bullet.h"

enum TurretAttackAIs{
  TA_GUN_ACCURATE,
  TA_GUN_SEMI_SPREAD,
  TA_GUN_FULL_SPREAD,
  TA_BEYBLADE
};

enum TurretMovementAIs{
  TM_STATIONARY,
  TM_FLIGHT,
  TM_GROUNDSPIN,
  TM_NOCLIP
};

class Turret : public GameObject //this is a round gun thing that tries to spin around to shoot the player
{
public:

    Turret();
    // x location, y location, width, heigth, pointer to display
    Turret(int xl, int yl, int cAI, int mAI, Display* display, std::vector<GameObject*>* obj);
    ~Turret();

    void handleEvent(SDL_Event* e);
    void update();
    bool render(int cameraX, int cameraY, int priority);
    void move(double xm, double ym);
    void turretMove(double distanceToPlayer);
    void shoot();
    void rotate(double angl);
    void damaged(CollisionData cd);
    bool collisionCheck(double x, double y);

    int getRadius();
    // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
    CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  double angle = 0; // angle that the gun is currently facing in // -90 is up facing
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  Point cannonTopLeft, cannonTopRight, cannonBottomLeft, cannonBottomRight;
  double rotationspeed = 2;
  double shootingAngle = 4; // at how close of an angle towards the player will the turret shoot
  int cooldown= 2;
  int shotFrequency = 30; // how often the gun shoots
  int bulletDamage = 20;
  int bulletSpeed = 5;
  int bulletKnockback = 3;
  int playerid = 9999999;
  int detectionRange = 500; // how far can it see
  bool gravity = false; // is it affected by gravity
  //maybe some other parameters of the bullet in question

  double moveSpeed = 2;
  int hp = 60;
  int radius = 10; // how big it is, used for hitbox purposes
  int distanceFromPlayer = 90; // in case of a moving turret, this is the distance it will keep from the player

  int combatAI = TA_GUN_SEMI_SPREAD;
  int movementAI = TM_STATIONARY;
};

#endif
