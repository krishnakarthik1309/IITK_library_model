all:
	g++ src/*.cpp -lGLEW -lGL -lGLU -lglut -lassimp -o bin/run

clean:
	rm run