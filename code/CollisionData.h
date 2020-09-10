#ifndef COLLISIONDATA_10052019
#define COLLISIONDATA_10052019

// this is returned upon a collision between two objects and then stuff happens once it's done
class CollisionData
{
public:
  CollisionData();
  CollisionData(double ox, double oy);
  // copies the info of another collisiondata
  void copy(CollisionData c);

  double x = 0;
  double y = 0;
  bool intersect = false;
  // what direction a wall/floor is facing, and if it's sloped or not
  bool up = false;
  bool down = false;
  bool right = false;
  bool left = false;
  bool slope = false;
  // knockback, damage, iframes, whatever else comes to mind
  int damage = 0;
  int iframes = 0;
  double knockback = 0;
};

#endif
