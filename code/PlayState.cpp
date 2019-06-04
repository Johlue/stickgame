#include "PlayState.h"
#include <iostream>

PlayState::PlayState()
{}

PlayState::PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs)
{
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  //TODO some other stuff
  ui.setDisplay(mDisplay);
  init();
}

PlayState::~PlayState()
{}

void PlayState::init()
{
  for(int i = 0; i < 1; i++)
  {
    //objects.push_back( new Boundary (365+i, 0, 365+i, 260, mDisplay, false, false, true, false)); // right facing
  }
  //objects.push_back( new Boundary(0, 400, 300, 300, mDisplay, true, false, false, true)); //diagonal up, left

    objects.push_back( new Boundary(64, 200, 64, 160, mDisplay, false, false, false, true)); // left
    objects.push_back( new Boundary(404, 200, 404, 160, mDisplay, false, false, true, false)); // right
  objects.push_back( new Boundary(64, 200, 404, 200, mDisplay, false, true, false, false)); // down facing line
  objects.push_back( new Boundary(64, 160, 404, 160, mDisplay, true, false, false, false)); // up facing line

    objects.push_back( new Boundary(64, 300, 64, 260, mDisplay, false, false, true, false)); // left
    objects.push_back( new Boundary(404, 300, 404, 260, mDisplay, false, false, false, true)); // right
  objects.push_back( new Boundary(64, 300, 404, 300, mDisplay, true, false, false, false)); // down facing line
  objects.push_back( new Boundary(64, 260, 404, 260, mDisplay, false, true, false, false)); // up facing line

  objects.push_back (new Hazard(200, 110, 50, 50, SPIKE, UP, 64, mDisplay));
  objects.push_back (new Hazard(800, 110, 150, 150, SPIKE, UP, 64, mDisplay));

  objects.push_back (new Turret(200, 200, mDisplay, &objects));

  objects.push_back( new Player(101, 101, &playerAlive, mDisplay, &objects));
  for(int i2 = 0; i2 < objects.size(); i2++)
  {
    if(objects[i2]->getType() == PLAYER)
    {
      currentPlayer = dynamic_cast<Player*>(objects[i2]);
      ui.setPlayer(currentPlayer);
      break;
    }
  }
}

void PlayState::freeMem()
{
	for(int i = 0; i < objects.size(); i++)
	{
		delete (objects[i]);
	}
	objects.clear();
}

void PlayState::update()
{
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->update();
    if(!objects[i]->isAlive())
    {
      delete (objects[i]);
      objects.erase(objects.begin() + i);
      ui.setDeadPlayer(true);
    }
    //std::cout << "update";
    if(!playerAlive)
    {
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == PLAYER)
        {
          delete (objects[i]);
          objects.erase(objects.begin() + i);
        }
      }
    }
    else
    {
      if(currentPlayer != nullptr)
      {
        cameraX = currentPlayer->getX() - 320+16;// -half.screenwidth +half.playerwidth
        cameraY = currentPlayer->getY() - 240+32;
        if(cameraX < 0) cameraX = 0;
        if(cameraY < 0) cameraY = 0;
      }
    }
  }
}

void PlayState::render()
{
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->render(cameraX, cameraY);
    //std::cout << "render";
  }
  ui.render();
}

void PlayState::handleEvents(SDL_Event* e)
{

  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->handleEvent(e);
    //std::cout << "event";
  }
  if(e->type == SDL_KEYDOWN)
  {
    switch(e->key.keysym.sym)
    {
      case SDLK_r:
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == PLAYER)
        {
          delete (objects[i]);
          objects.erase(objects.begin() + i);
        }
      }
      objects.push_back( new Player(101, 101, &playerAlive, mDisplay, &objects));
      playerAlive = true;

      // find player and add his location to the variable tracking thing
      for(int i2 = 0; i2 < objects.size(); i2++)
      {
        if(objects[i2]->getType() == PLAYER)
        {
          playerVectorLocation = i2;
          currentPlayer = dynamic_cast<Player*>(objects[i2]);
          ui.setPlayer(currentPlayer);
          ui.setDeadPlayer(false);
          break;
        }
      }
      break;

      case SDLK_ESCAPE:
      *currentState = MENUSTATE;
      break;
    }
  }
}
