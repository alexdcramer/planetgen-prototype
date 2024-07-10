#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
