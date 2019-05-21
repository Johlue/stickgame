#ifndef PLAYER_07052019
#define PLAYER_07052019

#include "GameObject.h"
#include <vector>
#include "Boundary.h"

class Player : public GameObject
{
public:
  Player();
  // interacting with other game objects may require a pointer to the gameobject array
  // x location, y location, pointer to display
  Player(double xl, double yl, Display* display, std::vector<GameObject*>* obj);
  ~Player();

  void handleEvent(SDL_Event* e);
  void update();
  void render();

protected:
  bool boundaryCollision();

  bool movingRight = false;
  bool movingLeft = false;
  bool movingDown = false;
  bool movingUp = false;
  std::vector<GameObject*>* objects = nullptr;
  //temp test thingy for intersection math
  CollisionData renderPoint;
  double xVel = 0;
  double yVel = 0;


  int hp;
  int ammo;
};


#endif
