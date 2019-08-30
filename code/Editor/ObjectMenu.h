#ifndef OBJECTMENU_30082019
#define OBJECTMENU_30082019

enum mStates{CLOSED, ENEMIES, OBJECTS};

class ObjectMenu
{
public:
  ObjectMenu();
  render();
  handleEvents();
protected:
  int mState; // is it open or closed and what open if it is open
};

#endif
