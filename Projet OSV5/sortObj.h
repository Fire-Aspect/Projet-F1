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

            /*memcpy(array_lect, lectureFichier(5), 20 * sizeof(int*));

            int n, m;
            Voiture tempQ2[16];               // Structure Voiture temporaire pour faire le tri

            float tempsLostQ2 = 994;

            //fonction tri de la structure
            for (n = 0; n < len - 1; n++) {
                for (m = n + 1; n < len; m++) {

                    if (copie_array[m].eliminated == 1){

                        copie_array[m].total = tempsLostQ2;
                        tempsLostQ2 = tempsLostQ2 + 1;

                    }
                    if (copie_array[n].total > copie_array[m].total) {
                        tempQ2[15] = copie_array[n];
                        copie_array[n] = copie_array[m];
                        copie_array[m] = tempQ2[15];
                    }
                }
            }
            return copie_array;*/


            break;
        case '6':
            printf("%s","Q3\n");
            /*
            memcpy(copie_array, array, len * sizeof(Voiture));
            int s, t;
            Voiture tempQ3[16];               // Structure Voiture temporaire pour faire le tri

            float tempsLostQ3 = 990;

            //fonction tri de la structure
            for (n = 0; n < len - 1; n++) {
                for (m = n + 1; n < len; m++) {

                    if (copie_array[m].eliminated == 1){

                        copie_array[m].total = tempsLostQ3;
                        tempsLostQ3 = tempsLostQ3 + 1;

                    }
                    if (copie_array[n].total > copie_array[m].total) {
                        tempQ2[15] = copie_array[n];
                        copie_array[n] = copie_array[m];
                        copie_array[m] = tempQ2[15];
                    }
                }
            }
            return copie_array;
            */
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