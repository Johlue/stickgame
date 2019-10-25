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

  double x;
  double y;
  bool intersect = false;
  // what direction a wall/floor is facing, and if it's sloped or not
  bool up;
  bool down;
  bool right;
  bool left;
  bool slope;
  // knockback, damage, iframes, whatever else comes to mind
  int damage;
  int iframes;
  double knockback;
};

#endif
