#include "cube.h"

using namespace std;

void cube::generate()
{
	int a, b, c;
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

		cubes[a].type = test_corner(x, y, z);
		if(cubes[a].type != 1)
		{
			cubes[a].type = test_edge(x, y, z);
		}

		// inner pieces
		if(x!=0 and x!=(num_layer-1) and
		   y!=0 and y!=(num_layer-1) and
		   z!=0 and z!=(num_layer-1))
		{
//			cout << x << y << z << endl;
			for(b=0; b<6; b++)
			{
				cubes[a].color[b] = 0;
			}
		}

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

		// set center pieces
		if(num_layer%2 != 0)
		{
			c = floor(num_layer/2);
			if(x == c and y == c and z == 0)
				center[0] = a;
			else if(x == c and y == c and z == num_layer-1)
				center[1] = a;
			else if(x == 0 and y == c and z == c)
				center[2] = a;
			else if(x == num_layer-1 and y == c and z == c)
				center[3] = a;
			else if(x == c and y == 0 and z == c)
				center[4] = a;
			else if(x == c and y == num_layer-1 and z == c)
				center[5] = a;
		}
		a++;
	}

	
}

void cube::draw()
{
	int a;
	int cube_count;

	cube_count = pow(num_layer, 3);

	for(a=0; a<cube_count; a++)
	{
		if(cubes[a].isrotating != 6)
		{
			//To be added
		}
		glPushMatrix();
		glTranslatef(-(num_layer/2.0)+cubes[a].pos[0],
					 -(num_layer/2.0)+cubes[a].pos[1],
					 -(num_layer/2.0)+cubes[a].pos[2]);
		draw_cube(a);
		glPopMatrix();		
	}
}

void cube::layer_up()
{
	num_layer = num_layer + 1;
}

void cube::layer_down()
{
	num_layer = num_layer - 1;
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
}

void cube::draw_cube(int index)
{
	int a;

	for(a=0; a<6; a++)
	{
		glColor3ub(colorScheme[cubes[index].color[a]][0],
				   colorScheme[cubes[index].color[a]][1],
				   colorScheme[cubes[index].color[a]][2]);

		glBegin(GL_QUADS);
			glVertex3f(CUBEVER[CUBEFACE[a][0]][0]+0.1, CUBEVER[CUBEFACE[a][0]][1], CUBEVER[CUBEFACE[a][0]][2]);
			glVertex3f(CUBEVER[CUBEFACE[a][1]][0]+0.1, CUBEVER[CUBEFACE[a][1]][1], CUBEVER[CUBEFACE[a][1]][2]);
			glVertex3f(CUBEVER[CUBEFACE[a][2]][0]+0.1, CUBEVER[CUBEFACE[a][2]][1], CUBEVER[CUBEFACE[a][2]][2]);
			glVertex3f(CUBEVER[CUBEFACE[a][3]][0]+0.1, CUBEVER[CUBEFACE[a][3]][1], CUBEVER[CUBEFACE[a][3]][2]);
		glEnd();
	}
}

int cube::test_corner(int x, int y, int z)
{
	int result;
	result = 3;
	
	if((x == 0 or x == (num_layer-1)) and
	   (y == 0 or y == (num_layer-1)) and
	   (z == 0 or z == (num_layer-1)))
	{
		result = 1;
	}
	
	return 1;
}

int cube::test_edge(int x, int y, int z)
{
	bool result;
	result = false;
	
	
}

void cube::swap_pieces(int a, int b)
{

}

cube::~cube()
{

}






