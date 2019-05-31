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
