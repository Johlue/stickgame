#ifndef PLAYER_07052019
#define PLAYER_07052019

#include "GameObject.h"
#include <vector>
#include "Boundary.h"
#include "Hazard.h"

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
  void render(int cameraX, int cameraY);

  double getX();
  double getY();

  void collisionCheck(); //
  bool movementCollisionCheck(); // checks if you ran into walls
  bool fallingCheck();
  void damaged(CollisionData hurt); // take damage from a source that is the hurt CollisionData

  int getHP();
  int getAmmo();

protected:
  void boundaryCollision(Boundary * ptr, CollisionData * tempPoint, bool * collidingX, bool * collidingY, CollisionData * collisionPointX, CollisionData * collisionPointY, double * shortestDistanceX, double * shortestDistanceY);
  void hazardCollision(Hazard * hazardPtr);

  bool movingRight = false;
  bool movingLeft = false;
  bool movingDown = false;
  bool movingUp = false;
  bool * alive; // is the player alive or not
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  std::vector<Animation*> mAnimations;
  //temp test thingy for intersection math
  CollisionData renderPoint;
  double xVel = 0;
  double yVel = 0;

  //is the player falling or not
  bool falling = false;
  // increase of yVel per frame while falling
  double gravity = .2;
  // maximum yVel gained from falling
  double terminalVelocity = 5;
  // how many frames can the player ascend for with a jump
  int maxJump = 30;
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
  // remaining invincibility frames
  int iframes = 0;
  int hp = 255;
  int ammo = 0;
};


#endif
