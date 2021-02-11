#include "EditorObject.h"

EditorObject::EditorObject(){}

EditorObject::EditorObject(int typ, int xl, int yl, Display * disp)
{
  type = typ;
  x = xl;
  y = yl;
  mDisplay = disp;
  constructStringInfo();
}

EditorObject::~EditorObject()
{
  if(stringInfo.size() > 0)
  {
    for(int i = 0; i < stringInfo.size(); i++)
    {
      delete stringInfo[i];
      stringInfo[i] = nullptr;
    }
    stringInfo.clear();
  }
}

void EditorObject::objectDeleted(int dl)
{
  for(int i = 0; i < stringInfo.size(); i++)
  {
    if(stringInfo[i]->type == "connect" && stringInfo[i]->value.size() > 0)
    {
      std::vector<std::string> strVec;
      strVec = splitString(stringInfo[i]->value, '|');

      int deleteConnection = -1;

      // add stuff to newValue based on ...stuff, and then replace value with newValue
      std::string newValue = "";
      for(int i2 = 0; i2 < strVec.size(); i2++)
      {
        if(std::stoi(strVec[i2]) == dl){deleteConnection = i2;}
        else
        {
          if(i2 > 0) {newValue += "|";}
          if(std::stoi(strVec[i2]) > dl) {newValue += std::to_string(std::stoi(strVec[i2])-1);}
          else {newValue += strVec[i2];}
        }
      }

      stringInfo[i]->value = newValue;
    }
  }
}

void EditorObject::dragged(int offsetX, int offsetY, int cameraX, int cameraY)
{
  if(type != EO_BOUNDARY)
  {
    int mx, my;
    SDL_GetMouseState( &mx, &my);
    mx += cameraX - offsetX; my += cameraY - offsetY;
    x = mx;
    y = my;
    for(int i = 0; i < stringInfo.size(); i++)
    {
      if(stringInfo[i]->type == "x") stringInfo[i]->value = std::to_string(mx);
      if(stringInfo[i]->type == "y") stringInfo[i]->value = std::to_string(my);
    }

  }
  else
  {
    int tx = abs(x - x2);
    int ty = abs(y - y2);

    int mx, my;
    SDL_GetMouseState( &mx, &my);
    mx += cameraX; my += cameraY;
    x = mx;
    y = my;
    x2 = x + tx;
    y2 = y + ty;
    for(int i = 0; i < stringInfo.size(); i++)
    {
      if(stringInfo[i]->type == "x") stringInfo[i]->value = std::to_string(x);
      if(stringInfo[i]->type == "y") stringInfo[i]->value = std::to_string(y);
      if(stringInfo[i]->type == "x2") stringInfo[i]->value = std::to_string(x2);
      if(stringInfo[i]->type == "y2") stringInfo[i]->value = std::to_string(y2);
    }
  }
}

void EditorObject::update()
{
  if(stringInfo[0]->value == "Walker")
  {
    // 3 is combatAI
    if(stringInfo[3]->value == "M_STRONG" || stringInfo[3]->value == "R_MINIG")
    {
      //big guys
      width = 30;
      height = 60;
    }
    else
    {
      width = 20;
      height = 40;
    }
  }
  else if(stringInfo[0]->value == "Hazard")
  {
    width = std::stoi(stringInfo[3]->value);
    if(width < 10) {width = 10;}
    height = std::stoi(stringInfo[4]->value);
    if(height < 10) {height = 10;}
  }
  else if(stringInfo[0]->value == "Turret")
  {
    width = 20;
    height = 20;
  }
  else if(stringInfo[0]->value == "Switch")
  {
    if(stringInfo[3]->value == "S_WALL")
    {
      width = 16;
      height = 16;
    }
    else if(stringInfo[3]->value == "S_FLOOR")
    {
      width = 32;
      height = 8;
    }
  }
  else if(stringInfo[0]->value == "Player")
  {
    width = 16;
    height = 32;
  }
  else if(stringInfo[0]->value == "Exit")
  {
    width = 40;
    height = 100;
  }
}

