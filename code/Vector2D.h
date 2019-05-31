#ifndef VECTOR2D_31052019
#define VECTOR2D_31052019

#include <cmath>

class Vector2D
{
public:
  Vector2D(); // default constructor
  ~Vector2D(); // destructor

  //create a vector from a start and end point
  Vector2D(double startX, double startY, double endX, double endY);

  //create a vector with an angle from two points and a predetermined length
  Vector2D(double startX, double startY, double endX, double endY, double oLength);
  
  double length; // distance between (0, 0) and (x, y)
  double angle; // angle in radians
  double x;
  double y;

};

#endif
