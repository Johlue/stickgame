#ifndef ANIMATION_07062019
#define ANIMATION_07062019

#include "ImageTexture.h"
#include <iostream>
#include <vector>
#include "Display.h"
#include "AnimationFrame.h"

/*
  how it actually works thou?:
  necessary textures are in a vector
  only 1 animation per object, if multiple are neccessary then add a vector to the object that is being animated
  runs through the list of frame objects at the speed of the delay
*/

class Animation
{
public:
  Animation();
  void update();
  void render(int x, int y, int cameraX, int cameraY);
  void addFrame(int sprite, int tex);
  void reset(); // reset animation
protected:
  bool looping; //does animation loop or get stuck at end frame
  int frameDelay; // how long does one animation frame last
  int currentDelay; // how many gameframes until the next animationframe
  int currentFrame = 0; // current animationframe being displayed
  Display * mDisplay;
  std::vector<ImageTexture*>* mTextures;
  std::vector<AnimationFrame> mFrames;
};

#endif
