#include "Ui.h"

Ui::Ui(){}
Ui::~Ui(){}

void Ui::update(){}
void Ui::render(){}

Player* Ui::getPlayer(){return player;}
void Ui::setPlayer(Player * newPlayer)
{
  player = newPlayer;
}
