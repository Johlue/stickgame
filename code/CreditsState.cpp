#include "CreditsState.h"

CreditsState::CreditsState(){}
CreditsState::CreditsState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  mDisplay = dis;
  textureArray = texA;
  currentState = cs;

}

CreditsState::~CreditsState(){}

// deal with user input
void CreditsState::handleEvents(SDL_Event* e)
{
  if(e->type == SDL_KEYUP)
  {
    if(e->key.keysym.sym == SDLK_ESCAPE)
    {
      timePassed = 0;
      *currentState = MENUSTATE;
    }
  }
}
// do frame update stuff
void CreditsState::update()
{
  timePassed++;
}
// draw the things
void CreditsState::render()
{
  (*textureArray)[TEX_CREDITS]->render(0,0);
  if(timePassed*2 < 255)
  {
    int opacity = std::max(255-(timePassed*2), 0);
    SDL_Rect redscreen = {0,0, mDisplay->getWidth(), mDisplay->getHeight()};
    SDL_SetRenderDrawColor(mDisplay->getRenderer(),255, 0, 0, opacity);
    SDL_RenderFillRect(mDisplay->getRenderer(), &redscreen);
  }
}
