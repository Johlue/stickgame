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
  init();
}

PlayState::~PlayState()
{}

void PlayState::init()
{
  for(int i = 0; i < 100; i++)
  {
    objects.push_back( new Boundary (365+i, 0, 365+i, 260, mDisplay, false, false, true, false));
  }
  objects.push_back( new Boundary(0, 400, 300, 300, mDisplay, true, false, false, true));
  objects.push_back( new Boundary(360, 0, 360, 260, mDisplay, false, false, false, true));
  objects.push_back( new Boundary(64, 200, 404, 200, mDisplay, false, true, false, false));
  objects.push_back( new Player(101, 101, mDisplay, &objects));
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
  }
}

void PlayState::render()
{
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->render();
  }
}

void PlayState::handleEvents(SDL_Event* e)
{

  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->handleEvent(e);
  }

  if(e->type == SDL_KEYDOWN)
  {
    if(e->key.keysym.sym == SDLK_ESCAPE)
    {
      *currentState = MENUSTATE;
    }
  }
}
