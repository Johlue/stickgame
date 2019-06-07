#ifndef ANIMATIONFRAME_07062019
#define ANIMATIONFRAME_07062019

class AnimationFrame
{
public:
  AnimationFrame(int row, int col, int tex);
  int getRow();
  int getCol();
  int getTexture();
protected:
  int row, col, texture;
};

#endif
