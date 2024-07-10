#include "heightmap.h"
#include "temperature.h"

int main() {
	int* len = malloc(sizeof(int));
	int* hgt = malloc(sizeof(int));
	int* tilt = malloc(sizeof(int));
	*len = 22;
	*hgt = 11;
	*tilt = 23;
	int* heightmap = genHeightmap(len, hgt);
	printHeightmap(heightmap, len, hgt);
	


	int* tempmap = genTempmap(heightmap, len, hgt, tilt);
	
	printf("Temperature:\n");
	printHeightmap(tempmap, len, hgt);

	free(len);
	free(hgt);
	free(heightmap);
	return 0;
}
