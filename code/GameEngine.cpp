#include "GameEngine.h"
#include "Display.h"

GameEngine::GameEngine(Display* display, Writer* writer)
{

  mDisplay = display;
  //TODO all the things, basically create a display and initialize gamestates and whatever
  // load a texture to the thingy
  loadImageTexture("graphics/menuButtons.png", 1, 15);           // 0
  loadImageTexture("graphics/chara.png", 10, 1);                // 1
  loadImageTexture("graphics/LevelEditMenu1.png", 1, 4);         // 2
  loadImageTexture("graphics/LevelEditMenuEnemies.png", 4, 3);   // 3
  loadImageTexture("graphics/LevelEditMenuObjects.png", 4, 3);   // 4
  loadImageTexture("graphics/MOUSE_CREATE.png", 1, 1);           // 5
  loadImageTexture("graphics/MOUSE_DRAG.png", 1, 1);             // 6
  loadImageTexture("graphics/MOUSE_EDIT.png", 1, 1);             // 7
  loadImageTexture("graphics/charaGunHand.png", 5, 1);           // 8
  loadImageTexture("graphics/charaSwordHand.png", 3, 2);         // 9
  loadImageTexture("graphics/Enemy_Normal_Body.png", 6, 1);      // 10
  loadImageTexture("graphics/Enemy_Pistol_Hand.png", 1, 1);      // 11
  loadImageTexture("graphics/Enemy_Large_Body.png", 7, 1);       // 12
  loadImageTexture("graphics/Enemy_Minigun_Hand.png", 2, 1);     // 13
  loadImageTexture("graphics/Enemy_SMG_Hand.png", 1, 1);         // 14
  loadImageTexture("graphics/Enemy_Sword_Hand.png", 4, 2);       // 15
  loadImageTexture("graphics/Enemy_Ball_Hand.png", 5, 1);        // 16
  loadImageTexture("graphics/Enemy_Dagger_Hand.png", 3, 1);      // 17
  loadImageTexture("graphics/EXIT.png", 1, 2);                   // 18
  loadImageTexture("graphics/Boss_Body.png", 1, 2);              // 19
  loadImageTexture("graphics/Boss_Megaguns.png", 1, 37);         // 20
  loadImageTexture("graphics/Boss_Wheel.png", 4, 1);             // 21
  loadImageTexture("graphics/Boss_Gun.png", 1, 1);               // 22
  loadImageTexture("graphics/Credits.png", 1, 1);                // 23
  loadImageTexture("graphics/Title.png",1,1);                    // 24


  loadImageTexture("graphics/404.png", 1, 1);                    // n+1

  // this mess autoloads level images
  std::ifstream levelList;
  levelList.open("LevelList.txt");
  if(levelList.is_open())
  {
    std::string line;
    while ( std::getline(levelList, line) )
    {
      if(line != "")
      {
        int oldSize = mTextures.size();
        line = "levels/" + line + ".png";
        loadImageTexture(line, 1, 1);
        if(mTextures.size() == oldSize) {levelImages.push_back(false);}
        else {levelImages.push_back(true);}
      }
    }
  }
/*
____________________________________________________________________________________________________________



          REMEMBER TO UPDATE THE TEXTURE ENUM IN IMAGETEXTURES WHEN ADDING STUFF


____________________________________________________________________________________________________________
*/

  /*
  mTextures.push_back(new ImageTexture());
  mTextures[0]->setRenderer(display->getRenderer());
  if(!mTextures[0]->loadFromFile("menuButtons.png"))
  {
    // fail check
    printf("Failed to load button sprite texture!\n");
  }
  mTextures[0]->useSpriteSheet(1, 9);*/
  mWriter = writer;

  std::vector<GameState*> states;
  std::cout << std::endl << currentState << std::endl;
  init();
}

GameEngine::~GameEngine()
{

}

void GameEngine::loadImageTexture(std::string name, int spriteRow, int spriteCol)
{
  mTextures.push_back(new ImageTexture());
  mTextures.back()->setRenderer(mDisplay->getRenderer());
  if(!mTextures.back()->loadFromFile(name))
  {
    std::cout << "Failed to load texture: " << name << std::endl << mTextures.size();
    mTextures.pop_back(); // deletes the failed texture and vector slot
    return;
  }
  if(spriteRow > 1 || spriteCol > 1) mTextures.back()->useSpriteSheet(spriteRow, spriteCol);
}

void GameEngine::init()
{
  std::ifstream kbFile;
  kbFile.open("keybindings.txt");
  if(kbFile.is_open())
  {
    std::string line;
    while ( std::getline(kbFile, line) )
    {
      keybindings.push_back(std::stoi(line));
    }
  }
  states.push_back(new MenuState(mDisplay, &mTextures, &currentState, mWriter, &keybindings));
  states.push_back(new PlayState(mDisplay, &mTextures, &currentState, mWriter, &loadableLevel, &keybindings));
  states.push_back(new LevelEditState(mDisplay, &mTextures, &currentState, mWriter));
  states.push_back(new LevelSelectState(mDisplay, &mTextures, &currentState, mWriter, &loadableLevel, &levelImages));
  states.push_back(new CreditsState(mDisplay, &mTextures, &currentState));
  //std::cout << states.size() << std::endl;
  mRunning = true;
  currentState = MENUSTATE;
  // create gamestates and i guess initialize them or whatever, the display is already in another place so who cares
}

void GameEngine::freeMem()
{
  //TODO: go through gamestate vector and freeMem all of the things
  for(int i = 0; i < mTextures.size(); i++)
  {
    mTextures[i]->freeTexture();
    delete mTextures[i];
    mTextures[i] = nullptr;
  }
  mTextures.clear();
  for(int i = 0; i < states.size(); i++)
  {
    states[i]->freeMem();
    delete states[i];
    states[i] = nullptr;
  }
  states.clear();
}

void GameEngine::handleEvents(SDL_Event* e)
{
  //printf("e");
  states[currentState]->handleEvents(e);
}

void GameEngine::update()
{
  //printf("u");
  states[currentState]->update();
}

void GameEngine::render()
{
  //std::cout << currentState;
  states[currentState]->render();
}

void GameEngine::setState(int s)
{
  currentState = s;
}

void GameEngine::quit()
{
  freeMem(); //...seems a bit redundant
}
