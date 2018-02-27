#ifndef _KOOL_H_
#define _KOOL_H_

#include "matrix.h"

typedef struct {
	double x; double y;
	double z;
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
void klRotateX(Matrix, float);
void klRotateY(Matrix, float);
void klRotateZ(Matrix, float);
void klTranslate(Matrix, float, float, float);
void klScale(Matrix, float, float, float);
void klLookAt(Matrix, Vector3, Vector3);

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
