all:
	g++ -I inc -L lib -o pong src/main.cpp src/game.cpp src/rendering.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows -m64

all_debug:
	g++ -I inc -L lib -o pong src/main.cpp src/game.cpp src/rendering.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -Wall -m64