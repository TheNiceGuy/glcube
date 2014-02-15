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