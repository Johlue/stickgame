#include "Animation.h"

AnimationFrame::AnimationFrame(int sptir, int tex)
{
  sprite = sptir;
  texture = tex;
}

int AnimationFrame::getSprite(){return sprite;}
int AnimationFrame::getTexture(){return texture;}
