
#ifndef IMAGETEXTURE_26032019
#define IMAGETEXTURE_26032019

#include <string>
#include <SDL.h>
#include <SDL_image.h>

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

    // this draws the texture, with some variables and I think the last four have default values?
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
