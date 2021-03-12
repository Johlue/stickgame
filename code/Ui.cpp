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

  }
  if(boss != nullptr)
  {
    if(boss->getActionState() != BAS_DEAD && boss->getActionState() != BAS_UNAWARE)
    {
      SDL_Rect rect3 = { mDisplay->getWidth() - 255 - 8, 8, 259, 24};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rect3);
      // hp bar
      SDL_Rect rect2 = { mDisplay->getWidth() - 255 - 6 + (255 - boss->getHP()), 10, std::max(boss->getHP(), 0), 20};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 155, 155, 155, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);

      SDL_Rect rect4 = { mDisplay->getWidth() - 122 - 8, 34, 124, 14};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rect4);
      // shield bar
      SDL_Rect rect5 = { mDisplay->getWidth() - 122 - 6 + (120 - (boss->getShieldHP())/10), 36, std::max(boss->getShieldHP()/10, 0), 10};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 50, 50, 255, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rect5);
    }
  }
}

void Ui::setDeadPlayer(bool dead){playerDead = dead;}
void Ui::setDisplay(Display* disp){mDisplay = disp;}
Player* Ui::getPlayer(){return player;}
void Ui::setPlayer(Player * newPlayer)
{
  player = newPlayer;
}
void Ui::setBoss(Boss * newBoss)
{
  boss = newBoss;
}
void Ui::deleteBoss()
{
  boss = nullptr;
}
