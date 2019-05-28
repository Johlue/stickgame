#include "CollisionData.h"

CollisionData::CollisionData(){}
CollisionData::CollisionData(double ox, double oy)
{
  x = ox;
  y = oy;
}

void CollisionData::copy(CollisionData c)
{
    x = c.x;
    y = c.y;
    intersect = c.intersect;
    up = c.up;
    down = c.down;
    right = c.right;
    left = c.left;
    slope = c.slope;
    iframes = c.iframes;
}
