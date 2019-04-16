#include "MenuButton.h"
#include <iostream>
#include <cstdlib>

MenuButton::MenuButton(int x, int y, ImageTexture* it, int width, int height)
{
  mPosition.x = x;
  mPosition.y = y;
  mWidth = width;
  mHeight = height;
  mTexture = it;
  mTexture->useSpriteSheet(2, 2);
}

MenuButton::~MenuButton()
{
  mTexture = nullptr;
}

void MenuButton::render()
{
  mTexture->render(mPosition.x, mPosition.y, mCurrentSprite);
}

void MenuButton::handleEvent(SDL_Event* e)
{
  //If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is outside button
		if(  x < mPosition.x ||  x > mPosition.x + mWidth || y < mPosition.y || y > mPosition.y + mHeight  )
		{
			mCurrentSprite = NORMAL;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = HIGHLIGHTED;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = PRESSED;
				break;

				case SDL_MOUSEBUTTONUP:
				//TODO: actual functionality
        std::cout << "Button Pressed!\n";
				break;
			}
		}
	}
}
