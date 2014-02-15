CC = g++
CFLAGS = -W -Wall -ansi -pedantic -std=gnu++11
LDFLAGS = -lSDL2 -lSDL2_ttf -lGL -lGLU -lpthread
EXEC = glcube

all: $(EXEC) clean

$(EXEC): src/cube.o src/camera.o src/render.o src/matrix.o src/glcube.o
	$(CC) -o bin/$(EXEC) src/cube.o src/camera.o src/render.o src/matrix.o src/glcube.o $(LDFLAGS)

cube.o: src/cube.cpp
	$(CC) -o src/cube.o -c src/cube.cpp $(CFLAGS)

camera.o: src/camera.cpp
	$(CC) -o src/camera.o -c src/camera.cpp $(CFLAGS)

render.o: src/render.cpp
	$(CC) -o src/render.o -c src/render.cpp  $(CFLAGS)

matrix.o: src/matrix.cpp
	$(CC) -o src/matrix.o -c src/matrix.cpp  $(CFLAGS)

glcube.o: src/glcube.cpp
	$(CC) -o src/glcube.o -c src/glcube.cpp  $(CFLAGS)

clean:
	rm -rf src/*.o
	rm -rf src/*~

mrproper: clean
	rm -rf bin/$(EXEC)
