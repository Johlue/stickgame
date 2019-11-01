#include "Ui.h"

Ui::Ui(){}

Ui::Ui(Display* display)
{
  mDisplay = display;
}
Ui::~Ui(){}

void Ui::update(){}
void Ui::render()
{
  if(!playerDead)
  {
    // hp bar box
    SDL_Rect rect3 = { 8, 8, 259, 24};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect3);
    // hp bar
    SDL_Rect rect2 = { 10, 10, std::max(player->getHP(), 0), 20};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);

    // gun bar surrounding box
    SDL_Rect rect = { 10, 34, 102, 12};
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
    // gun bar
    SDL_Rect rect4 = {11, 35, std::max(player->getLazerCharge()/90, 0.0), 10};
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 255, 255, 0xFF);
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect4);
  }
}

void Ui::setDeadPlayer(bool dead){playerDead = dead;}
void Ui::setDisplay(Display* disp){mDisplay = disp;}
Player* Ui::getPlayer(){return player;}
void Ui::setPlayer(Player * newPlayer)
{
  player = newPlayer;
}
