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
	TMesh camel;
	TMesh dino;

	klLoadTMesh("Modelos/camello.off", &camel);
	klLoadTMesh("Modelos/dinosaurio.off", &dino);

	BMP_LoadImage(width, height, 96);
	klViewport(width, height);

	rMatrix(m); // replace by load identy

	// should not receive any matrix!
	klRotateY(m, -90 * M_PI / 180);
	klTranslate(m, 0.4, 0, -1);
	klApplyTMesh(m, &camel);

	rMatrix(m);
	klTranslate(m, -0.585, -0.02, -1);
	klApplyTMesh(m, &dino);

	showMatrix(m);
		
	draw_mesh(&camel);
	draw_mesh(&dino);

	BMP_Save("screen.bmp");
	BMP_FreeImage();

	klFreeTMesh(&camel);
	klFreeTMesh(&dino);

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
