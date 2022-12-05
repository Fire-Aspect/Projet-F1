#include<stdio.h>
#include <unistd.h>
#include "structVoiture.h"
#include "timeGen.h"

int vieVoiture(Voiture caseV, int numCase, int pid, int tempsSess) {

    int numeroVoiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};
    float temps[5] = {};
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    printf("%d",secondeDepart);

    do {
        timeGenerator(temps);
        for (int i = 0; i <= 8; i++) {
            switch (i) {
                case 0:
                    caseV.s1 = temps[0];
                    break;
                case 1:
                    caseV.s2 = temps[1];
                    break;
                case 2:
                    caseV.s3 = temps[2];
                    break;
                case 3:
                    caseV.tTour[0] = temps[3];
                    break;
                case 4:
                    caseV.tTour[1] = temps[4];
                    break;
                case 5:
                    caseV.vId = numeroVoiture[numCase];
                    break;
                case 6:
                    caseV.total = temps[0] + temps[1] + temps[2];
                    break;
                case 7 :
                    caseV.pidFils = pid;
                    break;

            }
        }
        //for (int j = 0; j <= 4; j++){
//
//       }
    } while (secondePendant <= secondeDepart + tempsSess);

    exit(0);
}
