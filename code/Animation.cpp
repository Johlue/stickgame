#include "Animation.h"

Animation::Animation(){}

void Animation::render(int x, int y, int camx, int camy)
{
  (*mTextures)[mFrames[currentFrame].getTexture()]->render(x+camx, y+camy, mFrames[currentFrame].getSprite());
}

void Animation::update()
{
  currentDelay -= 1;
  if(currentDelay < 1)
  {
    if(currentFrame < mFrames.size())
    {
      currentFrame += 1;
      currentDelay = frameDelay;
    }
    else if(looping)
    {
      currentFrame = 0;
      currentDelay = frameDelay;
    }
  }
}

void Animation::addFrame(int sprite, int tex)
{
  AnimationFrame frame(sprite, tex);
  mFrames.push_back(frame);
}

void Animation::reset()
{
  currentFrame = 0;
  currentDelay = frameDelay;
}
