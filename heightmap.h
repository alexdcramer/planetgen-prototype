#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

int* genHeightmap(int* len, int* hgt) {

	// the max height of terrain is at 10,240m; or 33,595ft.
	// as such, each increment is 40m above sea level.
	// for the brick, 400m above sea level is used, or 1,312ft.
	// mount everest would be 221, or DD.
	// this is to allow mountains that are still reasonably realistic to form that are taller than earthern mountains.
	// in the future, a tectonics plate system could be used to more reliably generate realistic mountains

	int* heightmapArr = malloc(sizeof(int) * *len * *hgt);
	printf("Creating heightmap with %d length and %d height\n", *len, *hgt);
	int* currentIndex = malloc(sizeof(int));
	for (int i = 0; i < *hgt; i++) {
		for (int j = 0; j < *len; j++) {
			// preferably perlin noise would be used, but i want to create a brick to test first
			if (i > 1 && i < 7 && j > 2 && j < 13) {
				heightmapArr[*currentIndex] = 10;
			} else {
				heightmapArr[*currentIndex] = 0;
			}
			*currentIndex += 1;	
		}
	}
	free(currentIndex);

	return heightmapArr;
}

// FIXME: I break after 108 pixels in width!

void mapToImg(int* heightmap, int* len, int* hgt) {
	
	// partially taken from a stackoverflow answer
	
	int* bits = malloc(sizeof(int));
	int* bitWidth = malloc(sizeof(int));
	int* imgSize = malloc(sizeof(int));
	int* iHeaderSize = malloc(sizeof(int));
	int* offBits = malloc(sizeof(int));
	int* fileSize = malloc(sizeof(int));
	int* numPlanes = malloc(sizeof(int));

	*bits = 24;
	*bitWidth = ((*len * *bits + 31) / 32) * 4;
	*imgSize = *bitWidth * *hgt;
	*iHeaderSize = 40;
	*offBits = 54;
	*fileSize = *imgSize + *offBits;
	*numPlanes = 1;


	// header
	unsigned char header[54] = { 0 };
	memcpy(header, "BM", 2);
	memcpy(header + 2, fileSize, 4);
	memcpy(header + 10, offBits, 4);
	memcpy(header + 14, iHeaderSize, 4);
	memcpy(header + 18, len, 4);
	memcpy(header + 22, hgt, 4);
	memcpy(header + 26, numPlanes, 2);
	memcpy(header + 28, bits, 2);
	memcpy(header + 34, imgSize, 4);
	
	// create pixel buffer
	unsigned char* buffer = malloc(*imgSize);

	int* index = malloc(sizeof(int));
	*index = 0;

	for (int i = *hgt - 1; i >= 0; i--) {
		for (int j = 0; j < *len; j++) {
			if (heightmap[*index] == 0) {
				buffer[i * *bitWidth + j * 3] = 255;
			} else {
				buffer[i * *bitWidth + j * 3] = heightmap[*index];
			}

			buffer[i * *bitWidth + j * 3 + 1] = heightmap[*index];
			buffer[i * *bitWidth + j * 3 + 2] = heightmap[*index];
			

			
			*index += 1;	
		}

	}

	free(index);
	
	// free header info
	free(bits);
	free(bitWidth);
	free(imgSize);
	free(iHeaderSize);
	free(offBits);
	free(fileSize);
	free(numPlanes);

	// write to file
	FILE *fout = fopen("test.bmp", "wb");
	fwrite(header, 1, 54, fout);
	fwrite((char*)buffer, 1, *imgSize, fout);
	fclose(fout);
	free(buffer);

}

// this is temporary
void printHeightmap(int* heightmap, int* len, int* hgt) {
	
	int* currentIndex = malloc(sizeof(int));
	*currentIndex = 0;
	for (int i = 0; i < *hgt; i++) {
		for (int j = 0; j < *len; j++) {
			printf("%02x ", heightmap[*currentIndex]);
			*currentIndex += 1;
		}
		printf("\n");
	}	

	free(currentIndex);
}