bool EditorObject::handleEvents(SDL_Event * e, int cameraX, int cameraY)
{
  return false;
}

void EditorObject::render(int camX, int camY)
{
  if(type == EO_BOUNDARY){boundaryRender(camX, camY);}
  else if(type == EO_PLAYER){playerRender(camX, camY);}
  else if(type == EO_TURRET){turretRender(camX, camY);}
  else if(type == EO_SWITCH){switchRender(camX, camY);}
  else if(type == EO_SPIKE) {hazardRender(camX, camY);}
  else if(type == EO_WALKER_M){walkerRender(camX, camY);}
  else
  {
    SDL_Rect rect2 = { x - camX, y - camY, width, height};
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), type * 50, type * 33, type * 100, 0xFF );
    SDL_RenderFillRect(mDisplay->getRenderer(), &rect2);
  }
}

void EditorObject::walkerRender(int camX, int camY)
{
  if(stringInfo[3]->value == "M_STRONG" || stringInfo[3]->value == "R_MINIG")
  {
    (*textureArray)[TEX_ENEMY_LARGE_BODY]->render(x - camX, y - camY, 0, NULL, NULL, NULL, flip);
  }
  else
  {
    (*textureArray)[TEX_ENEMY_NORMAL_BODY]->render(x - camX, y - camY, 0, NULL, NULL, NULL, flip);
  }

  if(     stringInfo[3]->value == "MELEE")     {(*textureArray)[TEX_ENEMY_SWORD_HAND]->render(x - 10 - camX, y - 20 - camY, 0, NULL, NULL, NULL, flip);}
  else if(stringInfo[3]->value ==  "M_QUICK")  {(*textureArray)[TEX_ENEMY_DAGGER_HAND]->render(x - 10 - camX, y - camY, 0, NULL, NULL, NULL, flip);}
  else if(stringInfo[3]->value ==  "M_STRONG") {(*textureArray)[TEX_ENEMY_BALL_HAND]->render(x - 15 - camX, y - camY, 0, NULL, NULL, NULL, flip);}
  else if(stringInfo[3]->value ==  "RANGED")   {(*textureArray)[TEX_ENEMY_PISTOL_HAND]->render(x - 13 - camX, y - camY, 0, NULL, NULL, NULL, flip);}
  else if(stringInfo[3]->value ==  "R_QUICK")  {(*textureArray)[TEX_ENEMY_SMG_HAND]->render(x - 13 - camX, y - camY, 0, NULL, NULL, NULL, flip);}
  else if(stringInfo[3]->value ==  "R_MINIG")  {(*textureArray)[TEX_ENEMY_MINIGUN_HAND]->render(x - 10 - camX, y - camY, 0, NULL, NULL, NULL, flip);}

  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);
  int cx = x + (width/2) - camX;
  int cy = y + 5 - camY;
  if(     stringInfo[5]->value == "RIGHT")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx, cy, cx + 20, cy);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx + 20, cy, cx + 15, cy + 5);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx + 20, cy, cx + 15, cy - 5);
  }
  else if(stringInfo[5]->value == "LEFT")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx, cy, cx - 20, cy);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx - 20, cy, cx - 15, cy + 5);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx - 20, cy, cx - 15, cy - 5);
  }
}

void EditorObject::hazardRender(int camX, int camY)
{
  int topX = x + (width/2) - camX; int topY = y            - camY;
  int rightX = x + width   - camX; int rightY = y + height - camY;
  int leftX = x            - camX; int leftY = y + height  - camY;
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
  SDL_RenderDrawLine(mDisplay->getRenderer(), topX, topY, rightX, rightY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), topX, topY, leftX, leftY);
  SDL_RenderDrawLine(mDisplay->getRenderer(), rightX, rightY, leftX, leftY);
}

