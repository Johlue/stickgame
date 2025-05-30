#include "PlayState.h"
#include <iostream>

PlayState::PlayState()
{}

PlayState::PlayState(Display* dis, std::vector<ImageTexture*>* texA, int* cs, Writer* texS, std::string* lvl, std::vector<int>* kbs)
{
  keybindings = kbs;
  loadableLevel = lvl;
  currentState = cs;
  mDisplay = dis;
  textureArray = texA;
  mWriter = texS;
  //TODO some other stuff
  ui.setDisplay(mDisplay);
  ui.setWriter(texS);
  init();
}

PlayState::~PlayState()
{}

void PlayState::init()
{
  loadLevel();
}

void PlayState::freeMem()
{
	for(int i = 0; i < objects.size(); i++)
	{
		delete (objects[i]);
    objects[i] = nullptr;
	}
	objects.clear();
}

void PlayState::update()
{
  if(*loadableLevel != currentLevel)
  {
    currentLevel = *loadableLevel;
    loadLevel();
  }

  for(int i = 0; i < objects.size(); i++)
  {
    if(objects[i]->getId() == -1)
    {
      //std::cout << objectId << " " << objects.size() << std::endl;
      objects[i]->setId(objectId);
      objectId++;
    }
  }
  if(bossChecked)
  {
    if(bossId != -1)
    {
      if(objects[bossId]->getType() == BOSS)
      {
        Boss * btr = dynamic_cast<Boss*>(objects[bossId]);
        if(btr->getDeathTime() >= 255){*currentState = CREDITSSTATE;}
      }
    }
  }
  //std::cout << "currently existing objects: " << objects.size() << std::endl;
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->update();
    if(!objects[i]->isAlive())
    {
      delete (objects[i]);
      objects[i] = nullptr;
      objects.erase(objects.begin() + i);
    }
    //std::cout << "update";
    if(!playerAlive)
    {
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == PLAYER)
        {
          delete (objects[i]);
          objects[i] = nullptr;
          objects.erase(objects.begin() + i);
        }
      }
      ui.setDeadPlayer(true);
    }
    else
    {
      if(currentPlayer != nullptr)
      {
        cameraX = currentPlayer->getX() - (mDisplay->getWidth()/2)+16;// -half.screenwidth +half.playerwidth
        cameraY = currentPlayer->getY() - (mDisplay->getHeight()/2)+32;
        if(cameraX > levelSizeX - mDisplay->getWidth()) {cameraX = levelSizeX - mDisplay->getWidth();}
        if(cameraY > levelSizeY - mDisplay->getHeight()) {cameraY = levelSizeY - mDisplay->getHeight();}
        if(cameraX < 0) {cameraX = 0;}
        if(cameraY < 0) {cameraY = 0;}
        if(currentPlayer->getY() > levelSizeY + 100)
        {
          CollisionData tempPoint;
          tempPoint.damage = 1000;
          currentPlayer->damaged(tempPoint);
        }
      }
    }
    if(!bossChecked)
    {
      std::cout << "bosscheck";
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == BOSS)
        {
          std::cout << "bosssuccess";
          Boss * ptr = dynamic_cast<Boss*>(objects[i]);
          ui.setBoss(ptr);
          bossId = i;
        }
      }
      bossChecked = true;
    }
  }
}

void PlayState::render()
{
  std::vector<bool> processed; // records if the drawing for the current object is complete or not
  for(int i3 = 0; i3 < objects.size(); i3++){processed.push_back(false);}

  for(int i2 = 0; i2 < 9; i2++)
  {
    for(int i = 0; i < objects.size(); i++)
    {
      if(processed[i] == false) processed[i] = objects[i]->render(cameraX, cameraY, i2);
      //std::cout << "render";
    }
  }
  processed.clear();
  ui.render();
}

