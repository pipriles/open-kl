#include <stdio.h>
#include <math.h>
#include "matrix.h"

void rVector(Vector4 v) {
	Vector4 r = { 0, 0, 0, 1 };
	copy_vector(v, r, 4);
}

void rMatrix(Matrix m) {
	Matrix r = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	copy_matrix(m, r);
}

void copy_matrix(Matrix m1, Matrix m2) {
	int i, j;
	for(i=0; i < 4; i++) {
		for(j=0; j < 4; j++) 
			m1[i][j] = m2[i][j];
	}
}

void showMatrix(Matrix m) {
	int i, j;
	for(i=0; i < 4; i++) {
		for(j=0; j < 4; j++) {
			printf(" %.1f", m[i][j]);
		} printf("\n");
	}
}

void showVector(Vector4 v) {
	int i;
	for(i=0; i < 4; i++)
		printf(" %f", v[i]);
}

void copy_vector(double *u, double *v, const int size) {
	int i;
	for(i=0; i < size; i++)
		u[i] = v[i];
}

void mm_product(Matrix m1, Matrix t) {

	Matrix r;
	const int size = 4;
	int i, j, k;

	/* Calculate product */
	for(i=0; i < size; i++) {
		for(j=0; j < size; j++) {
			r[i][j] = 0;
			for(k=0; k < size; k++) 
				r[i][j] += t[i][k] * m1[k][j];
		}
	}

	copy_matrix(m1, r);
}

void mv_product(Matrix m, Vector4 v) {

	Vector4 r;
	const int size = 4;
	int i, k;

	for(i=0; i < size; i++) {
		r[i] = 0;
		for(k=0; k < size; k++)
			r[i] += m[i][k] * v[k];
	} 

	/* Copy result */
	copy_vector(v, r, 4);
}

/* Not really cross product */
void cross_product(Vector3 u, Vector3 v) {

	Vector4 r;
	r[0] = u[1] * v[2] - u[2] * v[1];
	r[1] = u[2] * v[0] - u[0] * v[2];
	r[2] = u[0] * v[1] - u[1] * v[0];
	copy_vector(u, r, 3);

}

void normalize(double *v, const int size) {

	double n = 0;
	int i;

	/* Calculate the norm */
	for(i=0; i < size; i++) 
		n += v[i] * v[i];
	n = sqrt(n);

	/* Normalize */
	for(i=0; i < size; i++)
		v[i] /= n;
}

/*
	 void copy_array(double *t1, double *t2, int size) {
	 for(int i=0; i < size; i++) t1[i] = t2[i]; 
	 }

	 class Matrix {

	 double *data = NULL;

	 public:
	 unsigned rows = 0;
	 unsigned cols = 0;

	 Matrix(int rows, int cols) {
	 this->rows = rows;
	 this->cols = cols;
	 this->data = new double[rows * cols];
	 }

	 Matrix(const Matrix &m) {
	 this->rows = m.rows;
	 this->cols = m.cols;
	 copy_array(this->data, m.data);
	 }

	 inline double at(int i, int j) {
	 return this->data ? this->data[i * rows + j] : 0;
	 }

	 Matrix operator*(const Matrix &m) {
	 Matrix t;
	 if (this->rows != m.cols) return t;
	 return t;
	 }

	 ~Matrix() {
	 delete[] data;
	 }
	 }

*/


