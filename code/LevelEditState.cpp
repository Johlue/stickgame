#include "LevelEditState.h"


LevelEditState::LevelEditState()
{}

LevelEditState::LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  mWriter = texS;
  init();
}

LevelEditState::~LevelEditState()
{
  freeMem();
}


void LevelEditState::init()
{
  menu.setPointers(currentEditorObject, &createObject);
  menu.setTextureArray(textureArray);

/* this stuff is for actaully drawing the texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 20; // controls the width of the rect
    Message_rect.h = 30; // controls the height of the rect

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(mDisplay->getRenderer(), Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Don't forget too free your surface and texture
    TTF_CloseFont( font );
    delete font;
    font = NULL;
    SDL_FreeSurface(surfaceMessage); SDL_DestroyTexture(Message);
    delete surfaceMessage; delete Message;
    surfaceMessage = nullptr; Message = nullptr;

  }*/
}

void LevelEditState::freeMem()
{
  for(int i = 0; i < objects.size(); i++)
  {
    delete objects[i]; // delete everything
    objects[i] = nullptr;
  }
  objects.clear();
}

void LevelEditState::handleEvents(SDL_Event* e)
{
  clicked = false;
  if(objects.size() != 0)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      if(objects[i]->handleEvents(e, cameraX, cameraY))
      {
        currentEditorObject = objects[i]; // choose editor object for editing if it got clicked
        clicked = true;
        break;
      }
    }
  }
  clicked = menu.handleEvents(e);
  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_ESCAPE:
      *currentState = MENUSTATE; // escape to return to menu
      break;

      case SDLK_DOWN: // arrows to move camera
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

      case SDLK_RCTRL: // right ctrl to make camera movement faster
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

      case SDLK_DELETE:
      if(currentEditorObject == nullptr) break;
      deleteObject(currentEditorObject->getIndex()); // remove currently chosen object
      currentEditorObject = nullptr;
      break;

      case SDLK_d: // dump some info to the console
      std::cout << "x: " << cameraX << " y: " << cameraY << " createObj: " << createObject << "bx: " << bx << "by: " << by << " currentEO: ";
      if(currentEditorObject != nullptr) std::cout << currentEditorObject << std::endl; else std::cout << "NaN\n";
      break;

    }
  }
  if(e->type == SDL_MOUSEBUTTONUP && !clicked)
  {
    mouseEvent(e->button); // used to determite which mouse button was pressed
  }
}

void LevelEditState::update()
{
  currentFrame += 1;
  cameraX += xMovement * speedMultiplier;
  cameraY += yMovement * speedMultiplier;
  //std::cout << "x: " << cameraX << "    y: " << cameraY << std::endl;
}

void LevelEditState::render()
{
  if(objects.size() > 0)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      objects[i]->render(cameraX, cameraY);
    }
  }

  if(currentEditorObject != nullptr) // if an editable is chose create a box around it
  {
    int clr = 188;
    if(currentFrame % 30 > 15) clr = 0;
    // draw currently chosen object at the upper left corner
    currentEditorObject->render(currentEditorObject->getX()-5, currentEditorObject->getY()-5);
    // draw box around currently chosen object
    int cx = currentEditorObject->getX(); int cy = currentEditorObject->getY();
    int cw = currentEditorObject->getWidth(); int ch = currentEditorObject->getHeight();
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), clr, clr, clr, 0xFF );
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy-cameraY-2   , cx+cw-cameraX+1, cy-cameraY-2   );
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy-cameraY-2   , cx-cameraX-2   , cy+ch-cameraY+1);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx+cw-cameraX+1, cy-cameraY-2   , cx+cw-cameraX+1, cy+ch-cameraY+1);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy+ch-cameraY+1, cx+cw-cameraX+1, cy+ch-cameraY+1);
  }
  if(bx != -9999999 && by != -9999999)
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
    int mx; int my;
    SDL_GetMouseState( &mx, &my );

    if(abs(bx - (mx + cameraX)) > abs(by - (my + cameraY))) my = by - cameraY;
    else mx = bx - cameraX;

    SDL_RenderDrawLine(mDisplay->getRenderer(), bx - cameraX, by - cameraY, mx, my);
  }
  menu.render();
}

void LevelEditState::changeState(int s)
{
  *currentState = s;
}

void LevelEditState::mouseEvent(SDL_MouseButtonEvent& b)
{
  int mx; int my;
  SDL_GetMouseState( &mx, &my );

  if(b.button == SDL_BUTTON_RIGHT)
  {
   currentEditorObject = nullptr;
   clicked = true;
   bx = -9999999; by = -9999999;
  }
  else if(b.button == SDL_BUTTON_LEFT)
  {
    if(createObject != EO_NONE) // if creating an object
    {
      //add new object to list according to the createObject thingy
      if(createObject == EO_BOUNDARY)
      {
        if(bx == -9999999 || by == -9999999)
        {
          bx = mx + cameraX; by = my + cameraY;
        }
        else
        {
          if(abs(bx - (mx + cameraX)) > abs(by - (my + cameraY))) my = by - cameraY;
          else mx = bx - cameraX;
          objects.push_back(new EditorObject(createObject, mx + cameraX, my + cameraY, mDisplay));
          objects[objects.size() - 1]->setIndex(objects.size() - 1); // set index of new object
          objects[objects.size() - 1]->setX2Y2(bx, by);
          bx = -9999999; by = -9999999;
        }
      }
      else
      {
        objects.push_back(new EditorObject(createObject, mx + cameraX, my + cameraY, mDisplay));
        objects[objects.size() - 1]->setIndex(objects.size() - 1); // set index of new object
        bx = -9999999; by = -9999999;
      }
    }

  }
}

void LevelEditState::deleteObject(int ix)
{
  delete objects[ix];
  objects[ix] = nullptr;
  objects.erase(objects.begin() + ix);
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->setIndex(i);
  }
}
