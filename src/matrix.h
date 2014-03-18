/*
 * matrix.h
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

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>

#include "global.h"

class matrix
{
	public:
		matrix();

		float mat[16];

		void print();
		void rotX(float x);
		void rotY(float y);
		void rotZ(float z);
		void set_matrix(float set_mat[16]);
		float* get_matrix();

		~matrix();

	private:
		void product(float m_mat[16]);
};

#endif
