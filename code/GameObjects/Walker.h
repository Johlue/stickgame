#ifndef WALKER_16082019
#define WALKER_16082019

#include "GameObject.h"
#include "Boundary.h"
#include "Player.h"

class Walker : public GameObject
{
public:
  Walker();
  // x location, y location, width, heigth, pointer to display
  Walker(int x, int y, Display* disp, std::vector<GameObject*>* objs);
  ~Walker();

  void handleEvent(SDL_Event* e);
  void update();
  void render(int cameraX, int cameraY);

protected:
  bool fallingCheck(); // check if there's floor underneath, and if not start falling
  void fallingCollisionCheck(); // if falling check if collided with floor
  bool floorEndCheck(); // check if the floor ends in front of you
  bool wallCheck(); //  see if wall is in front
  bool detectPlayer(); // try and find the player
  double xVel = 0; double yVel = 0;
  int direction = 1; // 1 = right, -1 = left;
  bool falling = false;
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  Boundary* floorBeneath = nullptr; // the floor that your currently standing on
  int playerid = 9999999;
  bool playerDetected = false; // has the player been seen
  double detectionRange = 200.0; // how far can this guy see
};

#endif
