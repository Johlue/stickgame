#ifndef GAMEOBJECT_03052019
#define GAMEOBJECT_03052019

class GameObject
{
public:
  GameObject();
  GameObject(int xl, int yl, int w, int h);
  ~GameObject();

  virtual void handleEvent();
  virtual void update();
  virtual void render();
private:
  int x;
  int y;
  int width;
  int height;

};

#endif
