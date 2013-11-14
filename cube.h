#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <cmath>
#include <new>
#include <unistd.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

const uint8_t colorScheme[7][3] =  {{  0,   0,   0},  //0 Black
									{255, 255, 255},  //1 White
									{255, 255,   0},  //2 Yellow
									{  0,   0, 255},  //3 Blue
									{  0, 255,   0},  //4 Green
									{255,   0,   0},  //5 red
									{255, 155,   0}}; //6 Orange
const uint8_t CUBEVER[8][3]     =  {{0, 0, 0},
									{1, 0, 0},
									{1, 1, 0},
									{0, 1, 0},
									{0, 0, 1},
									{1, 0, 1},
									{1, 1, 1},
									{0, 1, 1}};
const uint8_t CUBEFACE[6][4]    =  {{4, 5, 6, 7},
									{0, 1, 2, 3},
									{3, 2, 6, 7},
									{0, 1, 5, 4},
									{1, 2, 6, 5},
									{0, 3, 7, 4}};

struct cubies
{
	uint8_t color[6]   = {1, 2, 3, 4, 5, 6};
	uint8_t rot[3]     = {0, 0, 0};
	uint8_t pos[3]     = {0, 0, 0};
	uint8_t isrotating = 3;
};

class cube
{
	public:
		cube();

		void generate();
		void draw();
		void layer_up();
		void layer_down();
		void rotate(int c);

		~cube();

	private:
		uint8_t color[6]         = {0, 0, 0, 0, 0, 0}; //F B T D R L
		uint8_t center[6]        = {0, 0, 0, 0, 0, 0}; //F B T D R L (undeterminated)
		uint8_t num_layer        = 3;
		uint8_t side_rotating    = 6;
		double  side_rotation[6] = {0, 0, 0, 0, 0, 0};
		cubies *cubes;

		void draw_cube(int index);
};

#endif










