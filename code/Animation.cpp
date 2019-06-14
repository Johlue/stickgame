#include "Animation.h"



Animation::Animation(){}

Animation::Animation(int framdelay, bool loop, std::vector<ImageTexture*>* textures, Display* display)
{
  currentFrame = 0;
  frameDelay = framdelay;
  looping = loop;
  mTextures() = textures;
  mDisplay = display;
  currentDelay = frameDelay;
}

Animation::~Animation(){freeMem();}

void Animation::freeMem()
{
}
void Animation::render(int x, int y, int camx, int camy)
{
  std::cout << currentDelay << " " << currentFrame << std::endl;
  if(currentFrame < getmFrames().size())
  {
    (*mTextures())[getmFrames()[currentFrame].getTexture()]->render(x-camx, y-camy, getmFrames()[currentFrame].getSprite());
  }
  //mTextures()[1].rend(x+camx, y+camy, 1);

}

void Animation::update()
{
  currentDelay -= 1;
  if(currentDelay < 1)
  {
    if(currentFrame < getmFrames().size()-1)
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

void Animation::addFrame(int tex, int sprite)
{
  AnimationFrame af(tex, sprite);
  getmFrames().push_back(af);
}

void Animation::reset()
{
  currentFrame = 0;
  currentDelay = frameDelay;
}
