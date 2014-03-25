/*
 * cube.cpp
 *
 * Copyright (c) 2013-2014 Gabriel-Andrew Pollo Guilbert
 *                         <gabriel14_wii@hotmail.com>
 *
 *                       All Rights Reserved
 *
 * This program is free software. It comes without  any warranty, to
 * the extent permitted by  applicable law. You can  redistribute it
 * and/or modify it under the terms of the Do What the Fuck You Want
 * to  Public  License, Version 2, as  published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#include "cube.h"

using namespace std;

bool cube::is_lock()
{
	return lock;
}

void cube::generate()
{
	lock = true;
	int a, b;
	int x, y, z;
	int cube_count;

	cube_count = pow(num_layer, 3);

	// pointer to the cubies table
	delete [] cubes;
	delete [] cubes_index;
	cubes = new (nothrow) cubies[cube_count];
	cubes_index = new (nothrow) int[cube_count];

	// generating base puzzle
	a = 0;
	x = 0;
	y = 0;
	z = 0;
	while(z<num_layer)
	{
		cubes[a].pos[0] = x;
		cubes[a].pos[1] = y;
		cubes[a].pos[2] = z;

		cubes_index[a] = a;
		
		// set color
		if(z == num_layer-1)
			cubes[a].color[0] = 1;
		if(z == 0)
			cubes[a].color[1] = 2;
		if(y == num_layer-1)
			cubes[a].color[2] = 3;
		if(y == 0)
			cubes[a].color[3] = 4;
		if(x == num_layer-1)
			cubes[a].color[4] = 5;
		if(x == 0)
			cubes[a].color[5] = 6;		

		cubes[a].type = test_piece(x, y, z, a);
		
		x++;
		if(x==num_layer)
		{
			x=0;
			y++;
			if(y==num_layer)
			{
				y=0;
				z++;
			}
		}
		a++;
	}
	lock = false;
	detect_selection(SET);
}

void cube::draw()
{
	int a;
	int cube_count;
	float matrix[16];
	
	cube_count = pow(num_layer, 3);

	for(a=0; a<cube_count; a++)
	{
		if(cubes[a].type != UNDEF)
		{
			glPushMatrix();
			glTranslatef(-(num_layer/2.0)+cubes[a].pos[0]+0.5,
			             -(num_layer/2.0)+cubes[a].pos[1]+0.5,
			             -(num_layer/2.0)+cubes[a].pos[2]+0.5);

			glMultMatrixf(cubes[a].mat.mat);
			//draw_guide();
			draw_cube(a);
			glPopMatrix();
		}
	}
}

void cube::layer_up()
{
	num_layer = num_layer + 1;
	generate();
	detect_selection(SET);
}

void cube::layer_down()
{
	num_layer = num_layer - 1;
	fix_selection();
	if(num_layer <= 0)
		num_layer = 1;
	generate();
	detect_selection(SET);
}

void cube::rotate(int face, int rot, int offset)
{
	int pos[4];
	int index[2];
	int a, b, c;
	int x, y, z;
	int swap_level, swap_number;
	
	a = num_layer-1;
	if(face == FRONT or face == RIGHT or face == TOP)
	{
		switch(face)
		{
			case FRONT:
				face = BACK;
				break;
			case RIGHT:
				face = LEFT;
				break;
			case TOP:
				face = BOTTOM;
				break;
		}
		
		offset = a-offset;
		if(rot == CLOCKWISE)
			rot = COUNTER_CLOCKWISE;
		else
			rot = CLOCKWISE;
	}
	if(offset == 0 or offset == num_layer-1)
		swap_level = floor(num_layer/2);
	else
		swap_level = 1;
	
	index[0] = 0;
	while(swap_level>0)
	{
		index[1]    = 0;
		swap_number = a-(2*index[0]);
		while(swap_number>0)
		{	
			if(face == BACK)
			{
				pos[0] = (index[0]+index[1])+
				         (index[0])*num_layer+
				         (offset)*num_layer*num_layer;
				pos[1] = (a-index[0])+
				         (index[0]+index[1])*num_layer+
				         (offset)*num_layer*num_layer;
				pos[2] = (a-index[0]-index[1])+
				         (a-index[0])*num_layer+
				         (offset)*num_layer*num_layer;
				pos[3] = (index[0])+
				         (a-index[0]-index[1])*num_layer+
				         (offset)*num_layer*num_layer;
				if(rot == COUNTER_CLOCKWISE)
				{
					swap_pieces(pos[0], pos[1]);
					swap_pieces(pos[1], pos[2]);
					swap_pieces(pos[2], pos[3]);
				}
				else
				{
					swap_pieces(pos[0], pos[3]);
					swap_pieces(pos[3], pos[2]);
					swap_pieces(pos[2], pos[1]);	
				}
			}
			else if(face == LEFT)
			{
				pos[0] = (offset)+
				         (index[0])*num_layer+
				         (index[0]+index[1])*num_layer*num_layer;
				pos[1] = (offset)+
				         (index[0]+index[1])*num_layer+
				         (a-index[0])*num_layer*num_layer;
				pos[2] = (offset)+
				         (a-index[0])*num_layer+
				         (a-index[0]-index[1])*num_layer*num_layer;
				pos[3] = (offset)+
				         (a-index[0]-index[1])*num_layer+
				         (index[0])*num_layer*num_layer;
				if(rot == CLOCKWISE)
				{
					swap_pieces(pos[0], pos[1]);
					swap_pieces(pos[1], pos[2]);
					swap_pieces(pos[2], pos[3]);
				}
				else
				{
					swap_pieces(pos[0], pos[3]);
					swap_pieces(pos[3], pos[2]);
					swap_pieces(pos[2], pos[1]);	
				}
			}
			else if(face == BOTTOM)
			{
				pos[0] = (index[0]+index[1])+
				         (offset)*num_layer+
				         (index[0])*num_layer*num_layer;
				pos[1] = (index[0])+
				         (offset)*num_layer+
				         (a-index[0]-index[1])*num_layer*num_layer;
				pos[2] = (a-index[0]-index[1])+
				         (offset)*num_layer+
				         (a-index[0])*num_layer*num_layer;
				pos[3] = (a-index[0])+
				         (offset)*num_layer+
				         (index[0]+index[1])*num_layer*num_layer;
				if(rot == CLOCKWISE)
				{
					swap_pieces(pos[0], pos[1]);
					swap_pieces(pos[1], pos[2]);
					swap_pieces(pos[2], pos[3]);
				}
				else
				{
					swap_pieces(pos[0], pos[3]);
					swap_pieces(pos[3], pos[2]);
					swap_pieces(pos[2], pos[1]);	
				}
			}
			index[1]++;
			swap_number--;
		}
		index[0]++;
		swap_level--;
	}

	if(face == BACK)
	{
		for(x = 0; x<num_layer; x++)
		{
			for(y = 0; y<num_layer; y++)
			{
				a = x+y*num_layer+offset*num_layer*num_layer;
				if(rot == COUNTER_CLOCKWISE)
					cubes[cubes_index[a]].mat.rotZ( 90);
				else
					cubes[cubes_index[a]].mat.rotZ(-90);
			}
		}
	}
	else if(face == LEFT)
	{
		for(y = 0; y<num_layer; y++)
		{
			for(z = 0; z<num_layer; z++)
			{	
				a = offset+y*num_layer+z*num_layer*num_layer;
				if(rot == COUNTER_CLOCKWISE)
					cubes[cubes_index[a]].mat.rotX(-90);
				else
					cubes[cubes_index[a]].mat.rotX( 90);
			}
		}
	}
	else if(face == BOTTOM)
	{
		for(x = 0; x<num_layer; x++)
		{
			for(z = 0; z<num_layer; z++)
			{	
				a = x+offset*num_layer+z*num_layer*num_layer;
				if(rot == COUNTER_CLOCKWISE)
					cubes[cubes_index[a]].mat.rotY(-90);
				else
					cubes[cubes_index[a]].mat.rotY( 90);
			}
		}
	}
}

void cube::move_selection(uint8_t direction)
{
	detect_selection(RESET);
	if(direction == NEXT)
	{
		selection.cur_layer = selection.cur_layer + 1;
		if(selection.cur_layer == num_layer)
			selection.cur_layer = 0;
	}
	else
	{
		selection.cur_layer = selection.cur_layer - 1;
		if(selection.cur_layer == 255)
			selection.cur_layer = num_layer-1;
	}
	detect_selection(SET);
}

void cube::change_selection(uint8_t direction)
{
	detect_selection(RESET);
	if(direction == NEXT)
	{
		switch(selection.face)
		{
			case BACK:
				selection.face = BOTTOM;
				break;
			case BOTTOM:
				selection.face = LEFT;
				break;
			case LEFT:
				selection.face = BACK;
				break;
		}
	}
	else
	{
		switch(selection.face)
		{
			case BACK:
				selection.face = LEFT;
				break;
			case LEFT:
				selection.face = BOTTOM;
				break;
			case BOTTOM:
				selection.face = BACK;
				break;
		}
	}
	detect_selection(SET);
}

void cube::rotate_selection(uint8_t direction)
{
	if(direction == CLOCKWISE)
		rotate(selection.face, CLOCKWISE, selection.cur_layer);
	else
		rotate(selection.face, COUNTER_CLOCKWISE, selection.cur_layer);
}

//////////////////////
// private function //
//////////////////////

cube::cube()
{
	int a;
	lock = false;
	for(a = 0; a<6; a++)
	{
		color[a]         = 0;
		center[a]        = 0;
		side_rotation[a] = 0;
	}
	num_layer     = 8;
	sti_mar       = 0.15;
	side_rotating = 6;
	generate();
}

void cube::draw_cube(int index)
{
	int a, b;
	float x[4], y[4], z[4];
	
	for(a=0; a<6; a++)
	{
		glColor3ub(colorScheme[cubes[index].color[a]][0],
		           colorScheme[cubes[index].color[a]][1],
		           colorScheme[cubes[index].color[a]][2]);

		if(cubes[index].color[a] == 0)
		{
			glBegin(GL_QUADS);
				glVertex3f(CUBEVER[CUBEFACE[a][0]][0], CUBEVER[CUBEFACE[a][0]][1], CUBEVER[CUBEFACE[a][0]][2]);
				glVertex3f(CUBEVER[CUBEFACE[a][1]][0], CUBEVER[CUBEFACE[a][1]][1], CUBEVER[CUBEFACE[a][1]][2]);
				glVertex3f(CUBEVER[CUBEFACE[a][2]][0], CUBEVER[CUBEFACE[a][2]][1], CUBEVER[CUBEFACE[a][2]][2]);
				glVertex3f(CUBEVER[CUBEFACE[a][3]][0], CUBEVER[CUBEFACE[a][3]][1], CUBEVER[CUBEFACE[a][3]][2]);
			glEnd();
		}
		else
		{
			for(b = 0; b<4; b++)
			{
				x[b] = CUBEVER[CUBEFACE[a][b]][0];
				y[b] = CUBEVER[CUBEFACE[a][b]][1];
				z[b] = CUBEVER[CUBEFACE[a][b]][2];
			}
			inset_square(x, y, z, cubes[index].is_selected);
		}
	}
}

void cube::draw_guide()
{
	glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 2, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 2);
	glEnd();
}

void cube::inset_square(float x[4], float y[4], float z[4], bool sel)
{
	int a;
	float mar;
	float m[3];
	float t[3];
	float i[4][3];

	t[0] = x[0];
	t[1] = y[0];
	t[2] = z[0];
	
	for(a = 0; a<4; a++)
	{
		x[a] = x[a] - t[0];
		y[a] = y[a] - t[1];
		z[a] = z[a] - t[2];
	}
	
	m[0] = (x[0]+x[1]+x[2]+x[3])/4;
	m[1] = (y[0]+y[1]+y[2]+y[3])/4;
	m[2] = (z[0]+z[1]+z[2]+z[3])/4;

	for(a = 0; a<4; a++)
	{
		x[a] = x[a] - m[0];
		y[a] = y[a] - m[1];
		z[a] = z[a] - m[2];
	}
	
	glPushMatrix();
	glTranslatef(t[0]+m[0], t[1]+m[1], t[2]+m[2]);

	m[0] = 0;
	m[1] = 0;
	m[2] = 0;

	mar = 1-sti_mar;
	for(a = 0; a<4; a++)
	{
		i[a][0] = (x[a]-m[0])*mar;
		i[a][1] = (y[a]-m[1])*mar;
		i[a][2] = (z[a]-m[2])*mar;
	}
	
	glBegin(GL_QUADS);
		glVertex3f(i[0][0], i[0][1], i[0][2]);
		glVertex3f(i[1][0], i[1][1], i[1][2]);
		glVertex3f(i[2][0], i[2][1], i[2][2]);
		glVertex3f(i[3][0], i[3][1], i[3][2]);
		
		//glEnd();draw_guide();glBegin(GL_QUADS);
		if(sel == false)
		{
			glColor3ub(colorScheme[0][0],
			           colorScheme[0][1],
			           colorScheme[0][2]);
		}
		else
		{
			glColor3ub(colorScheme[7][0],
			           colorScheme[7][1],
			           colorScheme[7][2]);
		}
		
		glVertex3f(x[0], y[0], z[0]);
		glVertex3f(x[1], y[1], z[1]);
		glVertex3f(i[1][0], i[1][1], i[1][2]);
		glVertex3f(i[0][0], i[0][1], i[0][2]);

		glVertex3f(x[1], y[1], z[1]);
		glVertex3f(x[2], y[2], z[2]);
		glVertex3f(i[2][0], i[2][1], i[2][2]);
		glVertex3f(i[1][0], i[1][1], i[1][2]);

		glVertex3f(x[2], y[2], z[2]);
		glVertex3f(x[3], y[3], z[3]);
		glVertex3f(i[3][0], i[3][1], i[3][2]);
		glVertex3f(i[2][0], i[2][1], i[2][2]);

		glVertex3f(x[3], y[3], z[3]);
		glVertex3f(x[0], y[0], z[0]);
		glVertex3f(i[0][0], i[0][1], i[0][2]);
		glVertex3f(i[3][0], i[3][1], i[3][2]);
	glEnd();
	glPopMatrix();
}

uint8_t cube::test_piece(int x, int y, int z, int a)
{
	int b, c;
	uint8_t ptype;
	
	ptype = UNDEF;
	c = 0;
	
	// test center pieces
	if(num_layer%2 != 0)
	{
		b = floor(num_layer/2);
		if(x == b and y == b and z == num_layer-1)
		{
			center[0] = a;
			ptype = CENTER;
		}
		else if(x == b and y == b and z == 0)
		{
			center[1] = a;
			ptype = CENTER;
		}
		else if(x == b and y == num_layer-1 and z == b)
		{
			center[2] = a;
			ptype = CENTER;
		}
		else if(x == b and y == 0 and z == b)
		{
			center[3] = a;
			ptype = CENTER;
		}
		else if(x == num_layer-1 and y == b and z == b)
		{
			center[4] = a;
			ptype = CENTER;
		}
		else if(x == 0 and y == b and z == b)
		{
			center[5] = a;
			ptype = CENTER;
		}
	}
	
	if(ptype == UNDEF)
	{
		if(x == 0 or x == num_layer-1)
			c++;
		if(y == 0 or y == num_layer-1)
			c++;
		if(z == 0 or z == num_layer-1)
			c++;

		if(c == 3)
			ptype = CORNER;
		else if(c == 2)
			ptype = SIDE;
		else
			ptype = MIDDLE;
	}
	
	return ptype;
}

void cube::swap_pieces(int a, int b)
{
	int c, d;
	
	for(c = 0; c<3; c++)
	{
		d = cubes[cubes_index[a]].pos[c];
		cubes[cubes_index[a]].pos[c] = cubes[cubes_index[b]].pos[c];
		cubes[cubes_index[b]].pos[c] = d;
		d = cubes_index[a];
		cubes_index[a] = cubes_index[b];
		cubes_index[b] = d;
	}
}

void cube::detect_selection(int a)
{
	int x,y,z;
	
	if(selection.face == BACK)
	{
		z = selection.cur_layer;
		for(x = 0; x<num_layer; x++)
		{
			for(y = 0; y<num_layer; y++)
			{
				if(a == SET)
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = true;
				else
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = false;
			}
		}
	}
	else if(selection.face == LEFT)
	{
		x = selection.cur_layer;
		for(y = 0; y<num_layer; y++)
		{
			for(z = 0; z<num_layer; z++)
			{
				if(a == SET)
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = true;
				else
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = false;			}
		}
	}
	else if(selection.face == BOTTOM)
	{
		y = selection.cur_layer;
		for(x = 0; x<num_layer; x++)
		{
			for(z = 0; z<num_layer; z++)
			{
				if(a == SET)
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = true;
				else
					cubes[cubes_index[x+(y*num_layer)+(z*num_layer*num_layer)]].is_selected = false;			}
		}
	}
}

void cube::fix_selection()
{
	if(selection.cur_layer > num_layer-1)
		selection.cur_layer = num_layer-1;
}

cube::~cube()
{
  	//free(cubes_index);
	//free(cubes);
}
