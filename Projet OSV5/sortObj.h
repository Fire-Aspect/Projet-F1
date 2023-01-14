//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "extraFunctions.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
Voiture *sortObj(Voiture* array, int len, char session) {

    int position[20];
    static Voiture copie_array[21];
    memcpy(copie_array, array, len * sizeof(Voiture));
    static int array_lect[20][2];
    int k, r, l;
    Voiture voitTemp;
    switch (session) {
        case '1':
        case '2':
        case '3':
        case '4':
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

            //copie mémoire partagée du tableau du classement lu en fichier
            memcpy(array_lect, lectureFichier(5), 20 * 2 * sizeof(int));
            int voitElim[5][2];
            memset(voitElim, 0, sizeof(voitElim));
            int n = 0;
            int tempsLostQ2 = 994;

            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 994
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.

            for(int z = 15; z < 20; z++) {

                if (array_lect[z][1] == 1) {

                    voitElim[n][0] = array_lect[z][0];
                    voitElim[n][1] = tempsLostQ2;
                    n = n + 1;
                    tempsLostQ2 = tempsLostQ2 + 1;
                }
            }

            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (l = 0; l < 5; l++) {
                    if (copie_array[k].vId == voitElim[l][0]) {
                        copie_array[k].total = (float) voitElim[l][1];
                        copie_array[k].s1 = 0;
                        copie_array[k].s2 = 0;
                        copie_array[k].s3 = 0;
                        copie_array[k].eliminated = 1;
                        break;
                    }
                }
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
        case '6':
            printf("%s","Q3\n");
            /*
            int **copiePourFree = lectureFichier(5);

            //copie mémoire partagée du tableau du classement lu en fichier
            memcpy(array_lect, copiePourFree, 20 * sizeof(int *));
            int voitElim[10][2];
            int p = 0;
            int tempsLostQ2 = 994;

            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 994
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.

            for(int y = 10; y < 20; y++) {

                if (array_lect[y][1] == 1) {

                    voitElim[p][0] = array_lect[y][0];
                    voitElim[p][1] = tempsLostQ2;
                    p = p + 1;
                    tempsLostQ2 = tempsLostQ2 + 1;
                }
            }

            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (l = 0; l < 5; l++) {
                    if (copie_array[k].vId == voitElim[l][0]) {
                        copie_array[k].total = voitElim[l][1];
                        copie_array[k].s1 = 0;
                        copie_array[k].s2 = 0;
                        copie_array[k].s3 = 0;
                        copie_array[k].status = 2;
                        break;
                    }
                }
                for (r = k + 1; r < len; r++) {
                    if (copie_array[k].total > copie_array[r].total) {
                        voitTemp = copie_array[k];
                        copie_array[k] = copie_array[r];
                        copie_array[r] = voitTemp;
                    }
                }
            }

            return copie_array;
            for (int i = 0; i < 20; i++) {
                free(copiePourFree[i]);
            }
            free(copiePourFree);
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