#include "Display.h"
#include <iostream>

Display::Display(std::string windowName, int posX, int posY, int width, int height) : mRenderer(nullptr), mWindow(nullptr) //member initialization stuffs
{
  std::cout << mRenderer << "render initialization\n";
  std::cout << mWindow << "window intialization\n";
  m_width = width;
  m_height = height;
  init(windowName, posX, posY, width, height);
}

Display::~Display()
{}

void Display::freeMem(){
  SDL_DestroyRenderer( mRenderer );
  SDL_DestroyWindow( mWindow );
  mWindow = NULL;
  mRenderer = NULL;
}

int Display::getHeight(){return m_height;}
int Display::getWidth(){return m_width;}

bool Display::init(std::string windowName, int posX, int posY, int width, int height)
{
  bool success = true;

  // changing windowName to a char*
  const char * c = windowName.c_str();
  //Create window
  mWindow = SDL_CreateWindow( c, posX, posY, width, height, SDL_WINDOW_SHOWN );
  if( mWindow == NULL )
  {
    printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Create vsynced renderer for window
    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( mRenderer == NULL )
    {
      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    std::cout << mRenderer << " render nro\n";
    {
      //Initialize renderer color
      SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

      //Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if( !( IMG_Init( imgFlags ) & imgFlags ) )
      {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
      }
    }
  }
  std::cout << mRenderer << " render nro\n";
  return success;
}

SDL_Renderer* Display::getRenderer()
{
  //std::cout << mRenderer << " render nro\n";
  return mRenderer;
}

SDL_Window* Display::getWindow()
{
  //std::cout << mWindow << "windon nrom\n";
  return mWindow;
}
