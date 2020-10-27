#include "GameObject.h"

GameObject::GameObject(){}
GameObject::GameObject(int xl, int yl, int w, int h, Display* display){}
GameObject::~GameObject(){}

void GameObject::handleEvent(SDL_Event* e){}
void GameObject::update(){}
bool GameObject::render(int cameraX, int cameraY, int priority){}

bool GameObject::isOnScreen()
{
  return onScreen;
}

int GameObject::getType()
{
  return type;
}

bool GameObject::isAlive(){return alive;}
void GameObject::kill(){alive = false;}

CollisionData GameObject::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
int GameObject::activateThisObject(bool on){}

double GameObject::getX(){return x;}
double GameObject::getY(){return y;}

int GameObject::getWidth(){return width;}
int GameObject::getHeight(){return height;}

int GameObject::getId(){return id;}
void GameObject::setId(int o_id){id = o_id;}
