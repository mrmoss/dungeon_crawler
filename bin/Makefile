#!/bin/bash
#ubuntu
#sudo apt-get install libglew-dev freeglut3-dev
#mac
#brew install glew freeglut

COMPILER=g++
FLAGS=-O -Wno-deprecated-declarations
LIBS=

SRC_DIR=../src

ifeq ($(OS),Windows_NT)
	#FIGURE OUT WINDOWS
else
	ifeq ($(shell uname),Darwin)
		LIBS+=-framework OpenGL -framework GLUT
	else
		LIBS+=-lGL -lGLU -lglut -lpthread
	endif
endif

GAME_SRC=$(SRC_DIR)/chest.cpp $(SRC_DIR)/dungeon.cpp $(SRC_DIR)/enemy.cpp $(SRC_DIR)/entity.cpp $(SRC_DIR)/fireball.cpp $(SRC_DIR)/hero.cpp $(SRC_DIR)/hydra.cpp $(SRC_DIR)/item.cpp $(SRC_DIR)/object.cpp
GRAPHIC_SRC=$(SRC_DIR)/bmp.cpp $(SRC_DIR)/camera2d.cpp $(SRC_DIR)/gamemath.cpp $(SRC_DIR)/glut2d.cpp $(SRC_DIR)/specificinput.cpp $(SRC_DIR)/sprite.cpp $(SRC_DIR)/text.cpp $(SRC_DIR)/timer.cpp
MAP_SRC=$(SRC_DIR)/bitvec.cpp
SOUND_SRC=$(SRC_DIR)/sound.cpp

all: dungeon_crawler

dungeon_crawler: $(SRC_DIR)/main.cpp $(GAME_SRC) $(GRAPHIC_SRC) $(MAP_SRC) $(SOUND_SRC)
	$(COMPILER) $^ $(LIBS) $(FLAGS) -o $@

clean:
	@rm -rf dungeon_crawler dungeon_crawler.exe
