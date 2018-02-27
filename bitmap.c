#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

static BMP_PIXEL* IMAGE_PIXELS = NULL;
static BMP_IMAGE  IMAGE_PARAMS;

void BMP_LoadImage(int w, int h, int dpi) {

	int image_size = w * h;
	int file_size = 54 + 4 * image_size;
	int ppm = dpi * 39.375;

	IMAGE_PIXELS = (BMP_PIXEL *) 
		malloc(image_size * sizeof(BMP_PIXEL));

	BMP_IMAGE        *img = &IMAGE_PARAMS;
	BMP_FILE_HEADER  *bfh = &img->bfh;
	BMP_IMAGE_HEADER *bih = &img->bih;

	img->width  = w;
	img->height = h;
	img->dpi    = dpi;

	memcpy(&bfh->bitmap_type, "BM", 2);

	bfh->file_size     = file_size;
	bfh->reserved1     = 0;
	bfh->reserved2     = 0;
	bfh->offset_bits   = 0;

	bih->size_header   = sizeof(*bih);
	bih->width         = w;
	bih->height        = -h;
	bih->planes        = 1;
	bih->bit_count     = 24;
	bih->compression   = 0;
	bih->image_size    = file_size;
	bih->ppm_x         = ppm;
	bih->ppm_y         = ppm;
	bih->clr_used      = 0;
	bih->clr_important = 0;

}

void BMP_FreeImage() {
	free(IMAGE_PIXELS);
}

void BMP_SetPixel( 
		unsigned int x, 
		unsigned int y, 
		float r, float g, float b) {

	unsigned int width  = IMAGE_PARAMS.width;
	unsigned int height = IMAGE_PARAMS.width;
	unsigned int offset = y * width + x;

	if ( offset < 0 || offset > width * height )
		return;

	IMAGE_PIXELS[offset].r = r;
	IMAGE_PIXELS[offset].g = g;
	IMAGE_PIXELS[offset].b = b;
}

void BMP_Save(const char *file_name) {

	BMP_IMAGE *img = &IMAGE_PARAMS;
	unsigned int i, w, h, size;
	unsigned char color[3];
	FILE *fp;

	w = img->width;
	h = img->height;
	size = w * h;

	fp = fopen(file_name, "wb");

	fwrite(&img->bfh, 1, 14, fp);
	fwrite(&img->bih, 1, sizeof(img->bih), fp);

	for (i=0; i < size; i++) {
		color[0] = IMAGE_PIXELS[i].b;
		color[1] = IMAGE_PIXELS[i].g;
		color[2] = IMAGE_PIXELS[i].r;
		fwrite(&color, 1, sizeof(color), fp);
	}

	fclose(fp);
}

