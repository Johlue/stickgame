#ifndef TURRET_31052019
#define TURRET_31052019

#include "GameObject.h"
#include "Bullet.h"

class Turret : public GameObject //this is a round gun thing that tries to spin around to shoot the player
{
public:

    Turret();
    // x location, y location, width, heigth, pointer to display
    Turret(int xl, int yl, Display* display, std::vector<GameObject*>* obj);
    ~Turret();

    void handleEvent(SDL_Event* e);
    void update();
    void render(int cameraX, int cameraY);
    void move(double x, double y);
    void rotate(double angl);
    // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
    CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  double angle = 0; // angle that the gun is currently facing in // -90 is up facing
  std::vector<GameObject*>* objects = nullptr; // contains objects to interact with
  Point cannonTopLeft, cannonTopRight, cannonBottomLeft, cannonBottomRight;
  double rotationspeed = 2;
  int cooldown= 2;
  int shotFrequency = 30; // how often the gun shoots
  int bulletDamage = 20;
  int bulletSpeed = 5;
  int bulletKnockback = 3;
  int playerid = 9999999;
  //maybe some other parameters of the bullet in question
};

#endif
