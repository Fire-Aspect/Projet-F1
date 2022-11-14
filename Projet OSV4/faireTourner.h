#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timeGen.h"
#include "structVoiture.h"
#include "sortObj.h"


void faireTourner(int nbrVoiture, int nbrtour) {

    int numeroVoiture[20]= {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9};

    
    Voiture v[nbrVoiture];
    
    int shmid;

    Voiture *circuit;
    
    shmid = shmget(69, 20*sizeof(Voiture), IPC_CREAT | 0666);
    
    printf("%d \n", shmid);
    
    circuit = shmat(69, 0, 0);
    
    float temps[5] = {};
    size_t length = sizeof(v)/sizeof(v[0]);

    for (int n = 1; n <= nbrtour; n++ ) {

        for (int k = 0; k < length; k++) {
            timeGenerator(temps);
            for (int i = 0; i <= 7; i++) {
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
                    case 6:
                    	v[k].total = temps[0] + temps[1] + temps[2];
                    	break;

                }
            }
        }

        //showOutput(v, length);
        sortObj(v, length);
        showOutput(v, length);
    }
}


