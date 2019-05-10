#ifndef COLLISIONDATA_10052019
#define COLLISIONDATA_10052019

// this is returned upon a collision between two objects and then stuff happens once it's done
class CollisionData
{
public:
  CollisionData();
  CollisionData(double ox, double oy);
  double x;
  double y;
  bool intersect = false;
  // knockback, damage, iframes, whatever else comes to mind
};

#endif
