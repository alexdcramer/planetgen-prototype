#include <math.h>
#include <stdio.h>

int* getDegreeFromLatitude(int* hgt, int* val) {
	int* degree = malloc(sizeof(int));
	double* pixelsPerDegree = malloc(sizeof(double));
	*pixelsPerDegree = (double)(*hgt)/180.0;
	*degree = 90 - (int)floor((*val + 0.5)  / *pixelsPerDegree);
	
	free(pixelsPerDegree);
	
	return degree;
}
int* genLatitudeTemp(int* heightmap, int* len, int* hgt, int* tilt) {
	// the north pole is ~263.15K in the summer (0x58)
	// the amazon gets to ~313.15K in the summer (0x68)
	// the sahara gets to ~323.15K in the summer (0x6C)
	//
	// neither of these temperatures appear to be impacted by any sort of non-latitudinal temperature fluxuation
	
	// thus, where x is an integer between -90 and 90 representing latitude, θ is the tilt in degrees, and y is the temperature, the formula is:
	// y == -(2/3)|x+θ|+323.15
	// i suspect warm and cool currents are responsible for these temperatures being a bit warmer than i expected in temperate areas
	// especially because it lines up suspiciously well with inland eastern hemisphere temperatures	

	// something i will need to look into is what causes the slope and max temps, right now they're set at constants for earth-like atmospheres,
	// but those constants shouldn't always be the case...
	int* tempmap = malloc(sizeof(int) * *len * *hgt);
	
	int* index = malloc(sizeof(int));
	*index = 0;
	for (int i = 0; i < *hgt; i++) {
		// temperature is the same for each latitude, so longitude is only needed for setting the values	
		int* latitudePixel = malloc(sizeof(int));
		*latitudePixel = i;
		int* degree = getDegreeFromLatitude(hgt, latitudePixel);
		
		double* summerAvg = malloc(sizeof(double));
		double* winterAvg = malloc(sizeof(double));
		
		*summerAvg = ((-2  * abs(*degree - *tilt)) / 3) + 323.15;
		*winterAvg = ((-2  * abs(*degree + *tilt)) / 3) + 323.15;	
		
		int* avg = malloc(sizeof(int));
		*avg = (floor((*summerAvg + *winterAvg) / 2) / 3);
		
		for (int j = 0; j < *len; j++) {
			tempmap[*index] = *avg;			
			*index += 1;
		}
		free(latitudePixel);
		free(degree);
		free(summerAvg);
		free(winterAvg);
		free(avg);
	}

	free(index);
	return tempmap;
}
int* genTempmap(int* heightmap, int* len, int* hgt, int* tilt) {
	// this is supposed to generate temperature differentials based on various factors, than graph them all together
	// for now, only latitude is being taken into account, so it'll just return that
	
	// measuring in kelvin will be ideal, going from 0K to 765K in increments of 3K should help with modeling a decently large range of temperatures
	// I'm trying to keep these as 8 bit numbers so that they can fit easily into a png, however I think later on this should be changed as to allow
	// greater precision. Perhaps designing a file format for made planets would be ideal? 
	
	// Also in the future, atmospheric composition needs to be taken into account, alongside distance to/from the sun
	// Right now we can assume an earthern atmosphere 1 AU from a Sol-like star
	
	// One more thing, to get this to work with Köppen, summer and winter averages will need to be calculated
	// I think this can be handled via tilt, and all I'll need to do is generate two maps with ±θ
	// Using absolute values, this also accounts for temperature differences near the equator being near 0 :D
	// the tilt just so happens to align great with the tropics of capricorn and cancer, so it ~should~ accurately model tropical areas :D

	int* tempmap = genLatitudeTemp(heightmap, len, hgt, tilt);
	return tempmap;
}
