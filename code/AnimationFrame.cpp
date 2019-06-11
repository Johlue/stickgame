#include "Animation.h"

AnimationFrame::AnimationFrame(int tex, int sptir)
{
  sprite = sptir;
  texture = tex;
}

int AnimationFrame::getSprite(){return sprite;}
int AnimationFrame::getTexture(){return texture;}
