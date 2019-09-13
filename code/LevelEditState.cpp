#include "LevelEditState.h"


LevelEditState::LevelEditState()
{}

LevelEditState::LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
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
  clicked = false;
  if(objects.size() != 0)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      if(objects[i]->handleEvents(e))
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
      std::cout << "x: " << cameraX << " y: " << cameraY << " createObj: " << createObject << " currentEO: ";
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
  }
  else if(b.button == SDL_BUTTON_LEFT)
  {
    if(createObject != EO_NONE) // if creating an object
    {
      //add new object to list according to the createObject thingy
      objects.push_back(new EditorObject(createObject, mx + cameraX, my + cameraY, mDisplay));
      objects[objects.size() - 1]->setIndex(objects.size() - 1); // set index of new object
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
