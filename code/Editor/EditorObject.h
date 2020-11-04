#ifndef EDITOROBJECT_30082019
#define EDITOROBJECT_30082019

#include "GameObject.h"
#include <SDL.h>
#include "EO_String.h"
#include "func.h"

enum EO_types
{
  EO_NONE = -1, // nothing!

  EO_BOUNDARY, EO_SPIKE, EO_BOX, EO_SWITCH, EO_OBJECT_LIST_END,  // objects side of the menu | starts at 0

  EO_PLAYER = 1000, EO_WALKER_M, EO_TURRET, EO_ENEMY_LIST_END,  // enemies menu | starts at 1000

  //EO_PLAYER = 9999 //add other stuff later
};
enum EditorClickReturns
{
  ECR_CLICK_TRUE, ECR_CLICK_FALSE, ECR_CLICK_CONNECTION
};

class EditorObject
{
public:
  EditorObject();
  EditorObject(int typ, int xl, int yl, Display * disp);
  ~EditorObject();
  bool handleEvents(SDL_Event* e, int cameraX, int cameraY);
  void render(int camX, int camY);
    void boundaryRender(int camX, int camY);
    void playerRender(int camX, int camY);
    void turretRender(int camX, int camY);
    void switchRender(int camX, int camY);
  void update(int cameraX, int cameraY);
  void setIndex(int i);
  int getIndex();
  std::vector<EO_String*> getStringVector();
  int getX(); int getY(); int getWidth(); int getHeight(); int getType();
  void setX2Y2(int xs, int ys);
  int getOpenedMenu();
  void setOpenedMenu(int om);

  void saveLevel();
  void loadLevel(); // this probs needs a string or something

  bool clickedEdit(int cameraX, int cameraY); // when clicked while in edit mode
  bool clickedDrag(int cameraX, int cameraY); // clicked in drag mode
  void dragged(int offsetX, int offsetY, int cameraX, int cameraY); // what happens when this object is being dragged
  int editorClick(SDL_MouseButtonEvent& b, int strings, std::string ** es); // a click while this is currentEditorObject (strings is amount of parameters in object)
  void applyChanges();
  void setTextureArray(std::vector<ImageTexture*>* tA);

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

  bool clickDragged = false; // object is being click and dragged

  std::vector<EO_String*> stringInfo; // contains the necessary info to contruct an object string for level files
  std::vector<ImageTexture*>* textureArray = nullptr;
};

#endif
