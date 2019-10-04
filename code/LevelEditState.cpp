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
  if(currentEditorObject == nullptr) editableString = nullptr; // no editing strings while not editing objects

  clicked = false;

  if(currentEditorObject != nullptr)
  {
    if(e->type == SDL_MOUSEBUTTONUP )
    {
      clicked = currentEditorObject->editorClick(e->button, currentEditorObject->getStringVector().size(), &editableString);
    }
  }

  if(objects.size() != 0 && !clicked)
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
  if(!clicked) clicked = menu.handleEvents(e);
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
    if(editableString != nullptr) // can't but ifs in switch cases
    {
      if(editableString->size() < 7) // too big for ints can't use
      {
        if(editableString->compare("0") == 0) {*editableString = "";} // removes 0 from the front of the string

        if(e->key.keysym.sym == SDLK_0)      editableString->append("0"); // add appropriate number to string
        else if(e->key.keysym.sym == SDLK_1) editableString->append("1");
        else if(e->key.keysym.sym == SDLK_2) editableString->append("2");
        else if(e->key.keysym.sym == SDLK_3) editableString->append("3");
        else if(e->key.keysym.sym == SDLK_4) editableString->append("4");
        else if(e->key.keysym.sym == SDLK_5) editableString->append("5");
        else if(e->key.keysym.sym == SDLK_6) editableString->append("6");
        else if(e->key.keysym.sym == SDLK_7) editableString->append("7");
        else if(e->key.keysym.sym == SDLK_8) editableString->append("8");
        else if(e->key.keysym.sym == SDLK_9) editableString->append("9");
      }

      if(e->key.keysym.sym == SDLK_BACKSPACE) // remove last number from string
      {
        if(editableString->size() > 0) editableString->erase(editableString->end()-1, editableString->end());
        if(editableString->size() == 0) editableString->append("0");
      }

      if(editableString->size() == 0) editableString->append("0"); // adds 0 if string is empty
      if(editableString->size() > 0) currentEditorObject->applyChanges();
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
      std::cout << "string: " << editableString << std::endl;
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
  if(editableString != nullptr) mWriter->render(*editableString, 55, 5);
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
  menu.render(); // object choosing menu

  if(currentEditorObject != nullptr) // for drawing the editing menu
  {
    int yMod = 0;
    int EOProws = 0;
    if(currentEditorObject->getStringVector().size() > 9)
    {
      EOProws = (currentEditorObject->getStringVector().size()-1) / 9; //9+ = 1, 18+ = 2 etc.
      yMod = (currentEditorObject->getStringVector().size()-1) / 9; // how many rows
    }
    { // draw parameter editor box
      SDL_Rect rectT = {0,  480 - ((EOProws+1)*44) - 2, 640, 480};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 100, 100, 100, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }
    for(int i = 0; i < currentEditorObject->getStringVector().size(); i++) // go thru each EO_String
    { // draws the info of each parameter (up to 9 parameters / row)
      yMod = i / 9; //which row are we on
      { // draw box around parameter types
        SDL_Rect rectT = {5+((i%9)*70),  440 - (EOProws*44) + (yMod * 44), 64, 16};
        SDL_SetRenderDrawColor( mDisplay->getRenderer(), 188, 188, 188, 0xFF );
        SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
      }
      mWriter->render(currentEditorObject->getStringVector().at(i)->type, 5+((i%9)*70), 440 - (EOProws*44) + (yMod * 44)); // draw parameter types
      { // draw box around parameter values
        SDL_Rect rectT = {5+((i%9)*70),  460 - (EOProws*44) + (yMod * 44), 64, 16};
        SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 255, 255, 0xFF );
        SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
      }
      mWriter->render(currentEditorObject->getStringVector().at(i)->value, 5+((i%9)*70), 460 - (EOProws*44) + (yMod * 44));// draw parameter values
    }
  }
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
   editableString = nullptr;
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
