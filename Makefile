all:
	g++ -std=c++11 -I ./Mth -o game.exe *.cpp ./Mth/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lopengl32
