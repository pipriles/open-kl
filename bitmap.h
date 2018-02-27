#ifndef _BITMAP_H_
#define _BITMAP_H_

typedef struct {
	float r, g, b;
} BMP_PIXEL;

typedef struct {
	unsigned char bitmap_type[2];     // 2 bytes
	int           file_size;          // 4 bytes
	short         reserved1;          // 2 bytes
	short         reserved2;          // 2 bytes
	unsigned int  offset_bits;        // 4 bytes
} BMP_FILE_HEADER;

typedef struct {
	unsigned int size_header;        // 4 bytes
	unsigned int width;              // 4 bytes
	unsigned int height;             // 4 bytes
	short int    planes;             // 2 bytes
	short int    bit_count;          // 2 bytes
	unsigned int compression;        // 4 bytes
	unsigned int image_size;         // 4 bytes
	unsigned int ppm_x;              // 4 bytes
	unsigned int ppm_y;              // 4 bytes
	unsigned int clr_used;           // 4 bytes
	unsigned int clr_important;      // 4 bytes
} BMP_IMAGE_HEADER;

typedef struct {
	unsigned int width, height, dpi;
	BMP_FILE_HEADER  bfh;
	BMP_IMAGE_HEADER bih;
} BMP_IMAGE;

void BMP_LoadImage(int w, int h, int dpi);
void BMP_FreeImage();
void BMP_Save(const char *);
void BMP_SetPixel(
		unsigned int x, 
		unsigned int y, 
		float r, float g, float b
	);

#endif