void EditorObject::switchRender(int camX, int camY)
{
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
  SDL_RenderDrawLine(mDisplay->getRenderer(),
    x - camX, y - camY, x + width - camX, y - camY);
  SDL_RenderDrawLine(mDisplay->getRenderer(),
    x - camX, y - camY, x - camX, y + height - camY);
  SDL_RenderDrawLine(mDisplay->getRenderer(),
    x + width - camX, y - camY, x + width - camX, y + height - camY);
  SDL_RenderDrawLine(mDisplay->getRenderer(),
    x - camX, y + height - camY, x + width - camX, y + height - camY);
  if(stringInfo[7]->value == "T"){SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 255, 0, 0xFF);}
  else {SDL_SetRenderDrawColor(mDisplay->getRenderer(), 255, 0, 0, 0xFF);}
  SDL_Rect rect = { x + 1 - camX, y + 1 - camY, width - 1, height - 1};
  SDL_RenderFillRect(mDisplay->getRenderer(), &rect);
}

void EditorObject::turretRender(int camX, int camY)
{
  if(stringInfo[5]->value == "T")
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 100, 255, SDL_ALPHA_OPAQUE);
    drawCircle(mDisplay->getRenderer(), x - camX, y - camY, 10 + 2);
  }
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
  drawCircle(mDisplay->getRenderer(), x - camX, y - camY, 10);

  if(stringInfo[3]->value == "T_SLOW")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-3- camX, y-24- camY, x+3- camX, y-24- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-3- camX, y-24- camY, x-3- camX, y-10- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x+3- camX, y-24- camY, x+3- camX, y-10- camY);
  }
  else if(stringInfo[3]->value == "T_FAST")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-4- camX, y-20- camY, x+4- camX, y-20- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-4- camX, y-20- camY, x-4- camX, y-9- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x+4- camX, y-20- camY, x+4- camX, y-9- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x- camX, y-20- camY, x- camX, y-9- camY);
  }
  else if(stringInfo[3]->value == "T_SPREAD")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-8- camX, y-19- camY, x+8- camX, y-19- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-8- camX, y-19- camY, x-6- camX, y-8- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x+8- camX, y-19- camY, x+6- camX, y-8- camY);
  }
  else if(stringInfo[3]->value == "T_BLADE")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x- camX, y-38- camY, x-4- camX, y-9- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x- camX, y-38- camY, x+4- camX, y-9- camY);

    SDL_RenderDrawLine(mDisplay->getRenderer(), x- camX, y+38- camY, x+4- camX, y+9- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x- camX, y+38- camY, x-4- camX, y+9- camY);

    SDL_RenderDrawLine(mDisplay->getRenderer(), x-38- camX, y- camY, x-9- camX, y-4- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x-38- camX, y- camY, x-9- camX, y+4- camY);

    SDL_RenderDrawLine(mDisplay->getRenderer(), x+38- camX, y- camY, x+9- camX, y+4- camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x+38- camX, y- camY, x+9- camX, y-4- camY);
  }
}

void EditorObject::playerRender(int camX, int camY)
{
  (*textureArray)[TEX_PLAYER_BODY]->render(x - camX, y - camY, 0);
  (*textureArray)[TEX_PLAYER_GUN]->render(x-8 - camX, y - camY, 2);
}

