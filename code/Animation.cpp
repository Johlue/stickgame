#include "Animation.h"



Animation::Animation(){}

Animation::Animation(int framdelay, bool loop, std::vector<ImageTexture*>* textures, Display* display)
{
  currentFrame = 0;
  frameDelay = framdelay;
  looping = loop;
  mTextures = textures;
  mDisplay = display;
  currentDelay = frameDelay;
}

Animation::~Animation(){freeMem();}

void Animation::freeMem()
{
}
void Animation::render(int x, int y, int camx, int camy, SDL_RendererFlip flip, double rotation, SDL_Point center)
{
  if(currentFrame < mFrames.size())
  {
    (*mTextures)[mFrames[currentFrame].getTexture()]->render(x-camx, y-camy, mFrames[currentFrame].getSprite(), NULL, rotation, &center, flip);
  }
  //mTextures()[1].rend(x+camx, y+camy, 1);

}

void Animation::update()
{
  currentDelay -= 1;
  if(currentDelay < 1)
  {
    if(currentFrame < mFrames.size()-1)
    {
      currentFrame += 1;
    }
    else if(looping)
    {
      currentFrame = 0;
    }
    currentDelay = frameDelay;
  }
}

void Animation::setTransparency(int amount, int textureNro)
{
  (*mTextures)[textureNro]->setBlendMode(SDL_BLENDMODE_BLEND);
  (*mTextures)[textureNro]->setAlpha(amount);
}

void Animation::addFrame(int tex, int sprite)
{
  AnimationFrame af(tex, sprite);
  mFrames.push_back(af);
}

void Animation::reset()
{
  currentFrame = 0;
  currentDelay = frameDelay;
}
