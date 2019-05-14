#include "GameObject.h"

GameObject::GameObject(){}
GameObject::GameObject(int xl, int yl, int w, int h, Display* display){}
GameObject::~GameObject(){}

void GameObject::handleEvent(SDL_Event* e){}
void GameObject::update(){}
void GameObject::render(){}

bool GameObject::isOnScreen()
{
  return onScreen;
}

int GameObject::getType()
{
  return type;
}

CollisionData GameObject::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
