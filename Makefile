all:
	g++ src/*.cpp -lGLEW -lGL -lGLU -lglut -lassimp -lIL -o run

clean:
	rm run