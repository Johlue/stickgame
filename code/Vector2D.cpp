#include "Vector2D.h"

Vector2D::Vector2D(){}
Vector2D::~Vector2D(){}

Vector2D::Vector2D(double startX, double startY, double endX, double endY)
{
  x = endX - startX;
  y = endY - startY;
  length = sqrt(pow(x, 2) + pow(y, 2));
  angle = atan( y / x );
}

Vector2D::Vector2D(double startX, double startY, double endX, double endY, double oLength)
{
  double tx = endX - startX;
  double ty = endY - startY;
  length = oLength;
  if(tx == 0) tx += 0.000001; // to prevent divide by zero
  angle = atan( ty / tx ); // TODO: check if this works, it should but whatever
  x = oLength * cos(angle);
  y = oLength * sin(angle);
  if(endX - startX < 0)
  {
    x = -x;
    y = -y;
  }
}

//angle in radians
Vector2D::Vector2D(double oAngle,  double oLength)
{
  angle = oAngle;
  length = oLength;
  x = oLength * cos(angle);
  y = oLength * sin(angle);
}

Vector2D::operator+(Vector2D vector)
{
  x += vector.x;
  y += vector.y;
  length = sqrt(pow(x, 2) + pow(y, 2));
  angle = atan( y / x );
}

Vector2D::operator-(Vector2D vector)
{
  x -= vector.x;
  y -= vector.y;
  length = sqrt(pow(x, 2) + pow(y, 2));
  angle = atan( y / x );
}

Vector2D::operator=(Vector2D vector)
{
  x = vector.x;
  y = vector.y;
  length = vector.length;
  angle = vector.angle;
}

double Vector2D::dot(Vector2D vector)
{
  return (x * vector.x) + (y * vector.y);
}
