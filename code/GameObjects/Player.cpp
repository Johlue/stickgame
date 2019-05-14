#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(){}

Player::Player(double xl, double yl, Display* display, std::vector<GameObject*>* obj)
{
  mDisplay = display;
  SDL_Point renderPoint{0, 0};
  x = xl;
  y = yl;
  width = 16;
  height = 32;
  objects = obj;
  type = PLAYER;
}

Player::~Player(){}


void Player::handleEvent(SDL_Event* e)
{
  switch(e->type)
  {
    case SDL_KEYDOWN:
    switch(e->key.keysym.sym)
    {
      case SDLK_RIGHT:
      movingRight = true;
      break;

      case SDLK_LEFT:
      movingLeft = true;
      break;
    }
    break;

    case SDL_KEYUP:
    switch(e->key.keysym.sym)
    {
      case SDLK_RIGHT:
      movingRight = false;
      break;

      case SDLK_LEFT:
      movingLeft = false;
      break;
    }
    break;

    case SDL_MOUSEMOTION:
    break;
  }
}

void Player::update()
{
  if(movingRight) x += 3;
  if(movingLeft) x -= 3;

  //Get mouse position
  int xm, ym;
  double shortestDistance = 999999.0;
  double tempDistance = 99999.0;
  CollisionData tempPoint;
  SDL_GetMouseState( &xm, &ym );
  for(int i = 0; i < objects->size(); i++)
  {
    // run through all boundary type gameobjects
    if((*objects)[i]->getType() == BOUNDARY)
    {
      // Collisions happen here
      tempPoint = (*objects)[i]->lineIntersection(x, y, xm, ym, 1, 1, 1, 1);
      // if an intersection between the ray and the boundary happens do stuff
      if(tempPoint.intersect)
      {
        double pow1 = pow((x - tempPoint.x), 2.0);
        double pow2 = pow((y - tempPoint.y), 2.0);
        tempDistance = sqrt(pow1 + pow2);
        // if intersecting multiple boundaries then check which one is closest and collide with that one
        if(tempDistance < shortestDistance)
        {
          shortestDistance = tempDistance;
          renderPoint.x = tempPoint.x;
          renderPoint.y = tempPoint.y;
          renderPoint.intersect = tempPoint.intersect;
        }
      }
    }
  }
}

void Player::render()
{
  // line drawn from player to mouse location for testing purposes
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  int xm, ym;
  SDL_GetMouseState( &xm, &ym );
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, xm, ym);

// placeholder graphics for player
  SDL_Rect rect = { x, y, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);

// collision test rectangle, mouse based
  if(renderPoint.intersect)
  {
    SDL_Rect rect2 = { renderPoint.x-3, renderPoint.y-3, 7, 7};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
}
