#include "Hazard.h"

Hazard::Hazard(){type = 3;}
Hazard::Hazard(int xl, int yl, int w, int h, int haztype, int directionO, Display* display)
{
  type = 3;
  hazardType = haztype;
  direction = directionO;
}
Hazard::~Hazard(){}

void Hazard::handleEvent(SDL_Event* e){}
void Hazard::update(){}
void Hazard::render()
{
  switch(hazardType)
  {
    // what type of hazard
    case SPIKE:
      std::cout <<"spizzrender";
    switch(direction)
    {
      //what direction is the spike pointing
      case UP:
        std::cout <<"uprender";
      SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(mDisplay->getRenderer(), x, y+height, x+width, y+height);
      SDL_RenderDrawLine(mDisplay->getRenderer(), x, y+height, x+(width/2), y);
      SDL_RenderDrawLine(mDisplay->getRenderer(), x+(width/2), y, x+width, y+height);
      break;
    }
    //do stuff
    break;
  }
}

CollisionData Hazard::lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){}
