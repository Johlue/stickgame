#ifndef TEXTTEXTURE_24092019
#define TEXTTEXTURE_24092019

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class TextTexture
{
public:
  TextTexture();
  ~TextTexture();

  void setRenderer(SDL_Renderer* rend);

  void createTexture(std::string s);

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
  void render( int x, int y);

  //Gets image dimensions
  int getWidth();
  int getHeight();

  SDL_Renderer* getRend(){
    return mRenderer;
  }

protected:
  //The actual hardware texture
  SDL_Texture* mTexture;
  SDL_Renderer* mRenderer;

  //Image dimensions
  int mWidth = 8;
  int mHeight = 16;
};

#endif
