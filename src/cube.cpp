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
	cubes = new (nothrow) cubies[cube_count];

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
}

void cube::draw()
{
	int a;
	int cube_count;

	cube_count = pow(num_layer, 3);

	for(a=0; a<cube_count; a++)
	{
		if(cubes[a].type != UNDEF)
		{
			glPushMatrix();
			glTranslatef(-(num_layer/2.0)+cubes[a].pos[0],
						-(num_layer/2.0)+cubes[a].pos[1],
						-(num_layer/2.0)+cubes[a].pos[2]);
			draw_cube(a);
			glPopMatrix();
		}
	}
}

void cube::layer_up()
{
	num_layer = num_layer + 1;
	generate();
}

void cube::layer_down()
{
	num_layer = num_layer - 1;
	if(num_layer <= 0)
		num_layer = 1;
	generate();
}

void cube::rotate_front(int r)
{
	int a, b;
	
	a = 0;
	b = 0;
	
	while(b<4)
	{
		if(cubes[a].pos[0] == 0 and
		   cubes[a].pos[1] == 0 and
		   cubes[a].pos[2] == 0)
		{
		}
	}	
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
	num_layer     = 5;
	sti_mar       = 0.1;
	side_rotating = 6;
	generate();
}

void cube::draw_cube(int index)
{
	int a, b;
	int x[4], y[4], z[4];
	
	for(a=0; a<6; a++)
	{
		glColor3ub( colorScheme[cubes[index].color[a]][0],
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
			inset_square(x, y, z);
		}
	}
}

void cube::inset_square(int x[4], int y[4], int z[4])
{
	int a, b;
	int c[3];
	int delta[2][3];
	double vector_length;
	double vector_angle[3];
	double pos[3];
	double point[4][3];

	glPushMatrix();
	glTranslatef(x[0], y[0], z[0]);

	c[0] = x[0];
	c[1] = y[0];
	c[2] = z[0];
	for(a = 0; a<4; a++)
	{
		x[a] = x[a]-c[0];
		y[a] = y[a]-c[1];
		z[a] = z[a]-c[2];
	}
	
	for(a = 0; a<2; a++)
	{
		delta[a][0] = x[2+a]-x[0+a];
		delta[a][1] = y[2+a]-y[0+a];
		delta[a][2] = z[2+a]-z[0+a];

		vector_length = sqrt(pow(delta[a][0], 2) + pow(delta[a][1], 2) + pow(delta[a][2], 2));

		for(b = 0; b<3; b++)
		{
			vector_angle[b] = acos(delta[a][b]/vector_length);

			point[0+a][b] = sti_mar*cos(vector_angle[b]);
			point[2+a][b] = (vector_length-sti_mar)*cos(vector_angle[b]);

			if(a == 1 and delta[a][b] != delta[a-1][b]) 
			{
				point[0+a][b] = point[0+a][b] - delta[a][b];
				point[2+a][b] = point[2+a][b] - delta[a][b];
			}
		}
	}
	glBegin(GL_QUADS);
		glVertex3f(point[0][0], point[0][1], point[0][2]);
		glVertex3f(point[1][0], point[1][1], point[1][2]);
		glVertex3f(point[2][0], point[2][1], point[2][2]);
		glVertex3f(point[3][0], point[3][1], point[3][2]);

		glColor3ub(0, 0, 0);
		for(a = 0; a<3; a++)
		{		
			glVertex3f(x[a], y[a], z[a]);
			glVertex3f(x[a+1], y[a+1], z[a+1]);
			glVertex3f(point[a+1][0], point[a+1][1], point[a+1][2]);
			glVertex3f(point[a][0], point[a][1], point[a][2]);	
		}
		glVertex3f(x[3], y[3], z[3]);
		glVertex3f(x[0], y[0], z[0]);
		glVertex3f(point[0][0], point[0][1], point[0][2]);
		glVertex3f(point[3][0], point[3][1], point[3][2]);	
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

}

cube::~cube()
{
	free(cubes);
}






