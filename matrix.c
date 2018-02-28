#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

void rVector(Vector4 v) {
	Vector4 r = { 0, 0, 0, 1 };
	memcpy(v, r, 4 * sizeof(double));
}

void rMatrix(Matrix m) {
	Matrix r = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	memcpy(m, r, 16 * sizeof(double));
	// copy_matrix(m, r);
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

	memcpy(m1, r, 16 * sizeof(double));
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
	memcpy(v, r, 4 * sizeof(double));
}

/* Not really cross product */
void cross_product(Vector3 u, Vector3 v) {

	Vector4 r;
	r[0] = u[1] * v[2] - u[2] * v[1];
	r[1] = u[2] * v[0] - u[0] * v[2];
	r[2] = u[0] * v[1] - u[1] * v[0];

	memcpy(u, r, 3 * sizeof(double));
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

