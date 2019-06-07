#include "Animation.h"

AnimationFrame::AnimationFrame(int rows, int cols, int tex)
{
  row = rows;
  col = cols;
  texture = tex;
}

int AnimationFrame::getRow(){return row;}
int AnimationFrame::getCol(){return col;}
int AnimationFrame::getTexture(){return texture;}
