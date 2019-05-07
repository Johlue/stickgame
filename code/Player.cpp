#include "Player.h"
#include <iostream>

Player::Player(){}

Player::Player(int xl, int yl, Display* display)
{
  mDisplay = display;
  x = xl;
  y = yl;
  width = 16;
  height = 32;
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
  }
}

void Player::update()
{
  if(movingRight) x += 3;
  if(movingLeft) x -= 3;
}

void Player::render()
{
  SDL_Rect rect = { x, y, width, height};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
}
