#ifndef ANIMATIONFRAME_07062019
#define ANIMATIONFRAME_07062019

// some numbers to help animations work
class AnimationFrame
{
public:
  AnimationFrame(int sprit, int tex);
  int getSprite();
  int getTexture();
protected:
  int sprite, texture;
};

#endif
