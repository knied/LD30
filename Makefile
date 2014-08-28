all:
	g++ -std=c++11 -I ./Mth -o game.exe *.c *.cpp ./Mth/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lopengl32 -static-libgcc -static-libstdc++
