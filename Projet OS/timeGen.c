//
// Created by antoi on 27/09/2022.
//

#include "timeGen.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int timeGenerator(int temps[]) {
    int nbrRand = 0;
    const int n = 3;
    int somme = 0;
    int minut = 0;
    int sec = 0;

    srand(time(0));

    for (int i = 0; i < n; i++) {
        nbrRand = rand()%(45-25+1)+25;
        temps[i] = nbrRand;
    }
    somme = temps[0]+temps[1]+temps[2];
    minut = floor(somme/60);
    sec = somme % 60;
    temps[3] = minut;
    temps[4] = sec;

    return (0);
}