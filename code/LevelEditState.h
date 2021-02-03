#ifndef LEVELEDITSTATE_27082019
#define LEVELEDITSTATE_27082019

#include "GameState.h"
#include "GameObject.h"
#include "EditorObject.h"
#include "ObjectMenu.h"

enum mouseModes
{
  MOUSE_EDIT, MOUSE_DRAG, MOUSE_CREATE, MOUSE_CONNECT
};

class LevelEditState : public GameState
{
public:
  LevelEditState();
  // Display pointer, vector necessary textures, pointer to the active gamestate
  LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS);
  ~LevelEditState();

  void init();
  void freeMem();

  // deal with user input
  void handleEvents(SDL_Event* e);
    void clickEdit(int mx, int my, SDL_Event* e);
    void clickCreate(int mx, int my);
    void clickDrag(int mx, int my);
    void clickConnect(int mx, int my);
      void connectToMany(int objectIndex, int connectIndex);
      void unconnect();
  // do frame update stuff
  void update();
  // draw the things
  void render();
    void renderClickMode();
    void renderCurrentObject();
    void renderDoublePointObject();
    void renderEditMenu();
    void renderLoadSave();
    void renderSwitchConnections();

  //tells the GameEngine to change game states
  void changeState(int s);

  void saveLevel(std::string lvlName);
  void loadLevel(std::string lvlName);
protected:
  //void mouseEvent(SDL_MouseButtonEvent& b);
  void deleteObject(int ix); // deletes object at index ix, and also rearranges the index number in the objects vector
  // gets a string of parameters and creates an object based on them, returns true if creation succeeded
  bool createObjectFromFile(std::string sourceString);
  void createBoundary(int x, int y, int x2, int y2);

  std::vector<EditorObject*> objects; // change this to a new object later for ease of texturing
  EditorObject* currentEditorObject = nullptr; // pointer to currently editable object
  std::vector<ImageTexture*>* textureArray;
  ObjectMenu menu;
  int bx = -9999999; int by = -9999999; // boundary x and y

  int offsetX = 0; int offsetY = 0; // offset to where you are grabbing a dragged object
  int draggedIndex = -1;

  int createObject = EO_NONE; // type of creatable object
  int speedMultiplier = 1; //  speed at which the camera is moving
  int yMovement = 0; int xMovement = 0;
  int cameraX = 0; int cameraY = 0;
  bool clicked = false; // used to prevent double actions (picking from menu and creating object at the same time)
  int currentFrame = 0;
  int clickMode = MOUSE_EDIT; // this the choice of clicking. Drag, edit, create, etc.
  std::string * editableString = nullptr;

  int xLimit = 1000; int yLimit = 640;
  bool xLimitDrag = false; bool yLimitDrag = false;

  bool savingMode = false;
  bool loadingMode = false;
  std::string saveFileName = "save";
};

#endif
