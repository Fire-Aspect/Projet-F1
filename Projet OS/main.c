#include <stdio.h>
#include <stdlib.h>
#include "sortArray.h"
#include "timeGen.h"

typedef struct {
    int vId;
    int s1;
    int s2;
    int s3;
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

    int numeroVoiture[10]= {44, 63, 1, 11, 55, 16, 4, 3, 14, 31};
    int BS1[3]= {0,0,0};
    int BS2[3]= {0,0,0};
    int BS3[3]= {0,0,0};
    int BT[3]= {0,0,0};

    Voiture v[1];
    v[0].vId = 69;
    int temps[4] = {};

    timeGenerator(temps);
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                v[0].s1 = temps[0];
                break;
            case 1:
                v[0].s2 = temps[1];
                break;
            case 2:
                v[0].s3 = temps[2];
                break;
            case 3:
                v[0].tTour[0] = temps[3];
                break;
            case 4:
                v[0].tTour[1] = temps[4];
                break;
        }
    }
    printf("%d\n", v[0].s1);
    printf("%d\n", v[0].s2);
    printf("%d\n", v[0].s3);
    printf("%d\n", v[0].tTour[0]);
    printf("%d\n", v[0].tTour[1]);

    return 0;
}
