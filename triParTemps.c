
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int vId;
    int s1;
    int s2;
    int s3;
    int tTour[2];
}Voiture;


void triParTemps(Voiture v[], int size_t) {
    int i,j;
    Voiture temp;
    //tri de la structure
    for (i = 0; i < size_t - 1; i++) {
        for (j = i + 1; j < size_t; j++) {
            if (v[i].tTour > v[j].tTour) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

