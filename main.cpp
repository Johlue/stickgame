#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <array>
#include "testFile.h"
#include "Display.h"
#include "ImageTexture.h"
#include "gameState.h"
#include "menuState.h"



enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

//Loads media
bool loadMedia();

//Mouse button sprites
//SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
ImageTexture gButtonSpriteSheetTexture;

//Buttons objects
LButton gButtons[ 4 ];



LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is outside button
		if(  x < mPosition.x ||  x > mPosition.x + 300 || y < mPosition.y || y > mPosition.y + 200  )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

				case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void LButton::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, mCurrentSprite);
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "button.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{
	/*
		//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = i * 200;
			gSpriteClips[ i ].w = 300;
			gSpriteClips[ i ].h = 200;
		}*/
		gButtons[0].setPosition(0, 0);
		gButtons[1].setPosition(640 - 300, 480 - 200);
		gButtons[2].setPosition(0, 480 - 200);
		gButtons[3].setPosition(640 - 300, 0);
		gButtonSpriteSheetTexture.useSpriteSheet(1, 4);
	}

	return success;
}

int main( int argc, char* args[] )
{
	bool initSuccess = true;
	//Start up SDL and create window
	initSuccess = init();
	Display display("windowName", 100, 100, 640, 480);
	if( !initSuccess )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		gButtonSpriteSheetTexture.setRenderer(display.getRenderer());
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle button events
					for( int i = 0; i < 4; ++i )
					{
						gButtons[ i ].handleEvent( &e );
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( display.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( display.getRenderer() );

				//Render buttons
				for( int i = 0; i < 4; ++i )
				{
					gButtons[ i ].render();
				}

				//Update screen
				SDL_RenderPresent( display.getRenderer() );
			}
		}
	}

	//Free resources and close SDL
	// I don't understand why this was a separate fucntion
	display.freeMem();
	gButtonSpriteSheetTexture.freeTexture();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
