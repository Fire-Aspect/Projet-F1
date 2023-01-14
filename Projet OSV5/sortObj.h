//Mis à jour le 14/01/2023

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "extraFunctions.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
Voiture *sortObj(Voiture *array, int len, char session) {

    int position[20];

    static Voiture copie_array[21];
    memcpy(copie_array, array, len * sizeof(Voiture));
    static int array_lect[20][2];
    int k, r, l, g, n = 0;
    Voiture voitTemp;
    switch (session) {
        case '1':
        case '2':
        case '3':
        case '4':
            //Sessions P1 P2 P3 Q1
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = k + 1; r < len; r++) {
                    if (copie_array[k].total > copie_array[r].total) {
                        voitTemp = copie_array[k];
                        copie_array[k] = copie_array[r];
                        copie_array[r] = voitTemp;
                    }
                }
            }
            return copie_array;
            break;
        case '5':
            //Session Q2
            //copie mémoire partagée du tableau du classement lu en fichier
            memcpy(array_lect, lectureFichier(session), 20 * 2 * sizeof(int));
            int voitElimQ1[5][2];
            memset(voitElimQ1, 0, sizeof(voitElimQ1));
            int tempsLostQ2 = 994;

            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 994
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.

            for (int z = 15; z < 20; z++) {

                if (array_lect[z][1] == 1) {

                    voitElimQ1[n][0] = array_lect[z][0];
                    voitElimQ1[n][1] = tempsLostQ2;
                    n = n + 1;
                    tempsLostQ2 = tempsLostQ2 + 1;
                }
            }
            for (g = 0; g < len - 1; g++) {
                for (l = 0; l < 5; l++) {
                    if (copie_array[g].vId == voitElimQ1[l][0]) {
                        copie_array[g].total = (float) voitElimQ1[l][1];
                        copie_array[g].s1 = 0;
                        copie_array[g].s2 = 0;
                        copie_array[g].s3 = 0;
                        copie_array[g].eliminated = 1;
                        break;
                    }
                }
            }
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len - k - 1; r++) {
                    if (copie_array[r].total > copie_array[r + 1].total) {
                        voitTemp = copie_array[r];
                        copie_array[r] = copie_array[r + 1];
                        copie_array[r + 1] = voitTemp;
                    }
                }
            }

            return copie_array;
            break;

        case '6':
            //Session Q3
            //copie mémoire partagée du tableau du classement lu en fichier
            memcpy(array_lect, lectureFichier(session), 20 * 2 * sizeof(int));
            int voitElimQ2[10][2];
            memset(voitElimQ2, 0, sizeof(voitElimQ2));
            int tempsLostQ3 = 989;

            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 989
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.

            for (int z = 10; z < 20; z++) {

                if (array_lect[z][1] == 1) {

                    voitElimQ2[n][0] = array_lect[z][0];
                    voitElimQ2[n][1] = tempsLostQ3;
                    n = n + 1;
                    tempsLostQ3 = tempsLostQ3 + 1;
                }
            }
            for (g = 0; g < len - 1; g++) {
                for (l = 0; l < 10; l++) {
                    if (copie_array[g].vId == voitElimQ2[l][0]) {
                        copie_array[g].total = (float) voitElimQ2[l][1];
                        copie_array[g].s1 = 0;
                        copie_array[g].s2 = 0;
                        copie_array[g].s3 = 0;
                        copie_array[g].eliminated = 1;
                        break;
                    }
                }
            }
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len - k - 1; r++) {
                    if (copie_array[r].total > copie_array[r + 1].total) {
                        voitTemp = copie_array[r];
                        copie_array[r] = copie_array[r + 1];
                        copie_array[r + 1] = voitTemp;
                    }
                }
            }

            return copie_array;
            break;
        case '7':
            printf("%s", "Course en travaux\n");
            exit(0);
        case '8':
            printf("%s", "Course Sprint en travaux\n");
            exit(0);
        default:
            printf("%s", "Session inconnue\n");

    }
}
