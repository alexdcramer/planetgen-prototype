#include "heightmap.h"

int main() {
	int* len = malloc(sizeof(int));
	int* hgt = malloc(sizeof(int));
	*len = 20;
	*hgt = 10;
	int* heightmap = genHeightmap(len, hgt);
	printHeightmap(heightmap, len, hgt);
	
	free(len);
	free(hgt);
	free(heightmap);
	return 0;
}
