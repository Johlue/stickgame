#ifndef LEVELEDITSTATE_27082019
#define LEVELEDITSTATE_27082019

#include "GameState.h"
#include "GameObject.h"
#include "EditorObject.h"
#include "ObjectMenu.h"

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
  // do frame update stuff
  void update();
  // draw the things
  void render();

  //tells the GameEngine to change game states
  void changeState(int s);

  void saveLevel(std::string lvlName);
  void loadLevel(std::string lvlName);
protected:
  void mouseEvent(SDL_MouseButtonEvent& b);
  void deleteObject(int ix); // deletes object at index ix, and also rearranges the index number in the objects vector

  std::vector<EditorObject*> objects; // change this to a new object later for ease of texturing
  EditorObject* currentEditorObject = nullptr; // pointer to currently editable object
  std::vector<ImageTexture*>* textureArray;
  ObjectMenu menu;
  int bx = -9999999; int by = -9999999; // boundary x and y
  int createObject = EO_NONE; // type of creatable object
  int speedMultiplier = 1; //  speed at which the camera is moving
  int yMovement = 0; int xMovement = 0;
  int cameraX = 0; int cameraY = 0;
  bool clicked = false; // used to prevent double actions (picking from menu and creating object at the same time)
  int currentFrame = 0;
  std::string * editableString = nullptr;
};

#endif
