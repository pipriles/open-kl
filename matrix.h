#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef double Matrix[4][4];
typedef double Vector3[3];
typedef double Vector4[4];

void rVector(Vector4);
void rMatrix(Matrix);

void showMatrix(Matrix);
void showVector(Vector4);

void copy_matrix(Matrix, Matrix);
void copy_vector(double *, double *, const int);

void mm_product(Matrix, Matrix);
void mv_product(Matrix, Vector4);

void cross_product(Vector3 u, Vector3 v);
void normalize(double *, const int size);

#endif
