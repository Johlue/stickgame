#include "MenuButton.h"
#include <iostream>
#include <cstdlib>

MenuButton::MenuButton(int x, int y, ImageTexture* it, int type, int width, int height)
{
  mButtonType = type;
  mPosition.x = x;
  mPosition.y = y;
  mWidth = width;
  mHeight = height;
  mTexture = it;
  mTexture->useSpriteSheet(1, 12);
}

MenuButton::~MenuButton()
{
  mTexture = nullptr;
}

void MenuButton::render()
{
  mTexture->render(mPosition.x, mPosition.y, mCurrentSprite + (mButtonType * 3));
}

int MenuButton::handleEvent(SDL_Event* e)
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
        std::cout << "Button " << mButtonType << " Pressed!\n";

        // do stuff according to buttontype
        switch(mButtonType)
        {
          // quit game if buttontype is QUIT
          case QUIT:
            SDL_Event sdlevent;
            sdlevent.type = SDL_QUIT;
            SDL_PushEvent(&sdlevent);
            break;

          case START:
            return mButtonType;
            break;

          case EDIT:
            return mButtonType;
            break;
        }
        break;

			}
		}
	}
  // return nonexistent buttontype if no buttons were pressed
  return -1;
}
