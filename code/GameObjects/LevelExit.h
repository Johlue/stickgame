#ifndef LEVELEXIT_12112020
#define LEVELEXIT_12112020

#include "GameObject.h"

// this object is just a nameholder, actual exit functionality is in playstate

class LevelExit : public GameObject
{
public:
  LevelExit();
  ~LevelExit();
  LevelExit(int xl, int yl, std::string name, bool active, Display* display);

  virtual void handleEvent(SDL_Event* e);
  virtual void update();
  virtual bool render(int cameraX, int cameraY, int priority);

  std::string getExitName();

  virtual CollisionData lineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
  int activateThisObject(bool on);
protected:
  std::string exitName;
};

#endif
