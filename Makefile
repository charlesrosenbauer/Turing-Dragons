fast:
	clang -O3 -lm -lSDL -Wall src/*.c -o bin/dragons

dirty:
	clang -O1 -lm -lSDL src/*.c -o bin/dragons
