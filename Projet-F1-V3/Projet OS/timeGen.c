//
// Created by antoi on 27/09/2022.
//

#include "timeGen.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int timeGenerator(float temps[]) {
    float nbrRand = 0;
    const int n = 3;
    float somme = 0;
    float minut = 0;
    float sec = 0;
    
    float rest = 0;
    float temp = 0;
    int j = 0; 

    for (int i = 0; i < n; i++) {
        nbrRand = ((float)rand()/RAND_MAX)*(float)(45.0-25.0+1.0)+25.0;    
        temps[i] = nbrRand;
    }
    somme = temps[0]+temps[1]+temps[2];
    
    temp = somme;
    
    for (int j = 0; temp > 60; j++) {
   	 if (temp > 60) {
    		temp = temp-60;
    		rest = rest + 1;
    	}
    }
    minut = rest;
    sec = temp;
    temps[3] = minut;
    temps[4] = sec;

    return (0);
}