void PlayState::handleEvents(SDL_Event* e)
{
  for(int i = 0; i < objects.size(); i++)
  {
    objects[i]->handleEvent(e);
    //std::cout << "event";
  }
  if(e->type == SDL_KEYDOWN)
  {
    if(e->key.keysym.sym == SDLK_r)
    {
      /**
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == PLAYER)
        {
          delete (objects[i]);
          objects.erase(objects.begin() + i);
        }
      }
      */
      loadLevel();

      //objects.push_back( new Player(101, 101, &playerAlive, mDisplay, &objects, textureArray));
      playerAlive = true;
    }

    if (e->key.keysym.sym == (*keybindings)[KB_UP])
    {
      for(int i = 0; i < objects.size(); i++)
      {
        if(objects[i]->getType() == EXIT)
        {
          LevelExit * ext;
          ext = dynamic_cast<LevelExit*>(objects[i]);
          if(ext->getActivated())
          {
            if(currentPlayer->getX() > ext->getX()
            && currentPlayer->getX() + currentPlayer->getWidth() < ext->getX() + ext->getWidth()
            && (currentPlayer->getY() > ext->getY()
             || currentPlayer->getY() + currentPlayer->getHeight() < ext->getY() + ext->getHeight()))
            {
              std::cout << ext->getExitName();
              currentLevel = "levels/" + ext->getExitName() + ".txt";
              *loadableLevel = currentLevel;
              loadLevel();
            }
          }
        }
      }
    }
    if(e->key.keysym.sym == SDLK_ESCAPE)
    {
      *currentState = MENUSTATE;
    }
  }
}

void PlayState::loadLevel()
{
  deleteLevel();
  objectId = 0;
  //delete the player just in case?
  playerAlive = false;
  for(int i = 0; i < objects.size(); i++)
  {
    if(objects[i]->getType() == PLAYER)
    {
      delete (objects[i]);
      objects[i] = nullptr;
      objects.erase(objects.begin() + i);
    }
  }

  ui.deleteBoss();
  bossChecked = false;
  bossId = -1;

  std::ifstream levelFile;
  levelFile.open(currentLevel);
  if(levelFile.is_open())
  {
    std::string line;
    int lineCounter = 0;
    while ( std::getline(levelFile, line) )
    {
      std::vector<std::string> strVec;
      strVec = splitString(line, ' ');

      if(strVec.size() > 0) // non empty string
      {
        if(strVec[0] == "//"); // do nothing if a comment is here
        else if(strVec[0] == "size")
        {
          levelSizeX = std::stoi(strVec[1]); levelSizeY = std::stoi(strVec[2]);
          if(levelSizeY < mDisplay->getHeight()) {levelSizeY = mDisplay->getHeight();}
        }
        else if(strVec[0] == "Boundary") boundaryLoad(strVec);
        else if(strVec[0] == "Hazard") hazardLoad(strVec);
        else if(strVec[0] == "Turret") turretLoad(strVec);
        else if(strVec[0] == "Walker") walkerLoad(strVec);
        else if(strVec[0] == "Switch") switchLoad(strVec);
        else if(strVec[0] == "Exit")   exitLoad(strVec);
        else if(strVec[0] == "Boss")   bossLoad(strVec);
        else if(strVec[0] == "Player")
        {
          objects.push_back(new Player(std::stoi(strVec[1]), std::stoi(strVec[2]), &playerAlive, mDisplay, &objects, textureArray, keybindings));
          playerAlive = true;
        }


      }
      //std::cout << strVec[0] << strVec[2] << std::endl;
    }
    levelFile.close();

    // find player and add his location to the variable tracking thing
    for(int i2 = 0; i2 < objects.size(); i2++)
    {
      if(objects[i2]->getType() == PLAYER)
      {
        playerVectorLocation = i2;
        currentPlayer = dynamic_cast<Player*>(objects[i2]);
        ui.setPlayer(currentPlayer);
        ui.setDeadPlayer(false);
        break;
      }
    }

  } else std::cout << "level opening error is a thing that happened";
}

void PlayState::bossLoad(std::vector<std::string> bl)
{
  int bx, by;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]);

  objects.push_back(new Boss(bx, by, mDisplay, &objects, textureArray));
}

void PlayState::exitLoad(std::vector<std::string> bl)
{
  int bx, by;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]);
  std::string exitName = bl[3];
  bool activ;
  if(bl[4] == "T"){activ = true;}
  else            {activ = false;}

  objects.push_back(new LevelExit(bx, by, exitName, activ, mDisplay, textureArray));
}

void PlayState::turretLoad(std::vector<std::string> bl)
{
  bool inv; bool activ;
  int bx, by, cai, mai;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]);
  if(bl[3] == "T_SLOW") cai = TA_GUN_ACCURATE;
  else if(bl[3] == "T_FAST") cai = TA_GUN_SEMI_SPREAD;
  else if(bl[3] == "T_SPREAD") cai = TA_GUN_FULL_SPREAD;
  else if(bl[3] == "T_BLADE") cai = TA_BEYBLADE;
  else cai = 0;

  if(bl[4] == "T_STATIC") mai = TM_STATIONARY;
  else if(bl[4] == "T_FLIGHT") mai = TM_FLIGHT;
  else if(bl[4] == "T_GROUND") mai = TM_GROUNDSPIN;
  else if(bl[4] == "T_NOCLIP") mai = TM_NOCLIP;
  else mai = 0;

  if(bl[5] == "F") {inv = false;}
  else             {inv = true;}
  if(bl[6] == "T") {activ = true;} else {activ = false;}

  objects.push_back(new Turret(bx, by, cai, mai, mDisplay, &objects, inv, activ));
}

