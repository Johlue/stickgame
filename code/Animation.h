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
  Animation(int framdelay, bool loop, std::vector<ImageTexture*>* textures, Display* display);
  ~Animation();
  void update();
  void render(int x, int y, int cameraX, int cameraY, SDL_RendererFlip flip = SDL_FLIP_NONE, double rotation = 0, SDL_Point center = {0,0});
  void addFrame(int sprite, int tex); // add next frame, from texture nro, sprite nro
  void reset(); // reset animation
  void freeMem();
  void setTransparency(int amount, int textureNro);
protected:
  bool looping = true; //does animation loop or get stuck at end frame
  int frameDelay = 1; // how long does one animation frame last
  int currentDelay = 1; // how many gameframes until the next animationframe
  int currentFrame = 0; // current animationframe being displayed
  Display * mDisplay;
  std::vector<ImageTexture*>* mTextures;
  std::vector<AnimationFrame> mFrames;
};

#endif
