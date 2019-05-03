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
	return success;
}

int main( int argc, char* args[] )
{
	// vector to keep the textures in
	std::vector<ImageTexture*> textureArray;
	textureArray.push_back( new ImageTexture());


	bool initSuccess = true;
	//Start up SDL and create window
	initSuccess = init();
	Display display("windowName", 100, 100, 640, 480);
	GameEngine game(&display);
/*
	// load a texture to the thingy
	textureArray[0]->setRenderer(display.getRenderer());
	if(!textureArray[0]->loadFromFile("button.png"))
	{
		// fail check
		printf("Failed to load button sprite texture!\n");
		initSuccess = false;
	}
	textureArray[0]->useSpriteSheet(2, 2);
*/
	if( !initSuccess )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		// make a button
		MenuButton startButton(0, 200, textureArray[0], 0);
		MenuButton endButton(300, 200, textureArray[0], 1);
		MenuButton loadButton(0, 0, textureArray[0], 2);

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

			//Render buttons

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
	for(int i = 0; i < textureArray.size(); i++)
	{
		textureArray[i]->freeTexture();
	}
	for(int i = 0; i < textureArray.size(); i++)
	{
		delete (textureArray[i]);
	}
	textureArray.clear();

	game.freeMem();
	display.freeMem();

	//gButtonSpriteSheetTexture.freeTexture();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
