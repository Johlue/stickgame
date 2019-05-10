#include "Player.h"
#include <iostream>

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
  	//Get mouse position
  	int xm, ym;
  	SDL_GetMouseState( &xm, &ym );
    renderPoint = (*objects)[0]->lineIntersection(x, y, xm, ym, 1, 1, 1, 1);
    std::cout << renderPoint.x << ", " << renderPoint.y << std::endl;
    break;
  }
}

void Player::update()
{
  if(movingRight) x += 3;
  if(movingLeft) x -= 3;
}

void Player::render()
{
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
  int xm, ym;
  SDL_GetMouseState( &xm, &ym );
  SDL_RenderDrawLine(mDisplay->getRenderer(), x, y, xm, ym);

  SDL_Rect rect = { x, y, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);

  SDL_Rect rect2 = { renderPoint.x-3, renderPoint.y-3, 7, 7};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 255, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
}