void EditorObject::boundaryRender(int camX, int camY)
{
  // 5 = up | 6 = down | 7 = -> | 8 = <-
  SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
  SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y - camY, x2 - camX, y2 - camY);
  // draw an arrow towards the direction that is inpassable at the middle of the boundary
  // repeated 4 times cause I'm lazy
  if(stringInfo[5]->value == "T")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) - camX, y - 20 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) + 5 - camX, y - 5 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) - 5 - camX, y - 5 - camY);
  }
  if(stringInfo[6]->value == "T")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) - camX, y + 20 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) + 5 - camX, y + 5 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x + (abs(x - x2)/2) - camX, y - camY, x + (abs(x - x2)/2) - 5 - camX, y + 5 - camY);
  }
  if(stringInfo[7]->value == "T")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x + 20 - camX, y + (abs(y - y2)/2) - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x + 5 - camX, y + (abs(y - y2)/2) + 5 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x + 5 - camX, y + (abs(y - y2)/2) - 5 - camY);
  }
  if(stringInfo[8]->value == "T")
  {
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x - 20 - camX, y + (abs(y - y2)/2) - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x - 5 - camX, y + (abs(y - y2)/2) + 5 - camY);
    SDL_RenderDrawLine(mDisplay->getRenderer(), x - camX, y + (abs(y - y2)/2) - camY, x - 5 - camX, y + (abs(y - y2)/2) - 5 - camY);
  }
}

bool EditorObject::clickedEdit(int cameraX, int cameraY)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );
  mx += cameraX; my += cameraY;
  if(type == EO_BOUNDARY){mx +=2; my +=2;} // adjust mouse location to make up for wonky hitbox
  if(type == EO_TURRET){mx += 10; my += 10;}
  // if mouse is inside button return true;
  if( !( mx < x ||  mx > x + width || my < y || my > y + height)  )
  {
    return true;
  }
  return false;
}

bool EditorObject::clickedDrag(int cameraX, int cameraY)
{
  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );
  mx += cameraX; my += cameraY;

  // adjust mouse location to make up for wonky hitbox
  if(type == EO_BOUNDARY){ std::cout << "bound"; mx +=2; my +=2;}
  if(type == EO_TURRET){mx += 10; my += 10;}

  // if mouse is inside button return true;
  if( !( mx < x ||  mx > x + width || my < y || my > y + height)  )
  {
    //clickDragged = true;
    return true;
  }
  return false;
}

bool EditorObject::mouseEvent(SDL_MouseButtonEvent& b, int cameraX, int cameraY)
{

  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );
  mx += cameraX; my += cameraY;

  if(type == EO_BOUNDARY){mx += 2; my += 2;} // adjust mouse location to make up for wonky hitbox
  if(type == EO_TURRET){mx += 10; my += 10;}

  if(b.button == SDL_BUTTON_LEFT)
  {
    if( !( mx < x ||  mx > x + width || my < y || my > y + height)  )
    {
      return true;
    }
  }
  return false;
}

void EditorObject::saveLevel(){}

void EditorObject::loadLevel(){}

void EditorObject::constructStringInfo()
{
  if(type != EO_NONE) // add x and y to the thing if it's not an empty object
  {
    stringInfo.push_back(new EO_String("Type", "type")); // type is added, to not mess up the order of things
    stringInfo.push_back(new EO_String(std::to_string(x), "x"));
    stringInfo.push_back(new EO_String(std::to_string(y), "y"));
  }
  switch(type)
  {
    case EO_NONE:
    stringInfo[0]->value = "None";
    break;

    case EO_BOUNDARY:
    stringInfo[0]->value = "Boundary";
    stringInfo.push_back(new EO_String(std::to_string(0), "x2"));
    stringInfo.push_back(new EO_String(std::to_string(0), "y2"));
    stringInfo.push_back(new EO_String("F", "face ^"));
    stringInfo.push_back(new EO_String("F", "face v"));
    stringInfo.push_back(new EO_String("F", "face ->"));
    stringInfo.push_back(new EO_String("F", "face <-"));
    break;

    case EO_WALKER_M:
    stringInfo[0]->value = "Walker";
    stringInfo.push_back(new EO_String("MELEE", "combatAI"));
    stringInfo.push_back(new EO_String("WAIT", "walkAI"));
    stringInfo.push_back(new EO_String("LEFT", "facing"));
    break;

    case EO_SPIKE:
    stringInfo[0]->value = "Hazard";
    stringInfo.push_back(new EO_String("30", "width"));
    stringInfo.push_back(new EO_String("30", "height"));
    stringInfo.push_back(new EO_String("0", "angle"));
    stringInfo.push_back(new EO_String("50", "damage"));
    stringInfo.push_back(new EO_String("SPIKE", "subtype"));
    break;

    case EO_TURRET:
    stringInfo[0]->value = "Turret";
    stringInfo.push_back(new EO_String("T_SLOW", "t_atk"));
    stringInfo.push_back(new EO_String("T_STATIC", "t_move"));
    stringInfo.push_back(new EO_String("F", "invincib"));
    stringInfo.push_back(new EO_String("F", "active"));
    break;

    case EO_SWITCH:
    stringInfo[0]->value = "Switch";
    stringInfo.push_back(new EO_String("S_WALL", "s_type"));
    stringInfo.push_back(new EO_String("F", "one_time"));
    stringInfo.push_back(new EO_String("0", "timer"));
    stringInfo.push_back(new EO_String("", "connect"));
    stringInfo.push_back(new EO_String("F", "active"));
    break;

    case EO_EXIT:
    stringInfo[0]->value = "Exit";
    stringInfo.push_back(new EO_String("level", "LvlName"));
    stringInfo.push_back(new EO_String("F", "active"));
    break;

    case EO_PLAYER:
    stringInfo[0]->value = "Player";
    break;

  }
  update();
}

