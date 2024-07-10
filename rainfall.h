// currently just gives flat rainfall for all areas, needed for köppen calculation

int* genRainfallmap(int* len, int* hgt, int* heightmap, int* tempmap) {
	
	int* rainfallMap = malloc(sizeof(int) * *len * *hgt);
	int* index = malloc(sizeof(int));
	*index = 0;
	for (int i = 0; i < *hgt; i++) {
		for (int j = 0; j < *len; j++) {
			rainfallMap[*index] = 128;
			*index += 1;
		}
	}
	free(index);
	return rainfallMap;
}
