#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <array>
#include <vector>
#include "testFile.h"
#include "Display.h"
#include "ImageTexture.h"
#include "GameState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "GameEngine.h"
#include "Writer.h"
#include <stdlib.h>
#include <time.h>

// global time!
const int Screen_Width = 1280;
const int Screen_Height = 720;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

//Loads media
bool loadMedia();

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
	if(TTF_Init() == -1) success = false;
	return success;
}

int main( int argc, char* args[] )
{
	std::srand(time(NULL));
	bool initSuccess = true;
	//Start up SDL and create window
	initSuccess = init();
	Display display("StickGame", 0, 100, Screen_Width, Screen_Height);
	Writer writer;
	writer.setup(&display);
	GameEngine game(&display, &writer);

	if( !initSuccess )
	{
		printf( "Failed to initialize!\n" );
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
				// DONZO
				game.handleEvents(&e);
				//
				//-----------------------------------------------------------------------------------------------------------
				//
				//	THIS IS A BIG DEAL YOU KNOW
				//
				//-----------------------------------------------------------------------------------------------------------
				//

				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			// DONZO
			game.update();
			//
			//-----------------------------------------------------------------------------------------------------------
			//
			//	THIS IS A BIG DEAL YOU KNOW
			//
			//-----------------------------------------------------------------------------------------------------------
			//


			//Clear screen
			SDL_SetRenderDrawColor( display.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( display.getRenderer() );

			//Render stuff

			// DONZO
			game.render();
			//
			//-----------------------------------------------------------------------------------------------------------
			//
			//	THIS IS A BIG DEAL YOU KNOW
			//
			//-----------------------------------------------------------------------------------------------------------
			//

			//Update screen
			SDL_RenderPresent( display.getRenderer() );
		}
	}

	//Free resources and close SDL
	// I don't understand why this was a separate fucntion

	game.freeMem();
	display.freeMem();

	//gButtonSpriteSheetTexture.freeTexture();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
