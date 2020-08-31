#include "ObjectMenu.h"

ObjectMenu::ObjectMenu()
{}

void ObjectMenu::render()
{
  if(mState == CLOSED || mState == OBJECTS) (*textureArray)[2]->render(x, y, 3);
  else (*textureArray)[2]->render(x, y, 2);

  if(mState == CLOSED || mState == ENEMIES) (*textureArray)[2]->render(x, y+50, 1);
  else (*textureArray)[2]->render(x, y+50, 0);

  if(mState == ENEMIES)
  {
    for(int i = 0; i < 4; i++) // rows
    {
      for(int j = 0; j < 3; j++) // columns
      {
        (*textureArray)[3]->render(x+(39*i), y+100+(59*j), i+(j*4));
      }
    }
  }
  else if(mState == OBJECTS)
  {
    for(int i = 0; i < 4; i++) // rows
    {
      for(int j = 0; j < 3; j++) // columns
      {
        (*textureArray)[4]->render(x+(39*i), y+100+(59*j), i+(j*4));
      }
    }
  }
}

bool ObjectMenu::handleEvents(SDL_Event* e)
{
  if(e->type == SDL_MOUSEBUTTONUP )
  {
    return mouseEvent(e->button);
  }
}


void ObjectMenu::setTextureArray(std::vector<ImageTexture*>* tA)
{
  textureArray = tA;
}

bool ObjectMenu::mouseEvent(SDL_MouseButtonEvent& b)
{
  std::cout << *createObject << std::endl;
  bool clicked = false;
  //Get mouse position
  int mx, my;
  SDL_GetMouseState( &mx, &my );

  if(b.button == SDL_BUTTON_LEFT)
  {
    //Check if mouse is NOT outside button
    if( !( mx < x ||  mx > x + mWidth || my < y || my > y + mHeight)  )
    {
      clicked = true;
      if(mState == CLOSED || mState == OBJECTS) mState = ENEMIES; // change states to enemies when button is clicked
      else if(mState == ENEMIES) mState = CLOSED; // if already enemies close button
    }
    else if(  !(mx < x ||  mx > x + mWidth || my < y + 50 || my > y + 50 + mHeight)  )
    {
      clicked = true;
      if(mState == CLOSED || mState == ENEMIES) mState = OBJECTS; // change state to objects when button is clicked
      else if(mState == OBJECTS) mState = CLOSED;
    }

    if(mState != CLOSED &&
      !(mx < x || mx > x + mWidth || my < y + 100 || my > y + (squareHeight * 3) + 100)  // this is the area of the object grid
    ) // picking objects from the menu
    {
      int createObjectId = 0;                       // objects menu starts at 0
      if(mState == ENEMIES) createObjectId += 1000; // enemies menu starts at 1000

      createObjectId += (mx - x)/squareWidth;
      createObjectId += ((my - (y+100))/squareHeight)*4;

      if((createObjectId >= 0 && createObjectId <= EO_OBJECT_LIST_END-1) || (createObjectId >= 1000 && createObjectId <= EO_ENEMY_LIST_END-1)) // this needs to be regularily updated
      *createObject = createObjectId;
      clicked = true;
    }
  }
  else if(b.button == SDL_BUTTON_RIGHT)
  {
    *createObject = EO_NONE;
  } // on right click cancel object creation
  return clicked;
}

void ObjectMenu::setPointers(EditorObject * ceo, int * co)
{
  currentEditorObject = ceo;
  createObject = co;
}

void ObjectMenu::setX(int o_x){x = o_x;}
void ObjectMenu::setY(int o_y){y = o_y;}
