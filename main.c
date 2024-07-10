#include "heightmap.h"
#include "temperature.h"
#include <string.h>

int main(int argc, char* argv[]) {
	int* len = malloc(sizeof(int));
	int* hgt = malloc(sizeof(int));
	int* tilt = malloc(sizeof(int));
	*len = 20;
	*hgt = 10;
	*tilt = 23;
	
	if (argc > 1) {
		for (int i = 0; i < argc - 1; i++) {
			if (strcmp(argv[i], "--len") == 0) {
				*len = atoi(argv[i + 1]);
				*hgt = *len / 2;
			} else if (strcmp(argv[i], "--tilt") == 0) {
				*tilt = atoi(argv[i + 1]);
			}
		}
	}
	
	int* heightmap = genHeightmap(len, hgt);
	printHeightmap(heightmap, len, hgt);
	



	int* tempmap = genTempmap(heightmap, len, hgt, tilt);
	
	printf("Temperature:\n");
	printHeightmap(tempmap, len, hgt);

	free(len);
	free(hgt);
	free(heightmap);
	free(tempmap);
	return 0;
}
