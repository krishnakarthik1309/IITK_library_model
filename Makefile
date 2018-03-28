all:
	g++ src/*.cpp -lGLEW -lGL -lGLU -lglut -lassimp -o run

clean:
	rm run