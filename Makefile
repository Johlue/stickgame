#OBJS specifies which files to compile as part of the project
OBJS = main.cpp code\GameState.cpp code\ImageTexture.cpp code\Display.cpp code\MenuButton.cpp code\GameEngine.cpp code\MenuState.cpp code\PlayState.cpp code\GameObjects\GameObject.cpp code\GameObjects\Player.cpp code\GameObjects\Boundary.cpp code\CollisionData.cpp code\GameObjects\Hazard.cpp code\Point.cpp code\Ui.cpp code\GameObjects\Turret.cpp code\GameObjects\Bullet.cpp code\Vector2D.cpp code\func.cpp code\AnimationFrame.cpp code\Animation.cpp code\GameObjects\Slash.cpp code\GameObjects\Walker.cpp code\LevelEditState.cpp code\Editor\EditorObject.cpp code\Editor\ObjectMenu.cpp code\Editor\EO_String.cpp code\TextTexture.cpp code\Writer.cpp code\GameObjects\Switch.cpp code\GameObjects\LevelExit.cpp code\LevelSelectState.cpp code\LevelButton.cpp code\GameObjects\Boss.cpp code\CreditsState.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IF:\CPP\Tutorials\StickGame\code -IF:\mingw_dev_lib\include\SDL2 -IF:\CPP\Tutorials\StickGame\code\GameObjects -IF:\CPP\Tutorials\StickGame\code\Editor

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LF:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows -static-libgcc -static-libstdc++

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) -std=c++11 $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
