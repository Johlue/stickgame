#include "ImageTexture.h"
#include <iostream>

ImageTexture::ImageTexture()
{
	//Initialize
  mRenderer = NULL;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

ImageTexture::~ImageTexture()
{
	//Deallocate
	freeTexture();
}

void ImageTexture::setRenderer(SDL_Renderer* rend)
{
  mRenderer = rend;
}

bool ImageTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	freeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    std::cout << " this work?\n";
    std::cout << mRenderer;
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( mRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
      mSpriteRow = 1;
      mSpriteColumn = 1;
      mSpriteSize = {0, 0, mWidth, mHeight};
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void ImageTexture::useSpriteSheet(int row, int column)
{
  mSpriteRow = row;
  mSpriteColumn = column;
  if(mWidth%mSpriteRow != 0) std::cout << "Sprite sheet width is incorrect\n";
  if(mHeight%mSpriteColumn != 0) std::cout << "Sprite sheet height is incorrect\n";
  // calc width and height of sprites based on amount of rows
  mSpriteSize = {0, 0, mWidth / mSpriteRow, mHeight / mSpriteColumn};
}
/*
void ImageTexture::setCurrentSprite(int a)
{
  mCurrentSprite = a;
  // position of x in current sprite
  int aX = (mCurrentSprite % mSpriteRow) * mSpriteSize.w;
  // position of y in current sprite
  int divY = mCurrentSprite / mSpriteRow;
  int aY = divY * mSpriteSize.h;
  // create rectangle for current sprite;
	mSpriteSize = { aX, aY, mWidth / mSpriteRow, mHeight / mSpriteColumn };
}*/

void ImageTexture::freeTexture()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void ImageTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void ImageTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void ImageTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void ImageTexture::render( int x, int y, int sprite, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mSpriteSize.w, mSpriteSize.h};

  // position of x in current sprite
  int aX = (sprite % mSpriteRow) * mSpriteSize.w;
  // position of y in current sprite
  int divY = sprite / mSpriteRow;
  int aY = divY * mSpriteSize.h;
  // create rectangle for current sprite;
	SDL_Rect spriteClip = { aX, aY, mWidth / mSpriteRow, mHeight / mSpriteColumn };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
  	SDL_RenderCopyEx( mRenderer, mTexture, clip, &renderQuad, angle, center, flip );
	}
  else
  {
    // position of x in current sprite
    int aX = (sprite % mSpriteRow) * mSpriteSize.w;
    // position of y in current sprite
    int divY = sprite / mSpriteRow;
    int aY = divY * mSpriteSize.h;
    // create rectangle for current sprite;
  	SDL_Rect spriteClip = { aX, aY, mWidth / mSpriteRow, mHeight / mSpriteColumn };
    //std::cout << spriteQuad.x << " " << spriteQuad.y << " " << spriteQuad.w << " " << spriteQuad.h << std::endl;
  	SDL_RenderCopyEx( mRenderer, mTexture, &spriteClip, &renderQuad, angle, center, flip );
  }

	//Render to screen
}

int ImageTexture::getWidth()
{
	return mWidth;
}

int ImageTexture::getHeight()
{
	return mHeight;
}
