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
  menu.setX(mDisplay->getWidth() - 170);
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

  // mouse stuff, specifically mouse button up things
  if(e->type == SDL_MOUSEBUTTONUP)
  {
    int mx; int my;
    SDL_GetMouseState( &mx, &my );

    if(e->button.button == SDL_BUTTON_LEFT) // left mousebutton selects
    {
      if(menu.handleEvents(e))
      {
        clickMode = MOUSE_CREATE;
        currentEditorObject = nullptr;
      }
      // if no menu clickings happened
      else
      {
        if(clickMode == MOUSE_EDIT)
        {
          if(currentEditorObject == nullptr || !currentEditorObject->editorClick(e->button, currentEditorObject->getStringVector().size(), &editableString))
          {
            //choose a editable object
            for(int i = 0; i < objects.size(); i++)
            {
              if(objects[i]->clickedEdit(cameraX, cameraY))
              {
                currentEditorObject = objects[i];
                for(int i2 = 0; i2 < objects.size(); i2++) // close editor menus
                {
                  objects[i2]->setOpenedMenu(-1);
                }
              }
            }
          }
        }

        else if(clickMode == MOUSE_DRAG)
        {
          if(draggedIndex > -1)
          {
            draggedIndex = -1;
          }
          else
          {
            for(int i = 0; i < objects.size(); i++)
            {
              if(objects[i]->clickedDrag(cameraX, cameraY))
              {
                offsetX = mx - objects[i]->getX() + cameraX;
                offsetY = my - objects[i]->getY() + cameraY;
                if(objects[i]->getType() == EO_TURRET)
                {
                  offsetX -= 10;
                  offsetY -= 10;
                }
                draggedIndex = i;
                break;
              }
            }
          }
        }

        else if(clickMode == MOUSE_CREATE)
        {
          if(createObject != EO_NONE) // if creating an object
          {
            //add new object to list according to the createObject thingy
            if(createObject == EO_BOUNDARY || createObject == EO_BOX) // for two click creatables
            {
              if(bx == -9999999 || by == -9999999)
              {
                bx = mx + cameraX; by = my + cameraY;
              }
              else if(createObject == EO_BOUNDARY)
              {
                if(abs(bx - (mx + cameraX)) > abs(by - (my + cameraY))) my = by - cameraY;
                else mx = bx - cameraX;
                createBoundary( mx + cameraX, my + cameraY, bx, by);
                bx = -9999999; by = -9999999;
              }
              else if(createObject == EO_BOX)
              {
                createBoundary(mx + cameraX, my + cameraY, bx, my + cameraY);
                createBoundary(mx + cameraX, my + cameraY, mx + cameraX, by);
                createBoundary(bx, my + cameraY, bx, by);
                createBoundary(mx + cameraX, by, bx, by);

                bx = -9999999; by = -9999999;
              }
            }
            else
            {
              objects.push_back(new EditorObject(createObject, mx + cameraX, my + cameraY, mDisplay));
              objects[objects.size() - 1]->setTextureArray(textureArray);
              objects[objects.size() - 1]->setIndex(objects.size() - 1); // set index of new object
              bx = -9999999; by = -9999999;
            }
          }
        }
      }
    }
    else if(e->button.button == SDL_BUTTON_RIGHT) // right mousebutton cancels
    {
      loadingMode = false;
      savingMode = false;
      currentEditorObject = nullptr;
      createObject = EO_NONE;
      editableString = nullptr;
      bx = -9999999;
      by = -9999999;
    }

  }

  // camera movement controls
  if(e->type == SDL_KEYDOWN)
  {

    if(savingMode || loadingMode)
    {
      // writing the saving and loading file names
      switch(e->key.keysym.sym)
      {
        case SDLK_0: saveFileName.append("0"); break;
        case SDLK_1: saveFileName.append("1"); break;
        case SDLK_2: saveFileName.append("2"); break;
        case SDLK_3: saveFileName.append("3"); break;
        case SDLK_4: saveFileName.append("4"); break;
        case SDLK_5: saveFileName.append("5"); break;
        case SDLK_6: saveFileName.append("6"); break;
        case SDLK_7: saveFileName.append("7"); break;
        case SDLK_8: saveFileName.append("8"); break;
        case SDLK_9: saveFileName.append("9"); break;
        case SDLK_q: saveFileName.append("q"); break;
        case SDLK_w: saveFileName.append("w"); break;
        case SDLK_e: saveFileName.append("e"); break;
        case SDLK_r: saveFileName.append("r"); break;
        case SDLK_t: saveFileName.append("t"); break;
        case SDLK_y: saveFileName.append("y"); break;
        case SDLK_u: saveFileName.append("u"); break;
        case SDLK_i: saveFileName.append("i"); break;
        case SDLK_o: saveFileName.append("o"); break;
        case SDLK_p: saveFileName.append("p"); break;
        case SDLK_a: saveFileName.append("a"); break;
        case SDLK_s: saveFileName.append("s"); break;
        case SDLK_d: saveFileName.append("d"); break;
        case SDLK_f: saveFileName.append("f"); break;
        case SDLK_g: saveFileName.append("g"); break;
        case SDLK_h: saveFileName.append("h"); break;
        case SDLK_j: saveFileName.append("j"); break;
        case SDLK_k: saveFileName.append("k"); break;
        case SDLK_l: saveFileName.append("l"); break;
        case SDLK_z: saveFileName.append("z"); break;
        case SDLK_x: saveFileName.append("x"); break;
        case SDLK_c: saveFileName.append("c"); break;
        case SDLK_v: saveFileName.append("v"); break;
        case SDLK_b: saveFileName.append("b"); break;
        case SDLK_n: saveFileName.append("n"); break;
        case SDLK_m: saveFileName.append("m"); break;
        case SDLK_BACKSPACE:
        if(saveFileName.size() > 0) saveFileName.erase(saveFileName.end()-1, saveFileName.end());
        break;
        case SDLK_RETURN:
        if(savingMode)
        {
          std::string savefilenameforreals = saveFileName;
          savefilenameforreals.append(".txt");
          saveLevel(savefilenameforreals);
          savingMode = false;
        }
        else if(loadingMode)
        {
          std::string savefilenameforreals = saveFileName;
          savefilenameforreals.append(".txt");
          loadLevel(savefilenameforreals);
          loadingMode = false;
        }
        break;
      }
    }
    else
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

        case SDLK_s:
        loadingMode = false;
        savingMode = true;
        //saveLevel("testLevel.txt");
        break;

        case SDLK_l:
        savingMode = false;
        loadingMode = true;
        //loadLevel("testLevel.txt");
        break;
      }

      // object editor thingy
      if(editableString != nullptr) // can't put ifs in switch cases
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

      case SDLK_q:
      currentEditorObject = nullptr;
      createObject = EO_NONE;
      if(clickMode == MOUSE_EDIT)
      {
        clickMode = MOUSE_CREATE;
        break;
      }
      if(clickMode == MOUSE_CREATE)
      {
        clickMode = MOUSE_DRAG;
        break;
      }
      clickMode = MOUSE_EDIT;
      break;

      case SDLK_e:
      currentEditorObject = nullptr;
      createObject = EO_NONE;
      if(clickMode == MOUSE_EDIT)
      {
        clickMode = MOUSE_DRAG;
        break;
      }
      if(clickMode == MOUSE_CREATE)
      {
        clickMode = MOUSE_EDIT;
        break;
      }
      clickMode = MOUSE_CREATE;
      break;

      case SDLK_d: // dump some info to the console
      std::cout << "x: " << cameraX << " y: " << cameraY << " createObj: " << createObject << "bx: " << bx << "by: " << by << " currentEO: ";
      if(currentEditorObject != nullptr) std::cout << currentEditorObject << std::endl; else std::cout << "NaN\n";
      std::cout << "string: " << editableString << std::endl;
      break;

    }
  }
  /*
  if(e->type == SDL_MOUSEBUTTONUP && !clicked)
  {
    mouseEvent(e->button); // used to determite which mouse button was pressed
  }*/
}

