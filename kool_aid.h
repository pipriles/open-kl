#ifndef _KOOL_H_
#define _KOOL_H_

#include "matrix.h"

typedef struct {
	double x, y, z;
} Point;

typedef struct {
	unsigned int edges[3];
} TFace;

typedef struct {
	unsigned int pcount;
	unsigned int fcount;
	Point *points;
	TFace *faces;
} TMesh;

void klViewport(unsigned int, unsigned int);
void klRotateX(Matrix, double);
void klRotateY(Matrix, double);
void klRotateZ(Matrix, double);
void klTranslate(Matrix, double, double, double);
void klScale(Matrix, double, double, double);
void klLookAt(Matrix, double, double, double, double, double, double);

double klDisplayX(Point);
double klDisplayY(Point);

int klViewportX(const double x);
int klViewportY(const double y);
int klToViewport(Point v, unsigned int *, unsigned int *);

/* Load mesh from file */
void klLoadTMesh(const char *, TMesh *);
void klFreeTMesh(TMesh *);

void klApplyTMesh(Matrix, TMesh *);

/* utility shit */
void klDisplayTMesh(TMesh *);

#endif
