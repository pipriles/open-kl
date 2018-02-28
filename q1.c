#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "kool_aid.h"
#include "bitmap.h"

void draw_mesh(TMesh *);

int main(int argc, char const* argv[]) {

	const int width  = 600;
	const int height = 600;

	Matrix m; // should not exist!!
	TMesh camel, dino, pig, cow, dilo;

	klLoadTMesh("Modelos/camello.off", &camel);
	klLoadTMesh("Modelos/dinosaurio.off", &dino);
	klLoadTMesh("Modelos/cochino.off", &pig);
	klLoadTMesh("Modelos/vaca.off", &cow);
	klLoadTMesh("Modelos/dilo.off", &dilo);

	BMP_LoadImage(width, height, 96);
	klViewport(width, height);

	rMatrix(m); // replace by load identy
	// should not receive any matrix! (right?)
	klRotateZ(m, 180 * M_PI / 180);
	klRotateY(m, 110 * M_PI / 180);
	klTranslate(m, 0.5, 0, -1);
	klApplyTMesh(m, &camel);

	rMatrix(m);
	klRotateZ(m, 180 * M_PI / 180);
	klRotateY(m, 160 * M_PI / 180);
	klTranslate(m, -1, -0.02, -1);
	klApplyTMesh(m, &dino);

	rMatrix(m);
	klRotateY(m, 20 * M_PI / 180);
	klTranslate(m, 2, 0.25, -4);
	klApplyTMesh(m, &pig);

	rMatrix(m);
	klRotateZ(m, M_PI);
	klTranslate(m, -2.5, 0, -3);
	klApplyTMesh(m, &cow);

	rMatrix(m);
	klTranslate(m, 0, 0, -5);
	klApplyTMesh(m, &dilo);

	rMatrix(m);
	klLookAt(m, 0, 0, -1, 0, 0, 0);

	/* We have to find a workaround */
	klApplyTMesh(m, &camel);
	klApplyTMesh(m, &dino);
	klApplyTMesh(m, &pig);
	klApplyTMesh(m, &cow);
	klApplyTMesh(m, &dilo);

	showMatrix(m);
		
	draw_mesh(&camel);
	draw_mesh(&dino);
	draw_mesh(&pig);
	draw_mesh(&cow);
	draw_mesh(&dilo);

	BMP_Save("screen.bmp");
	BMP_FreeImage();

	klFreeTMesh(&camel);
	klFreeTMesh(&dino);
	klFreeTMesh(&pig);
	klFreeTMesh(&cow);
	klFreeTMesh(&dilo);

	return 0; 
}

void draw_mesh(TMesh *mesh) {

	Point *p;
	unsigned int i, x, y;
	int err = 0;

	for(i=0; i < mesh->pcount; i++) {
		p = &mesh->points[i];
		err = klToViewport(*p, &x, &y);
		if (!err) 
			BMP_SetPixel(x, y, 255, 255, 255);
	}

}
