#ifndef PLAYER_07052019
#define PLAYER_07052019

#include "GameObject.h"
#include <vector>
#include "Boundary.h"
#include "Hazard.h"
#include "Slash.h"
#include "Bullet.h"
#include "Walker.h"
#include "Point.h"

class Player : public GameObject
{
public:
  Player();
  // interacting with other game objects may require a pointer to the gameobject array
  // x location, y location, pointer to display
  Player(double xl, double yl, bool * life, Display* display, std::vector<GameObject*>* obj, std::vector<ImageTexture*>* texs);
  ~Player();

  void handleEvent(SDL_Event* e);
  void update();
  bool render(int cameraX, int cameraY, int priority);

  double getX();
  double getY();

  void collisionCheck(); //
  void damaged(CollisionData hurt); // take damage from a source that is the hurt CollisionData

  int getHP();
  int getAmmo();

  CollisionData lineIntersection(double ox1, double oy1, double ox2, double oy2, double nx3, double ny3, double nx4, double ny4);

protected:

  //boundary collision stuff
  std::vector<int> getCollidableBoundaries();

  void knockedBack(int direction, int force); //left(-1) or right(1) and how far/fast/long is knockbacked
  bool fallingCheck();
  bool roofCheck();
  Point movementCollisionCheck(); // checks if you ran into walls
  Point boundaryCollision(std::vector<int> collidables);
  void hazardCollision(Hazard * hazardPtr);
  void rotate(double angl);

  bool movingRight = false;
  bool movingLeft = false;
  bool movingDown = false;
  bool movingUp = false;
  bool aimingForward = false;
  bool aimingUp = false;
  bool aimingDown = false;
  bool * alive; // is the player alive or not
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  std::vector<Animation*> mAnimations;
  std::vector<Point> beamEndPoint; // alternates between start point and end point
  std::vector<Point> beamStartPoint;
  //temp test thingy for intersection math
  CollisionData renderPoint;
  double xVel = 0;
  double yVel = 0;

  // amount of frames until player can use melee again
  int meleeCooldown = 0;
  //is the player falling or not
  bool falling = false;
  // increase of yVel per frame while falling
  double gravity = .25;
  // maximum yVel gained from falling
  double terminalVelocity = 5;
  // how many frames can the player ascend for with a jump
  int maxJump = 20;
  // for how many frames has the player been ascending with a jump
  int currentJump = 0;
  // currently pressing jump button
  bool jumping = false;
  // has the player stopped pressing the jump button while midair, or reached maxJump
  bool jumpEnded = false;
  // is the player facing right (or left)
  bool facingRight = true;
  // is the player currently being knockbacked
  bool knockback = false;
  // can't move for some reason (amount of frames)
  int stunned = 0;
  // remaining invincibility frames
  int iframes = 0;
  double gunAngle = 0;
  Point gunPoint; // location of gun relative to player
  int hp = 255;
  int ammo = 0;
  int gunFrame = 2;
};


#endif
