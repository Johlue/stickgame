#include "Vector2D.h"

Vector2D::Vector2D(){}
Vector2D::~Vector2D(){}

Vector2D::Vector2D(double startX, double startY, double endX, double endY)
{
  x = fabs(startX - endX);
  y = fabs(startY - endY);
  length = sqrt(pow(x, 2) + pow(y, 2));
  angle = atan( y / x );
}

Vector2D::Vector2D(double startX, double startY, double endX, double endY, double oLength)
{
  x = fabs(startX - endX);
  y = fabs(startY - endY);
  length = oLength;
  angle = atan( y / x ); // TODO: check if this works, it should but whatever
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
