#include "TextTexture.h"

TextTexture::TextTexture()
{
	//Initialize
  mRenderer = NULL;
	mTexture = NULL;
}

TextTexture::~TextTexture()
{
  freeTexture();
}

void TextTexture::setRenderer(SDL_Renderer* rend){mRenderer = rend;}

void TextTexture::createTexture(std::string s )
{
  if(mRenderer == NULL){std::cout << "Renderer of TextTexture is null"; return;}
  TTF_Font* font = TTF_OpenFont("lazy.ttf", 24); //this opens a font style and sets a size

  SDL_Color color = {0, 0, 0};  // this is the color in rgb format

  const char * c = s.c_str();
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, c, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

  mTexture = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage); //now you can convert it into a texture

  //Don't forget too free your surface and font
  TTF_CloseFont( font );
  delete font;
  font = NULL;
  SDL_FreeSurface(surfaceMessage);
  delete surfaceMessage;
  surfaceMessage = nullptr;
}

//Deallocates texture
void TextTexture::freeTexture()
{
  //Free texture if it exists
  if( mTexture != NULL )
  {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
  }
}

//Set color modulation
void TextTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

//Set blending
void TextTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

//Set alpha modulation
void TextTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

// this draws the texture, with some variables and lst ones have default values
// sprite is used for sprite sheets, starts on the left upper corner at 0, goes through row first then 1 col down
void TextTexture::render( int x, int y)
{
  	//Set rendering space and render to screen
  	SDL_Rect renderQuad = { x, y, mWidth, mHeight};

    SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad);

}

//Gets image dimensions
int TextTexture::getWidth(){return mWidth;}
int TextTexture::getHeight(){return mHeight;}
