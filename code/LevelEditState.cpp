#include "LevelEditState.h"


LevelEditState::LevelEditState()
{}

LevelEditState::LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  init();
}

LevelEditState::~LevelEditState()
{}


void LevelEditState::init()
{
  menu.setTextureArray(textureArray);
}

void LevelEditState::freeMem()
{}

void LevelEditState::handleEvents(SDL_Event* e)
{
  menu.handleEvents(e);
  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_ESCAPE:
      *currentState = MENUSTATE;
      break;

      case SDLK_DOWN:
      yMovement = 5;
      break;

      case SDLK_UP:
      yMovement = -5;
      break;

      case SDLK_RIGHT:
      xMovement = 5;
      break;

      case SDLK_LEFT:
      xMovement = -5;
      break;

      case SDLK_RCTRL:
      speedMultiplier = 3;
      break;
    }
  }
  else if(e->type == SDL_KEYUP)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_DOWN:
      yMovement = 0;
      break;

      case SDLK_UP:
      yMovement = 0;
      break;

      case SDLK_RIGHT:
      xMovement = 0;
      break;

      case SDLK_LEFT:
      xMovement = 0;
      break;

      case SDLK_RCTRL:
      speedMultiplier = 1;
      break;
    }
  }
}

void LevelEditState::update()
{
  cameraX += xMovement * speedMultiplier;
  cameraY += yMovement * speedMultiplier;
  std::cout << "x: " << cameraX << "    y: " << cameraY << std::endl;
}

void LevelEditState::render()
{
  menu.render();
  for(int i = 0; i < 20; i++ )
  {
    SDL_Rect rect2 = { i*200 - cameraX, i*200 - cameraY, 50, 50};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 255, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
}

void LevelEditState::changeState(int s)
{
  *currentState = s;
}
