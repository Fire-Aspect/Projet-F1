//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
Voiture *sortObj(Voiture* array, int len, char session) {
    static Voiture copie_array[21];
    switch (session) {
        case '1':
        case '2':
        case '3':
            memcpy(copie_array, array, len * sizeof(Voiture));
            int i, j;
            Voiture temp[21];               // Structure Voiture temporaire pour faire le tri

            //fonction tri de la structure
            for (i = 0; i < len - 1; i++) {
                for (j = i + 1; j < len; j++) {
                    if (copie_array[i].total > copie_array[j].total) {
                        temp[20] = copie_array[i];
                        copie_array[i] = copie_array[j];
                        copie_array[j] = temp[20];
                    }
                }
            }
            return copie_array;
            break;
        case '4':
            memcpy(copie_array, array, len * sizeof(Voiture));
            int k, r;
            Voiture tempQ1[21];               // Structure Voiture temporaire pour faire le tri

            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = k + 1; r < len; r++) {
                    if (copie_array[k].total > copie_array[r].total) {
                        temp[20] = copie_array[k];
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


   /* static Voiture copie_array[21];
    memcpy(copie_array, array, len * sizeof(Voiture));

    int i, j;
    Voiture temp[21];               // Structure Voiture temporaire pour faire le tri

    //fonction tri de la structure
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (copie_array[i].total > copie_array[j].total) {
                temp[20] = copie_array[i];
                copie_array[i] = copie_array[j];
                copie_array[j] = temp[20];
            }
        }
    }
    return copie_array;
    */
}

//à améliorer plus tard