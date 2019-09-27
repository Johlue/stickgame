#include "Writer.h"

Writer::Writer(){}

Writer::~Writer()
{
  if(mSymbolTextures.size() > 0)
  {
    for(int i = 0; i < mSymbolTextures.size(); i++)
    {
        mSymbolTextures[i]->freeTexture();
        delete mSymbolTextures[i];
        mSymbolTextures[i] = nullptr;
    }
    mSymbolTextures.clear();
  }
}

void Writer::setup(Display * display)
{
  mDisplay = display;
  for(int i = 0; i < mSymbols.size(); i++)
  {
    mSymbolTextures.push_back(new TextTexture());
    mSymbolTextures.back()->setRenderer(mDisplay->getRenderer());
    mSymbolTextures.back()->createTexture(mSymbols.substr(i, 1));
  }
}

void Writer::render(std::string text, int x, int y)
{

  if(text.size() == 0) return;
  bool valid = true;
  std::string temp = "";
  for(int i = 0; i < text.size(); i++) // runs through each symbol in string
  {
    if(!valid) std::cout << "Symbol is invalid.\n"; // non existing symbol
    valid = false;
    temp = text.substr(i, 1); // get letter here
    for(int j = 0; j < mSymbols.size(); j++) // go through symbols looking for a match
    {
      if(temp == mSymbols.substr(j, 1))
      {
        valid = true;
        mSymbolTextures[j]->render(x + (mSymbolTextures[j]->getWidth()*i), y); // if match is found render to screen
        break;
      }
    }
  }
}