void PlayState::hazardLoad(std::vector<std::string> bl)
{
  int bx, by, bw, bh, hazardType, angle, damage;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]); bw = std::stoi(bl[3]); bh = std::stoi(bl[4]);
  angle = std::stoi(bl[5]); damage = std::stoi(bl[6]); // convert strings to ints
  if(bl[7] == "SPIKE") hazardType = 0;
  else hazardType = 1;
  objects.push_back(new Hazard(bx, by, bw, bh, hazardType, angle, damage, mDisplay));
}

void PlayState::boundaryLoad(std::vector<std::string> bl) // boundary portion of level loading function
{
  int bx, by, bx2, by2; // x and y values
  bool t1, t2, t3, t4; // directional truth values
  // concert string parts to integers
  bx = std::stoi( bl[1] ); by = std::stoi( bl[2] ); bx2 = std::stoi( bl[3] ); by2 = std::stoi( bl[4] );
  if(bl[5] == "T") t1 = true; else t1 = false;
  if(bl[6] == "T") t2 = true; else t2 = false;
  if(bl[7] == "T") t3 = true; else t3 = false;
  if(bl[8] == "T") t4 = true; else t4 = false;
  objects.push_back( new Boundary(bx, by, bx2, by2, mDisplay, t1, t2, t3, t4));
}

void PlayState::walkerLoad(std::vector<std::string> bl) // walkers for the level load
{
  int bx; int by; int cAI; int wAI; int direct;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]);
  if(bl[3] == "MELEE") cAI = MELEE;
  else if(bl[3] ==  "M_QUICK") cAI = MELEE_QUICK; // fast, weak, jumps
  else if(bl[3] ==  "M_STRONG") cAI = MELEE_STRONG;//slow, hits like a truck
  else if(bl[3] ==  "RANGED") cAI = RANGED; // pistol meh shooting speed / power
  else if(bl[3] ==  "R_QUICK") cAI = RANGED_QUICK;// smg, fast shooting, meh power
  else if(bl[3] ==  "R_MINIG") cAI = RANGED_MINIGUN;// minigun(duh), fast strong shooting, moves slowly
  else if(bl[3] ==  "R_BFG") cAI = RANGED_HYPERBEAM;

       if(bl[4] == "STAND")     wAI = STANDING; // stands still and only turns around if detects player
  else if(bl[4] == "INSTTURN")  wAI = INSTANTTURN; // turns as soon as edge is detected
  else if(bl[4] == "WAIT")      wAI = WAIT; // waits 2 seconds at edge of floor before turning around

  if(bl[5] == "LEFT") direct = -1;
  else                direct = 1;

  objects.push_back(new Walker(bx, by, cAI, wAI, mDisplay, &objects, textureArray, direct));
}

void PlayState::switchLoad(std::vector<std::string> bl)
{
  int bx; int by; int switchType; bool once; int reactivTime; bool activ;
  bx = std::stoi(bl[1]); by = std::stoi(bl[2]);
       if(bl[3] == "S_WALL") {switchType = SWITCH_WALL;}
  else if(bl[3] == "S_FLOOR"){switchType = SWITCH_FLOOR;}

  if(bl[4] == "T") {once = true;} else {once = false;}
  reactivTime = std::stoi(bl[5]);
  if(bl[7] == "T") {activ = true;} else {activ = false;}

  objects.push_back(new Switch(bx, by, mDisplay, &objects, switchType, once, reactivTime, activ));

  std::vector<std::string> gl;
  gl = splitString(bl[6], '|');
  Switch * ptr;
  for(int i = 0; i < gl.size(); i++)
  {
    ptr = dynamic_cast<Switch*>(objects.back());
    ptr->addActivatable(std::stoi(gl[i]));
  }
}

int PlayState::getLevelLimitX(){return levelSizeX;}
int PlayState::getLevelLimitY(){return levelSizeY;}

void PlayState::deleteLevel()
{
  freeMem();
}
