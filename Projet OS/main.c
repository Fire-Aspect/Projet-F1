#include <stdio.h>
#include <stdlib.h>
#include "sortArray.h"
#include "timeGen.h"

typedef struct Voiture{
    int vId;
    int tps[3];
    int tTour[2];
}Voiture;

int main() {
    //Initialiser l'array
    /*
    int result, arr[] = {5, 2, 8, 7, 1, 34, 2};
    int longueur = sizeof(arr)/sizeof(arr[0]);

    result = sortArray(arr, longueur);
     */
    // printf("%d ", result);
    Voiture v1;
    v1.vId = 01;
    int temps[4] = {};

    timeGenerator(temps);
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                v1.tps[0] = temps[0];
                break;
            case 1:
                v1.tps[1] = temps[1];
                break;
            case 2:
                v1.tps[2] = temps[2];
                break;
            case 3:
                v1.tTour[0] = temps[3];
                break;
            case 4:
                v1.tTour[1] = temps[4];
                break;
        }
    }
    printf("%d\n", v1.tps[0]);
    printf("%d\n", v1.tps[1]);
    printf("%d\n", v1.tps[2]);
    printf("%d\n", v1.tTour[0]);
    printf("%d\n", v1.tTour[1]);

    return 0;
}
