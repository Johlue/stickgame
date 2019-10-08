#ifndef EDITOROBJECT_30082019
#define EDITOROBJECT_30082019

#include "GameObject.h"
#include <SDL.h>
#include "EO_String.h"

enum EO_types
{
  EO_NONE, EO_BOUNDARY, EO_WALKER_M, EO_TURRET, EO_SPIKE //add other stuff later
};

class EditorObject
{
public:
  EditorObject();
  EditorObject(int typ, int xl, int yl, Display * disp);
  ~EditorObject();
  bool handleEvents(SDL_Event* e, int cameraX, int cameraY);
  void render(int camX, int camY);
  void update(int cameraX, int cameraY);
  void setIndex(int i);
  int getIndex();
  std::vector<EO_String*> getStringVector();
  int getX(); int getY(); int getWidth(); int getHeight(); int getType();
  void setX2Y2(int xs, int ys);
  int getOpenedMenu();

  void saveLevel();
  void loadLevel(); // this probs needs a string or something

  bool editorClick(SDL_MouseButtonEvent& b, int strings, std::string ** es); // a click while this is currentEditorObject (strings is amount of parameters in object)
  void applyChanges();
  void clickDrag(SDL_MouseButtonEvent& b, int cameraX, int cameraY);

protected:
  void constructStringInfo(); // creates a default list of EO_Strings depending on type
  bool mouseEvent(SDL_MouseButtonEvent& b, int cameraX, int cameraY); // return true if this object was clicked, else return false
  int x; int y; int width = 30; int height = 30;
  int x2; int y2; // for boundary objects
  int stringLength; // how many separated letters in a string
  int type; //as in object type
  Display * mDisplay;
  int index; // the current location of the object in the object vector
  int openedMenu = -1; // which parameters menu is open (-1 means none are open)

  bool clickDragged = false; // starting to click and drag chosen object
  int clickDragNumber = 0; // delay between actually click and dragging and original click
  bool trueClickDragged = false; // object is actually being clickand dragged

  std::vector<EO_String*> stringInfo; // contains the necessary info to contruct an object string for level files
};

#endif
