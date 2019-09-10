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
  LevelEditState(Display* dis, std::vector<ImageTexture*>* texA, int* cs);
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
protected:
  void mouseEvent(SDL_MouseButtonEvent& b);

  std::vector<EditorObject> objects; // change this to a new object later for ease of texturing
  EditorObject* currentEditorObject = nullptr;
  std::vector<ImageTexture*>* textureArray;
  ObjectMenu menu;
  int speedMultiplier = 1;
  int yMovement = 0; int xMovement = 0;
  int cameraX = 0; int cameraY = 0;
};

#endif
