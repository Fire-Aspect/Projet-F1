//
// Created by antoi on 12/10/2022.
//

#include "faireTourner.h"
#include "showOutput.h"
#include "timeGen.h"
#include "tri.h"
#include <stdio.h>
#include <stdlib.h>

void faireTourner(int nbrVoiture, int nbrtour) {

    int numeroVoiture[10]= {44, 63, 1, 11, 55, 16, 4, 3, 14, 31};
    int BS1[3]= {0,0,0};
    int BS2[3]= {0,0,0};
    int BS3[3]= {0,0,0};
    int BT[3]= {0,0,0};

    Voiture v[nbrVoiture];
    int temps[5] = {};
    size_t length = sizeof(v)/sizeof(v[0]);

    for (int n = 1; n <= nbrtour; n++ ) {

        for (int k = 0; k < length; k++) {
            timeGenerator(temps);
            for (int i = 0; i < 6; i++) {
                switch (i) {
                    case 0:
                        v[k].s1 = temps[0];
                        break;
                    case 1:
                        v[k].s2 = temps[1];
                        break;
                    case 2:
                        v[k].s3 = temps[2];
                        break;
                    case 3:
                        v[k].tTour[0] = temps[3];
                        break;
                    case 4:
                        v[k].tTour[1] = temps[4];
                        break;
                    case 5:
                        v[k].vId = numeroVoiture[k];
                        break;
                }
            }
        }
        //tri(v,length);

        showOutput(v, length);

    }
}