void LevelEditState::update()
{
  currentFrame += 1;
  cameraX += xMovement * speedMultiplier;
  cameraY += yMovement * speedMultiplier;
  if(objects.size() > 0)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      objects[i]->update(cameraX, cameraY);
    }
  }
  if(currentEditorObject == nullptr) // close editor menus if no object is chosen
  {
    if(objects.size() > 0)
    {
      for(int i = 0; i < objects.size(); i++)
      {
        objects[i]->setOpenedMenu(-1);
      }
    }
  }
  if(draggedIndex > -1) // if currently dragging something
  {
    objects[draggedIndex]->dragged(offsetX, offsetY, cameraX, cameraY);
    if(clickMode != MOUSE_DRAG) draggedIndex = -1;
  }
}

void LevelEditState::render()
{
  mWriter->render("X: " + (std::to_string(cameraX)), 60, 5);
  mWriter->render("Y: " + (std::to_string(cameraY)), 135, 5);
  if(objects.size() > 0)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      objects[i]->render(cameraX, cameraY);
    }
  }

  // draw mouse mode icons
  switch(clickMode)
  {
    case MOUSE_EDIT:
    (*textureArray)[11]->render(5, 5, 0);
    break;

    case MOUSE_DRAG:
    (*textureArray)[10]->render(5, 5, 0);
    break;

    case MOUSE_CREATE:
    (*textureArray)[9]->render(5, 5, 0);
    break;
  }

  if(currentEditorObject != nullptr) // if an editable is chose create a box around it
  {
    int clr = 188;
    if(currentFrame % 30 > 15) clr = 0;

    // draw currently chosen object at the upper left corner
    currentEditorObject->render(currentEditorObject->getX()-5, currentEditorObject->getY()-65);

    // draw box around currently chosen object
    int cx = currentEditorObject->getX(); int cy = currentEditorObject->getY();
    int cw = currentEditorObject->getWidth(); int ch = currentEditorObject->getHeight();
    SDL_SetRenderDrawColor( mDisplay->getRenderer(), clr, clr, clr, 0xFF );
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy-cameraY-2   , cx+cw-cameraX+1, cy-cameraY-2   );
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy-cameraY-2   , cx-cameraX-2   , cy+ch-cameraY+1);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx+cw-cameraX+1, cy-cameraY-2   , cx+cw-cameraX+1, cy+ch-cameraY+1);
    SDL_RenderDrawLine(mDisplay->getRenderer(), cx-cameraX-2   , cy+ch-cameraY+1, cx+cw-cameraX+1, cy+ch-cameraY+1);
  }
  if(bx != -9999999 && by != -9999999) // drawing 2 point objects, line, box etc
  {
    SDL_SetRenderDrawColor(mDisplay->getRenderer(), 0, 0, 0, 0xFF);
    int mx; int my;
    SDL_GetMouseState( &mx, &my );

    if(createObject == EO_BOUNDARY)
    {
      if(abs(bx - (mx + cameraX)) > abs(by - (my + cameraY))) my = by - cameraY; // if x is longer draw the line only on x axis, else y
      else mx = bx - cameraX;

      SDL_RenderDrawLine(mDisplay->getRenderer(), bx - cameraX, by - cameraY, mx, my);
    }
    else if(createObject == EO_BOX)
    {
      SDL_RenderDrawLine(mDisplay->getRenderer(), mx, by - cameraY, mx, my);
      SDL_RenderDrawLine(mDisplay->getRenderer(), bx - cameraX, my, mx, my);
      SDL_RenderDrawLine(mDisplay->getRenderer(), bx - cameraX, by - cameraY, mx, by - cameraY);
      SDL_RenderDrawLine(mDisplay->getRenderer(), bx - cameraX, by - cameraY, bx - cameraX, my);
    }
  }
  menu.render(); // object choosing menu

  if(currentEditorObject != nullptr) // for drawing the object editing menu
  {
    int yMod = 0;
    int EOProws = 0;
    if(currentEditorObject->getStringVector().size() > 9)
    {
      EOProws = (currentEditorObject->getStringVector().size()-1) / 9; //9+ = 1, 18+ = 2 etc.
      yMod = (currentEditorObject->getStringVector().size()-1) / 9; // how many rows
    }
    { // draw parameter editor box
      SDL_Rect rectT = {0,  mDisplay->getHeight() - ((EOProws+1)*44) - 2, mDisplay->getWidth(), mDisplay->getHeight()};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 100, 100, 100, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }
    for(int i = 0; i < currentEditorObject->getStringVector().size(); i++) // go thru each EO_String
    { // draws the info of each parameter (up to 9 parameters / row)
      yMod = i / 9; //which row are we on
      { // draw box around parameter types
        SDL_Rect rectT = {5+((i%9)*70),  (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44), 64, 16};
        SDL_SetRenderDrawColor( mDisplay->getRenderer(), 188, 188, 188, 0xFF );
        SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
      }
      mWriter->render(currentEditorObject->getStringVector().at(i)->type, 5+((i%9)*70), (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44)); // draw parameter types
      { // draw box around parameter values
        SDL_Rect rectT = {5+((i%9)*70),  (mDisplay->getHeight() - 20) - (EOProws*44) + (yMod * 44), 64, 16};
        SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 255, 255, 0xFF );
        SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
      }
      mWriter->render(currentEditorObject->getStringVector().at(i)->value, 5+((i%9)*70), (mDisplay->getHeight() - 20) - (EOProws*44) + (yMod * 44));// draw parameter values
    }
    // draw currently opened menu
    int om = currentEditorObject->getOpenedMenu();
    if(om != -1) // if a multiple choice menu is open
    {
      yMod = om/9;
      std::vector<std::string> tms = menuOptions(currentEditorObject->getStringVector()[om]->type);
      if(tms.size() > 0)
      {
        for(int i2 = 0; i2 < tms.size(); i2++)
        {
          { // draw box and then a smaller box and fill it with text
            // black box for outlines
            {
              SDL_Rect rectT = {5+((om%9)*70)-1,  (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44) - (17 * i2)-1, 64+2, 16+2};
              SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
              SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
            }
            // actual text container
            {
              SDL_Rect rectT = {5+((om%9)*70),  (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44) - (17 * i2), 64, 16};
              SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 255, 255, 0xFF );
              SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
            }
            // draw options inside box
            mWriter->render(tms[i2], 5+((om%9)*70),  (mDisplay->getHeight() - 40) - (EOProws*44) + (yMod * 44) - (17 * i2));
          }
        }
      }
    }
  }

  // rendering load/save modes
  if(loadingMode || savingMode)
  {
    {
      SDL_Rect rectT = {(mDisplay->getWidth()/2)-250, (mDisplay->getHeight()/2)-125, 500, 250};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }
    {
      SDL_Rect rectT = {(mDisplay->getWidth()/2)-248, (mDisplay->getHeight()/2)-123, 496, 246};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 255, 255, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }

    {
      SDL_Rect rectT = {(mDisplay->getWidth()/2)-225, (mDisplay->getHeight()/2)-20, 450, 40};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 0, 0, 0, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }
    {
      SDL_Rect rectT = {(mDisplay->getWidth()/2)-223, (mDisplay->getHeight()/2)-18, 446, 36};
      SDL_SetRenderDrawColor( mDisplay->getRenderer(), 255, 255, 255, 0xFF );
      SDL_RenderFillRect(mDisplay->getRenderer(), &rectT);
    }
    std::string writeThisShitDown = saveFileName;
    writeThisShitDown.append(".txt");
    mWriter->render(writeThisShitDown, (mDisplay->getWidth()/2)-220, (mDisplay->getHeight()/2)-8);

    if(loadingMode)
    {
      mWriter->render("Load Level Name:", (mDisplay->getWidth()/2)-225, (mDisplay->getHeight()/2)-46);
    }
    else
    {
      mWriter->render("Save Level Name:", (mDisplay->getWidth()/2)-225, (mDisplay->getHeight()/2)-46);
    }

  }
}

