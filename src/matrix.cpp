/*
 * matrix.cpp
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

#include "matrix.h"

using namespace std;

void matrix::print()
{
	cout << mat[ 0] << "	" << mat[ 1] << "	" << mat[ 2] << "	" << mat[ 3] << endl;
	cout << mat[ 4] << "	" << mat[ 5] << "	" << mat[ 6] << "	" << mat[ 7] << endl;
	cout << mat[ 8] << "	" << mat[ 9] << "	" << mat[10] << "	" << mat[11] << endl;
	cout << mat[12] << "	" << mat[13] << "	" << mat[14] << "	" << mat[15] << endl;
}

void matrix::rotX(float x)
{
	x = x*M_PI/180;
	
	float m[16] = {1,      0,      0, 0,
                       0, cos(x), sin(x), 0,
                       0,-sin(x), cos(x), 0,
                       0,      0,      0, 1};

	product(m);
}

void matrix::rotY(float y)
{
	y = y*M_PI/180;
	
	float m[16] = { cos(y), 0, sin(y), 0,
                             0, 1,      0, 0,
                       -sin(y), 0, cos(y), 0,
                             0, 0,      0, 1};

	product(m);
}

void matrix::rotZ(float z)
{
	z = z*M_PI/180;
	
	float m[16] = {cos(z),-sin(z), 0, 0,
                       sin(z), cos(z), 0, 0,
                            0,      0, 1, 0,
                            0,      0, 0, 1};

	product(m);
}

void matrix::set_matrix(float set_mat[16])
{
	int a;
	
	for(a = 0; a<16; a++)
		mat[a] = set_mat[a];
}

//////////////////////
// private function //
//////////////////////

matrix::matrix()
{
	int a;
	for(a = 0; a<16; a++)
	{
		if(a == 0 or a == 5 or a == 10 or a == 15)
			mat[a] = 1;
		else
			mat[a] = 0;
	}
}

void matrix::product(float m[16])
{
	float t[16];
	
	copy(mat, mat+16, t);
	
	mat[ 0] = t[ 0]*m[ 0]+t[ 1]*m[ 4]+t[ 2]*m[ 8]+t[ 3]*m[12];
	mat[ 1] = t[ 0]*m[ 1]+t[ 1]*m[ 5]+t[ 2]*m[ 9]+t[ 3]*m[13];
	mat[ 2] = t[ 0]*m[ 2]+t[ 1]*m[ 6]+t[ 2]*m[10]+t[ 3]*m[14];
	mat[ 3] = t[ 0]*m[ 3]+t[ 1]*m[ 7]+t[ 2]*m[11]+t[ 3]*m[15];

	mat[ 4] = t[ 4]*m[ 0]+t[ 5]*m[ 4]+t[ 6]*m[ 8]+t[ 7]*m[12];
	mat[ 5] = t[ 4]*m[ 1]+t[ 5]*m[ 5]+t[ 6]*m[ 9]+t[ 7]*m[13];
	mat[ 6] = t[ 4]*m[ 2]+t[ 5]*m[ 6]+t[ 6]*m[10]+t[ 7]*m[14];
	mat[ 7] = t[ 4]*m[ 3]+t[ 5]*m[ 7]+t[ 6]*m[11]+t[ 7]*m[15];

	mat[ 8] = t[ 8]*m[ 0]+t[ 9]*m[ 4]+t[10]*m[ 8]+t[11]*m[12];
	mat[ 9] = t[ 8]*m[ 1]+t[ 9]*m[ 5]+t[10]*m[ 9]+t[11]*m[13];
	mat[10] = t[ 8]*m[ 2]+t[ 9]*m[ 6]+t[10]*m[10]+t[11]*m[14];
	mat[11] = t[ 8]*m[ 3]+t[ 9]*m[ 7]+t[10]*m[11]+t[11]*m[15];
	
	mat[12] = t[12]*m[ 0]+t[13]*m[ 4]+t[14]*m[ 8]+t[15]*m[12];
	mat[13] = t[12]*m[ 1]+t[13]*m[ 5]+t[14]*m[ 9]+t[15]*m[13];
	mat[14] = t[12]*m[ 2]+t[13]*m[ 6]+t[14]*m[10]+t[15]*m[14];
	mat[15] = t[12]*m[ 3]+t[13]*m[ 7]+t[14]*m[11]+t[15]*m[15];
}

matrix::~matrix()
{

}