void EditorObject::setIndex(int i){index = i;}
int EditorObject::getIndex(){return index;}
int EditorObject::getX()
{
  if(type == EO_TURRET) return x - 10;
  return x;
}
int EditorObject::getY()
{
  if(type == EO_TURRET) return y - 10;
  return y;
}
int EditorObject::getWidth() {return width;} int EditorObject::getHeight(){return height;}
int EditorObject::getType() {return type;}
void EditorObject::setX2Y2(int xs, int ys)
{
  if(type == EO_BOUNDARY)
  {
    // sets x to the right and x2 to the left, and y to top and y2 to bottom
    if(xs < x) {x2 = x; x = xs;}
    else {x2 = xs;}
    if(ys < y) {y2 = y; y = ys;}
    else {y2 = ys;}
    width = abs(x - x2) + 4;
    height = abs(y - y2) + 4;
    //std::cout << "y: " << y << " x: " << x << " x2: " << x2 << " y2: " << y2 << std::endl;
    for(int i= 0; i < stringInfo.size(); i++)
    {
      // reorganize string info
      if(stringInfo[i]->type == "x") stringInfo[i]->value = std::to_string(x);
      if(stringInfo[i]->type == "y") stringInfo[i]->value = std::to_string(y);
      if(stringInfo[i]->type == "x2") stringInfo[i]->value = std::to_string(x2);
      if(stringInfo[i]->type == "y2") {stringInfo[i]->value = std::to_string(y2); break;}
    }
  }
  else {x2 = xs; y2 = ys;}
}
std::vector<EO_String*> EditorObject::getStringVector(){return stringInfo;}

int EditorObject::getOpenedMenu(){return openedMenu;}

void EditorObject::applyChanges()
{
  for(int i = 0; i < stringInfo.size(); i++)
  {
    if(stringInfo[i]->type == "x") x = std::stoi(stringInfo[i]->value);
    if(stringInfo[i]->type == "y") y = std::stoi(stringInfo[i]->value);
    if(stringInfo[i]->type == "x2") x2 = std::stoi(stringInfo[i]->value);
    if(stringInfo[i]->type == "y2") y2 = std::stoi(stringInfo[i]->value);
  }
}