void LevelEditState::changeState(int s)
{
  *currentState = s;
}


void LevelEditState::createBoundary(int x, int y, int x2, int y2)
{
  objects.push_back(new EditorObject(EO_BOUNDARY, x, y, mDisplay));
  objects[objects.size() - 1]->setTextureArray(textureArray);
  objects[objects.size() - 1]->setIndex(objects.size() - 1);
  objects[objects.size() - 1]->setX2Y2(x2, y2);
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

void LevelEditState::saveLevel(std::string lvlName)
{
  if(objects.size() > 0 && lvlName.size() > 0)
  {
    std::ofstream levelfile;
    levelfile.open(lvlName);
    for(int i = 0; i < objects.size(); i++)
    {
      for(int i2 = 0; i2 < objects[i]->getStringVector().size(); i2++)
      {
        levelfile << objects[i]->getStringVector().at(i2)->value;
        levelfile << " ";
      }
      levelfile << "\n";
    }
    levelfile.close();
  }
}

void LevelEditState::loadLevel(std::string lvlName)
{
  if(lvlName.size() > 0)
  {
    freeMem();
    std::string line;
    std::ifstream levelfile;
    levelfile.open(lvlName);
    if(levelfile.is_open())
    {
      while(std::getline(levelfile, line))
      {
        if(line != "") createObjectFromFile(line);
      }
    }
    else std::cout << "opening level file failed\n";
    levelfile.close();
  }
}

bool LevelEditState::createObjectFromFile(std::string sourceString)
{
  std::vector<std::string> pieces;
  pieces = splitString(sourceString, ' ');

  // first create a an appropriately tagged object
  if(pieces[0] == "Boundary")
  {
    objects.push_back(new EditorObject(EO_BOUNDARY, 0, 0, mDisplay));
    objects[objects.size() - 1]->setTextureArray(textureArray);
  }
  else if(pieces[0] == "Turret")
  {
    objects.push_back(new EditorObject(EO_TURRET, 0, 0, mDisplay));
    objects[objects.size() - 1]->setTextureArray(textureArray);
  }
  else if(pieces[0] == "Hazard")
  {
    objects.push_back(new EditorObject(EO_SPIKE, 0, 0, mDisplay));
    objects[objects.size() - 1]->setTextureArray(textureArray);
  }
  else if(pieces[0] == "Walker")
  {
    objects.push_back(new EditorObject(EO_WALKER_M, 0, 0, mDisplay));
    objects[objects.size() - 1]->setTextureArray(textureArray);
  }
  else if(pieces[0] == "Player")
  {
    objects.push_back(new EditorObject(EO_PLAYER, 0, 0, mDisplay));
    objects[objects.size() - 1]->setTextureArray(textureArray);
  }
  else return false;

  if(pieces.size() == objects.back()->getStringVector().size())
  {
    for(int i = 0; i < pieces.size(); i++)
    {
      objects.back()->getStringVector().at(i)->value = pieces[i];
      objects.back()->applyChanges();
    }
    // this is for width/height
    if(pieces[0] == "Boundary") objects.back()->setX2Y2(std::stoi(pieces[3]), std::stoi(pieces[4]));
  }
  else return false;

  return false;
}
