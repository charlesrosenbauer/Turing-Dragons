fast:
	clang -O3 -lSDL -Wall src/*.c -o bin/dragons

dirty:
	clang -O1 -lSDL src/*.c -o bin/dragons