int EditorObject::editorClick(SDL_MouseButtonEvent& b, int strings, std::string ** es)
{

    if(b.button == SDL_BUTTON_RIGHT)
    {
      clickDragged = false;
      openedMenu = -1;
      return false;
    }
    int rtValue = ECR_CLICK_FALSE;
    //Get mouse position
    int mx, my;
    SDL_GetMouseState( &mx, &my );
    int EOProws = 0; int yMod;

    if(strings > 9)
    {
      EOProws = (strings - 1) / 9; //9+ = 1, 18+ = 2 etc.
    }

    //if a dropdown menu is open
    if(openedMenu != -1)
    {
      yMod = openedMenu/9;
      std::vector<std::string> tms = menuOptions(stringInfo[openedMenu]->type);
      if(tms.size() > 0)
      {
        for(int i2 = 0; i2 < tms.size(); i2++)
        {
          //is mouse inside the currently processed option
          if(  mx > 5+((openedMenu%9)*70)-1
            && mx < 5+((openedMenu%9)*70)-1 + 64 + 2
            && my > (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44) - (17 * i2) - 1
            && my < (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44) - (17 * i2) - 1 + 16 + 2)
          {
            stringInfo[openedMenu]->value = tms[i2]; // change value to chosen one
            rtValue = ECR_CLICK_TRUE; // also a click happened
            update();
            break;
          }
        }
      }
    }

    // return true or false?
    if(my > mDisplay->getHeight() - ((EOProws+1)*44) - 2) rtValue = ECR_CLICK_TRUE;

    for(int i = 0; i < strings; i++)
    {
      yMod = i / 9; //which row are we on
      if(  mx > 5+((i%9)*70) && mx < (5+((i%9)*70)) + 64 //is being clicked inside value?
        && my > (mDisplay->getHeight() - 20) - (EOProws*44) + (yMod * 44) && my < ((mDisplay->getHeight() - 20) - (EOProws*44) + (yMod * 44)) + 16)
      {
        // if value is a number
        if(stringInfo[i]->type == "x" || stringInfo[i]->type == "y" || stringInfo[i]->type == "x2" ||
           stringInfo[i]->type == "y2" || stringInfo[i]->type == "width" || stringInfo[i]->type == "height" ||
           stringInfo[i]->type == "angle" || stringInfo[i]->type == "damage" || stringInfo[i]->type == "timer")
        {
          *es = &(stringInfo[i]->value);
           //do number things
           openedMenu = -1; // close other menus
        }
        // if value is a boolean
        else if(stringInfo[i]->type == "face ->" || stringInfo[i]->type == "face <-" ||
        stringInfo[i]->type == "face v" || stringInfo[i]->type == "face ^" ||
        stringInfo[i]->type == "one_time" || stringInfo[i]->type == "invincib" || stringInfo[i]->type == "active")
        {
          if(stringInfo[i]->value == "F") // if false clicked becomes true, others become false
          {
            for(int i2 = 0; i2 < strings; i2++)
            {
              if(stringInfo[i2]->type == "face ->" || stringInfo[i2]->type == "face <-" || // set all to faces to false
              stringInfo[i2]->type == "face v" || stringInfo[i2]->type == "face ^")
              {
                stringInfo[i2]->value = "F";
              }
            }
            stringInfo[i]->value = "T";
          }
          else {stringInfo[i]->value = "F";} // if false becomes true

          openedMenu = -1; // close other menus
          *es = nullptr;
        }
        // value is direction (this gets its own category cause Im lazy)
        else if(stringInfo[i]->type == "facing")
        {
          if(stringInfo[i]->value == "LEFT") stringInfo[i]->value = "RIGHT";
          else stringInfo[i]->value = "LEFT";
        }
        // if value is a multi-connector thingy
        else if(stringInfo[i]->type == "connect")
        {
          rtValue = ECR_CLICK_CONNECTION;
          openedMenu = -1;
        }
        // value is multiple choice
        else
        {
            std::cout << "Number: "<< i << " button pressed\n";
            openedMenu = i;
            *es = nullptr;
        }

      }
    }
    std::cout << "rtValue: " << rtValue << std::endl;
    return rtValue;
}

void EditorObject::setTextureArray(std::vector<ImageTexture*>* tA)
{
  textureArray = tA;
}

void EditorObject::setOpenedMenu(int om)
{
  openedMenu = om;
}
