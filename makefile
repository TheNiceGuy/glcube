CC = g++
CFLAGS = -W -Wall -ansi -pedantic -std=c++11
LDFLAGS = -lSDL -lGL -lGLU
EXEC = glcube

all: $(EXEC) clean

$(EXEC): cube.o camera.o render.o glcube.o
	$(CC) -o bin/$(EXEC) cube.o camera.o render.o glcube.o $(LDFLAGS)

cube.o: cube.cpp
	$(CC) -o cube.o -c cube.cpp $(CFLAGS)

camera.o: camera.cpp
	$(CC) -o camera.o -c camera.cpp $(CFLAGS)

render.o: render.cpp
	$(CC) -o render.o -c render.cpp  $(CFLAGS)

glcube.o: glcube.cpp
	$(CC) -o glcube.o -c glcube.cpp  $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf *.*~

mrproper: clean
	rm -rf $(EXEC)
