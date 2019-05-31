#ifndef TURRET_31052019
#define TURRET_31052019

#include "GameObject.h"

class Turret : public GameObject //this is a round gun thing that tries to spin around to shoot the player
{
public:

    Turret();
    // x location, y location, width, heigth, pointer to display
    Turret(int xl, int yl, int w, int h, Display* display);
    ~Turret();

    void handleEvent(SDL_Event* e);
    void update();
    void render(int cameraX, int cameraY);

    // checks if two lines intersect based on two points each(x1, y1),(x2, y2) and (x3, y3),(x4, y4)
    CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
protected:
  double angle; // angle that the gun is currently facing in
  int shotFrequency; // how often the gun shoots
  int bulletDamage;
  int bulletSpeed;
  int bulletKnockback;
  //maybe some other parameters of the bullet in question
};

#endif
