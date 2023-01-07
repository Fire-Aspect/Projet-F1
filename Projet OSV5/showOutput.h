//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"
#include "sortObj.h"

#define COLOR_CYAN  "\033[0;36m"
#define COLOR_CYAN_OFF   "\033[0m"

//Fonction showOutput (param : structure voiture et longueur de voiture)
//But : Afficher un tableau avec les temps d'une voiture dans différents secteurs de piste

void showOutput(Voiture* array, int len) {
    fflush(stdout);
    int kTemp;

    //Fonction de tri
    Voiture classement[21];
    memcpy(classement, array, len * sizeof(Voiture));

    char *rowC[] = {"Numéro", "Secteur 1", "Secteur 2", "Secteur 3", "Temps par tour", "Différence de temps"};

    printf("%s", "+========+==============+==============+==============+=================+=====================+\n");
    printf("|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\n",
           -6, rowC[0], -12, rowC[1], -12, rowC[2], -12, rowC[3], -15, rowC[4], -18, rowC[5]);
    printf("+%*s+%*s+%*s+%*s+%*s+%*s+\n", -3, "--------", 12, "--------------", 12, "--------------", 12, "--------------",
           -15, "-----------------", 18, "---------------------");

    for (int i = 0; i < len-1; ++i) {
        
        for (int k = 0; k < 20; k++) {
            if (classement[20].s1 > classement[k].s1) {
                classement[20].s1 = classement[k].s1;
                classement[20].idBest[0] = classement[k].vId;
            }
            if (classement[20].s2 > classement[k].s2) {
                classement[20].s2 = classement[k].s2;
                classement[20].idBest[1] = classement[k].vId;
            }
            if (classement[20].s3 > classement[k].s3) {
                classement[20].s3 = classement[k].s3;
                classement[20].idBest[2] = classement[k].vId;
            }
        }
        if(i == 0){
            printf("| %-6d | %-12.3f | %-12.3f | %-12.3f | %.0f%s%-13.3f |                     |\n", classement[i].vId,
                   classement[i].s1, classement[i].s2, classement[i].s3, classement[i].tTour[0], ".",
                   classement[i].tTour[1]);
        }
        else{
            kTemp = i-1;
            printf("| %-6d | %-12.3f | %-12.3f | %-12.3f | %.0f%s%-13.3f | +%-18.3f | \n", classement[i].vId,
                   classement[i].s1, classement[i].s2, classement[i].s3, classement[i].tTour[0], ".",
                   classement[i].tTour[1], fabsf(classement[i].total - classement[kTemp].total));
        }
    }

        printf("%s", "+========+==============+==============+==============+=================+=====================+\n");


            printf("| %-s%-6s%s | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m |\n", "\033[1;31m", "Best", "\033[0m", classement[20].idBest[0], classement[20].idBest[1], classement[20].idBest[2]);
            printf("| %-6s | %-12.3f | %-12.3f | %-12.3f |\n", " ", classement[20].s1, classement[20].s2, classement[20].s3);
            printf("%s", "+=====================================================+\n");



}