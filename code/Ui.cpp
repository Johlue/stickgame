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
  SDL_Rect rect2 = { 10, 10, player->getHP(), 20};
  SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 0, 0, 0xFF );
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
}

void Ui::setDisplay(Display* disp){mDisplay = disp;}
Player* Ui::getPlayer(){return player;}
void Ui::setPlayer(Player * newPlayer)
{
  player = newPlayer;
}
