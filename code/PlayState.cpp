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
  objects.push_back( new Boundary(360, 00, 360, 260, mDisplay));
  objects.push_back( new Player(100, 100, mDisplay, &objects));
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
