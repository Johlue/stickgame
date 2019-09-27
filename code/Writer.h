#ifndef WRITER_27092019
#define WRITER_27092019

#include <string>
#include <vector>
#include <iostream>
#include "TextTexture.h"
#include "Display.h"

class Writer
{
public:
  Writer();
  ~Writer();
  void setup(Display * display); // sets important pointers and does whatever other stuff necessary
  void render(std::string text, int x, int y); // put some text on the screen at x, y
protected:
  std::string mSymbols = "0123456789abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ !#¤%&/()=?`@£$€{[]}+*^¨<>|,.-;:_§½";
  std::string mFont = "lazy.ttf";
  std::vector<TextTexture*> mSymbolTextures;
  Display * mDisplay;
};

#endif
