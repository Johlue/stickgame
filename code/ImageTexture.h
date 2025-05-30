
#ifndef IMAGETEXTURE_26032019
#define IMAGETEXTURE_26032019

#include <string>
#include <SDL.h>
#include <SDL_image.h>

enum Texturenums
{
  TEX_MENUBUTTONS = 0,
  TEX_PLAYER_BODY = 1,
  TEX_LEVELEDIT_MENU = 2,
  TEX_LEVELEDIT_MENU_ENEMIES = 3,
  TEX_LEVELEDIT_MENU_OBJECTS = 4,
  TEX_LEVELEDIT_MOUSEMODE_CREATE = 5,
  TEX_LEVELEDIT_MOUSEMODE_DRAG = 6,
  TEX_LEVELEDIT_MOUSEMODE_EDIT = 7,
  TEX_PLAYER_GUN = 8,
  TEX_PLAYER_SWORD = 9,
  TEX_ENEMY_NORMAL_BODY = 10,
  TEX_ENEMY_PISTOL_HAND = 11,
  TEX_ENEMY_LARGE_BODY = 12,
  TEX_ENEMY_MINIGUN_HAND = 13,
  TEX_ENEMY_SMG_HAND = 14,
  TEX_ENEMY_SWORD_HAND = 15,
  TEX_ENEMY_BALL_HAND = 16,
  TEX_ENEMY_DAGGER_HAND = 17,
  TEX_EXIT_DOOR = 18,
  TEX_BOSS_BODY = 19,
  TEX_BOSS_MEGAGUNS = 20,
  TEX_BOSS_WHEEL = 21,
  TEX_BOSS_GUN = 22,
  TEX_CREDITS = 23,
  TEX_TITLE = 24,
  TEX_404,
  TEX_FIRST_LEVEL_IMAGE
};

class ImageTexture
{
	public:
		//Initializes variables
		ImageTexture();

		//Deallocates memory
		~ImageTexture();

    void setRenderer(SDL_Renderer* rend);

		//Loads image at specified path
		bool loadFromFile( std::string path );

		// splinters the chosen image to be used as a sprite sheet, automagically sets sizes of sprites based on
		// amount of rows and columns
		void useSpriteSheet(int row, int col);

		//Deallocates texture
		void freeTexture();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

    // this draws the texture, with some variables and lst ones have default values
		// sprite is used for sprite sheets, starts on the left upper corner at 0, goes through row first then 1 col down
		// clip is used for scaling and it's x and y values are ignored
		void render( int x, int y, int sprite = 0, SDL_Rect* clip = NULL, double angle = 0.0,
									SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Renderer* getRend(){
			return mRenderer;
		}

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
		int mSpriteRow; // how many sprite rows in image
		int mSpriteColumn; // how many columns
		SDL_Rect mSpriteSize; // size and location of the current sprite in the texture

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif
