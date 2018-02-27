#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kool_aid.h"

static unsigned int klScreenWidth  = 0;
static unsigned int klScreenHeight = 0;

void klViewport(unsigned int w, unsigned int h) {
	klScreenWidth  = w;
	klScreenHeight = h;
}

void klRotateX(Matrix m, float deg) {
	Matrix t = { 
		{ 1,        0,         0, 0, }, 
		{ 0, cos(deg), -sin(deg), 0, },
		{ 0, sin(deg),  cos(deg), 0, },
		{ 0,        0,         0, 1  },
	};
	mm_product(m, t);
}

void klRotateY(Matrix m, float deg) {
	Matrix t = {
		{  cos(deg), 0, sin(deg), 0, },
		{				  0, 1,        0, 0, },
		{ -sin(deg), 0, cos(deg), 0, },
		{         0, 0,        0, 1  },
	};
	mm_product(m, t);
}

void klRotateZ(Matrix m, float deg) {
	Matrix t = {
		{ cos(deg), -sin(deg), 0, 0, },
		{ sin(deg),  cos(deg), 0, 0, },
		{ 			 0,         0, 1, 0, },
		{ 			 0,         0, 0, 1  },
	};
	mm_product(m, t);
}


void klTranslate(Matrix m, float x, float y, float z) {
	Matrix t = { { 1,0,0,x }, { 0,1,0,y }, { 0,0,1,z }, { 0,0,0,1 } };
	mm_product(m, t);
}

void klScale(Matrix m, float x, float y, float z) {
	Matrix t = { { x,0,0,0 }, { 0,y,0,0 }, { 0,0,z,0 }, { 0,0,0,1 } };
	mm_product(m, t);
}

void klLookAt(Matrix m, Vector3 e, Vector3 t) {

	Vector3 u = { 0, 1, 0 }; /* For now it is 0, 1, 0 */
	Vector3 f, l;
	Matrix cam;

	f[0] = e[0] - t[0];
	f[1] = e[1] - t[1];
	f[2] = e[2] - t[2];

	normalize(f, 4);			/* Normalize forward vector */
	copy_vector(l, u, 3);	/* Copy forward into left vector */
	cross_product(l, f);	/* Cross product l(up) and forward */

	/* Rotation Matrix */
	rMatrix(cam);
	klTranslate(cam, -e[0], -e[1], -e[2]);
	cam[0][0] = l[0];
	cam[0][1] = l[1];
	cam[0][2] = l[2];
	cam[1][0] = u[0];
	cam[1][1] = u[1];
	cam[1][2] = u[2];
	cam[2][0] = f[0];
	cam[2][1] = f[1];
	cam[2][2] = f[2];

	mm_product(m, cam);

}

double klDisplayX(Point p) {
	/* Assume d is 1 */
	return p.x / p.z;
}

double klDisplayY(Point p) {
	/* Assume d is 1 */

	return p.y / p.z;
}

int klViewportX(const double x) {
	/* ugly shit */
	return (int) ((x + 1) * klScreenWidth / 2);
}

int klViewportY(const double y) {
	/* more ugly shit */
	return (int) ((y + 1) * klScreenHeight / 2);
}

int klToViewport(Point p, unsigned int *x, unsigned int *y) {

	double fx = klDisplayX(p);
	double fy = klDisplayY(p);

	if (fx < -1 || fx > 1 || 
			fy < -1 || fy > 1 ) 
		return 1;

	*x = klViewportX(fx);
	*y = klViewportY(fy);

	return 0;

}

void klLoadTMesh(const char *path, TMesh *mesh) {

	FILE *fp = fopen(path, "r");
	unsigned int i, n, m, offset;
	Point *pt;
	TFace *fc;

	if (fp == NULL) return;

	fscanf(fp, "OFF %d %d %d", &n, &m, &offset);
	printf(" %d %d %d\n", n, m, offset);

	mesh->pcount = n;
	mesh->fcount = m;

	mesh->points = (Point *) malloc(n * sizeof(Point));
	mesh->faces  = (TFace *) malloc(m * sizeof(TFace));

	for(i=0; i < n; i++) {
		pt = (Point *) &(mesh->points[i]);
		fscanf(fp, " %lf", &(pt->x));
		fscanf(fp, " %lf", &(pt->y));
		fscanf(fp, " %lf", &(pt->z));
	};

	for(i=0; i < m; i++) {
		fc = (TFace *) &(mesh->faces[i]);
		fscanf(fp, " %d", &offset);
		fscanf(fp, " %d", &(fc->edges[0]));
		fscanf(fp, " %d", &(fc->edges[1]));
		fscanf(fp, " %d", &(fc->edges[2]));
	}

	fclose(fp);

}

void klFreeTMesh(TMesh *mesh) {

	mesh->pcount = 0;
	mesh->fcount = 0;

	free(mesh->points);
	free(mesh->faces);

	mesh->points = NULL;
	mesh->faces = NULL;

}

void klApplyTMesh(Matrix t, TMesh *m) {

	unsigned int i;
	Vector4 u;
	Point *p;

	for(i=0; i < m->pcount; i++) {
		p = &m->points[i];

		/* Transform to Vector4 */
		u[0] = p->x;
		u[1] = p->y;
		u[2] = p->z;
		u[3] = 1;
		mv_product(t, u); 

		/* Transform again to point 
		 * very bad... */
		p->x = u[0];
		p->y = u[1];
		p->z = u[2];
	}

}

