#include "func.h"

void rotatePoint(double angle, Point * origin, Point center)
{
  angle = (angle ) * (3.14159265359/180); // Convert to radians

  double centerX = center.x;
  double centerY = center.y;

  double rotatedX = (cos(angle) * (origin->x - centerX)) - (sin(angle) * (origin->y - centerY)) + centerX;

  double rotatedY = (sin(angle) * (origin->x - centerX)) + (cos(angle) * (origin->y - centerY)) + centerY;

  origin->x = rotatedX;
  origin->y = rotatedY;

}

void drawRectangle(SDL_Renderer * renderer, double x1, double y1, double x2, double y2)
{
  SDL_RenderDrawLine(renderer, x1, y1, x1, y2);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y1);
  SDL_RenderDrawLine(renderer, x2, y2, x1, y2);
  SDL_RenderDrawLine(renderer, x2, y2, x2, y1);
}

void drawCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius)
{
  const double diameter = (radius * 2);

  double x = (radius - 1);
  double y = 0;
  double tx = 1;
  double ty = 1;
  double error = (tx - diameter);

  while (x >= y)
  {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0)
    {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void fillCircle(SDL_Renderer * renderer, double centreX, double centreY, double radius)
{
  const double diameter = (radius * 2);

  double x = (radius - 1);
  double y = 0;
  double tx = 1;
  double ty = 1;
  double error = (tx - diameter);
  int r = 0;
  while (x >= y)
  {
    r++;
    if(r < radius)
    {
      //  Draw vertical lines across the entire circle
      SDL_RenderDrawLine(renderer, centreX + x, centreY - y, centreX + x, centreY + y); // right side
      SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX - x, centreY + y); // left side
      SDL_RenderDrawLine(renderer, centreX + y, centreY - x, centreX + y, centreY + x); //center right
      SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX - y, centreY + x); // center left
    }

    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0)
    {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

double pi(){return 3.14159265359;}

bool closeEnough(double a, double b)
{
  if(a < b + 0.05 && a > b -0.05) return true;
  return false;
}

void splitString(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> splitString(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splitString(s, delim, elems);
    return elems;
}

double pythagoras(double a, double b)
{
  a = pow(a, 2.0); b = pow(b, 2.0);
  double r = sqrt(a + b);
  return r;
}

std::vector<std::string> getLevelArray()
{
  std::vector<std::string> levelArray;
  std::ifstream levelList;
  levelList.open("LevelList.txt");
  if(levelList.is_open())
  {
    std::string line;
    while ( std::getline(levelList, line) )
    {
      if(line != "") {levelArray.push_back(line);}
    }
  }
  return levelArray;
}

std::vector<std::string> menuOptions(std::string type)
{
  std::vector<std::string> tms;
  if(type == "walkAI")
  {
    tms.push_back("STAND"); tms.push_back("INSTTURN"); tms.push_back("WAIT");
  }
  else if(type == "combatAI")
  {
    tms.push_back("MELEE"); tms.push_back("M_QUICK"); tms.push_back("M_STRONG"); tms.push_back("RANGED");
    tms.push_back("R_QUICK"); tms.push_back("R_MINIG"); tms.push_back("R_BFG");
  }
  else if(type == "subtype")
  {
    tms.push_back("SPIKE");
  }
  else if(type == "t_atk")
  {
    tms.push_back("T_SLOW");
    tms.push_back("T_FAST");
    tms.push_back("T_SPREAD");
    tms.push_back("T_BLADE");
  }
  else if(type == "t_move")
  {
    tms.push_back("T_STATIC");
    tms.push_back("T_FLIGHT");
    tms.push_back("T_GROUND");
    tms.push_back("T_NOCLIP");
  }
  else if(type == "s_type")
  {
    tms.push_back("S_WALL");
    tms.push_back("S_FLOOR");
  }
  else if(type == "LvlName")
  {
    for(int i = 0; i < getLevelArray().size(); i++)
    {
      tms.push_back(getLevelArray()[i]);
    }
  }
  return tms;
}

double randomDouble(double min, double max)
{
  return (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
}
