//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "extraFunctions.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
Voiture *sortObj(Voiture* array, int len, char session) {
    static Voiture copie_array[21];
    static int array_lect[20][2];
    switch (session) {
        case '1':
        case '2':
        case '3':
        case '4':
            memcpy(copie_array, array, len * sizeof(Voiture));
            int k, r;
            Voiture tempQ1[21];               // Structure Voiture temporaire pour faire le tri

            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = k + 1; r < len; r++) {
                    if (copie_array[k].total > copie_array[r].total) {
                        tempQ1[20] = copie_array[k];
                        copie_array[k] = copie_array[r];
                        copie_array[r] = tempQ1[20];
                    }
                }
            }
            return copie_array;
            break;
        case '5':
            printf("%s","Q2\n");
            break;
        case '6':
            printf("%s","Q3\n");
            break;
        case '7':
            printf("%s","Course\n");
            break;
        case '8':
            printf("%s","Course Sprint\n");
            break;
        default:
            printf("%s", "stop it get some help - Michael Jordan");

    }
}

//à améliorer plus tard