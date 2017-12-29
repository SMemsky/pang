# Makefile for building Pang on Linux using gcc

Target = pang
TargetPath = ../

CXX = g++
CXXFLAGS = -g -Wall -Wextra -O2 -std=c++11 -pedantic
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics

MAIN_OBJECTS = main.o \
	Game.o \
	GameObjectManager.o \
	VisibleGameObject.o \
	Splash.o \
	MainMenu.o \
	PlayerPaddle.o \
	Paddle.o \
	AIPaddle.o \
	GameBall.o

all: pang

pang: $(MAIN_OBJECTS)
	$(CXX) $(MAIN_OBJECTS) -o $(TargetPath)$(Target) $(LDFLAGS)

main.o: main.cpp \
		Game.h \
		GameObjectManager.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h \
		GameObjectManager.h \
		VisibleGameObject.h \
		Splash.h \
		MainMenu.h \
		PlayerPaddle.h \
		Paddle.h \
		AIPaddle.h \
		GameBall.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

GameObjectManager.o: GameObjectManager.cpp GameObjectManager.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c GameObjectManager.cpp

VisibleGameObject.o: VisibleGameObject.cpp VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c VisibleGameObject.cpp

Splash.o: Splash.cpp Splash.h
	$(CXX) $(CXXFLAGS) -c Splash.cpp

MainMenu.o: MainMenu.cpp MainMenu.h
	$(CXX) $(CXXFLAGS) -c MainMenu.cpp

PlayerPaddle.o: PlayerPaddle.cpp PlayerPaddle.h \
		Paddle.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c PlayerPaddle.cpp

Paddle.o: Paddle.cpp Paddle.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c Paddle.cpp

AIPaddle.o: AIPaddle.cpp AIPaddle.h \
		Paddle.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c AIPaddle.cpp

GameBall.o: GameBall.cpp GameBall.h \
		VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c GameBall.cpp

clean:
	rm -r *.o

.PHONY: all pang clean