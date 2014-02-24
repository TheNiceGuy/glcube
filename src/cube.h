/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  cube.h                                                             //
//                                                                     //
//  Copyright (c) 2013-2014 Gabriel-Andrew Pollo Guilbert              //
//                          <gabriel14_wii@hotmail.com>                //
//                                                                     //
//                        All Rights Reserved                          //
//                                                                     //
//  This program is free software. It comes without  any warranty, to  //
//  the extent permitted by  applicable law. You can  redistribute it  //
//  and/or modify it under the terms of the Do What the Fuck You Want  //
//  to  Public  License, Version 2, as  published by Sam Hocevar. See  //
//  http://www.wtfpl.net/ for more details.                            //
//                                                                     //
/////////////////////////////////////////////////////////////////////////  

#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include <new>

#include "matrix.h"
#include "global.h"

enum action
{
	SET,
	RESET
};
enum direction
{
	NEXT,
	BACKWARD
};

enum piece_type
{
	CENTER,
	CORNER,
	SIDE,
	MIDDLE,
	UNDEF
};

enum face
{
	FRONT,
	BACK,
	TOP,
	BOTTOM,
	RIGHT,
	LEFT
};

enum rotation
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
};

const uint8_t colorScheme[8][3] =  {{  0,   0,   0},  //0 plastic
				    {255, 255, 255},  //1 White
				    {255, 255,   0},  //2 Yellow
				    {  0,   0, 255},  //3 Blue
				    {  0, 255,   0},  //4 Green
				    {255,   0,   0},  //5 red
				    {255, 155,   0},  //6 Orange
				    {  0, 255, 255}}; //7 selection
const float CUBEVER[8][3]     =    {{-0.5,-0.5,-0.5},
				    { 0.5,-0.5,-0.5},
				    { 0.5, 0.5,-0.5},
				    {-0.5, 0.5,-0.5},
				    {-0.5,-0.5, 0.5},
				    { 0.5,-0.5, 0.5},
				    { 0.5, 0.5, 0.5},
				    {-0.5, 0.5, 0.5}};
const uint8_t CUBEFACE[6][4]    =  {{4, 5, 6, 7},
				    {0, 1, 2, 3},
				    {3, 2, 6, 7},
				    {0, 1, 5, 4},
				    {1, 2, 6, 5},
				    {0, 3, 7, 4}};

struct cubies
{
	bool is_selected;
	uint8_t color[6];   //1, 2, 3, 4, 5, 6
	uint8_t pos[3];
	uint8_t type;       //enum piece_type
	matrix mat;
	
	cubies()
	{
		is_selected = false;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		color[3] = 0;
		color[4] = 0;
		color[5] = 0;
		type       = 0;
	}
};

struct layer
{
	uint8_t face;
	uint8_t cur_layer;
	
	layer()
	{
		face      = BACK;
		cur_layer = 0;
	}
};

class cube
{
	public:
		cube();

		bool is_lock();
		void generate();
		void draw();
		void layer_up();
		void layer_down();
		void rotate(int face, int rot, int offset);
		void move_selection(uint8_t direction);
		void change_selection(uint8_t direction);
		void rotate_selection(uint8_t direction);
		
		~cube();

	private:
		bool lock;
		uint8_t color[6];  //F B T D R L
		uint8_t center[6]; //F B T D R L (color undeterminated)
		uint8_t num_layer;
		uint8_t side_rotating;
		float sti_mar;
		float side_rotation[6];
		int *cubes_index;
		cubies *cubes;
		layer selection;

		void draw_cube(int index);
		void draw_guide();
		void inset_square(float x[4], float y[4], float z[4], bool sel);
		void swap_pieces(int a, int b);
		void detect_selection(int a);
		
		uint8_t test_piece(int x, int y, int z, int a);
};

#endif