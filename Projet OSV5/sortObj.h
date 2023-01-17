//Mis à jour le 14/01/2023

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "extraFunctions.h"

//Fonction sortObj
//But : trier les temps de tours dans différents secteurs d'une voiture
Voiture *sortObj(Voiture *array, int len, char session, int *nbrTourFait,bool depart) {

    int position[20];
    static Voiture copie_array[21];
    memcpy(copie_array, array, len * sizeof(Voiture));
    static int array_lect[20][2];
    int k, r, l, g, n = 0;
    Voiture voitTemp;
    float temps1erPlace;
    switch (session) {
        case '1':
        case '2':
        case '3':
            //Sessions P1 P2 P3
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len-k-1; r++) {
                    if (copie_array[r].total > copie_array[r +1].total) {
                        voitTemp = copie_array[r];
                        copie_array[r] = copie_array[r+1];
                        copie_array[r+1] = voitTemp;
                    }
                }
            }
            return copie_array;
            break;
        case '4':
            //Sessions Q1
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len-k-2; r++) {
                    if (copie_array[r].bestToursPerso > copie_array[r +1].bestToursPerso) {
                        voitTemp = copie_array[r];
                        copie_array[r] = copie_array[r+1];
                        copie_array[r+1] = voitTemp;
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

            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 994
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.
            int tempsLostQ2 = 994;
            for (int z = 15; z < 20; z++) {

                if (array_lect[z][1] == 1) {

                    voitElimQ1[n][0] = array_lect[z][0];
                    voitElimQ1[n][1] = tempsLostQ2;
                    n = n + 1;
                    tempsLostQ2 = tempsLostQ2 + 1;
                }
            }
            //mise à zéro de tous les champs du tableau pour signifier l'élimination
            for (g = 0; g < len - 1; g++) {
                for (l = 0; l < 5; l++) {
                    if (copie_array[g].vId == voitElimQ1[l][0]) {
                        copie_array[g].bestToursPerso = (float) voitElimQ1[l][1];
                        copie_array[g].s1 = 0;
                        copie_array[g].s2 = 0;
                        copie_array[g].s3 = 0;
                        copie_array[g].tTour[0] = 0;
                        copie_array[g].tTour[1] = 0;
                        copie_array[g].eliminated = 1;
                        break;
                    }
                }
            }
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len - k - 2; r++) {
                    if (copie_array[r].bestToursPerso > copie_array[r + 1].bestToursPerso) {
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


            //fonction tri de la structure
            //si la voiture est éliminée, son temps est augmenté de 989
            //puis ce temps est incrémenté de 1 pour les voitures éliminées suivantes.
            int tempsLostQ3 = 989;
            for (int z = 10; z < 20; z++) {

                if (array_lect[z][1] == 1) {

                    voitElimQ2[n][0] = array_lect[z][0];
                    voitElimQ2[n][1] = tempsLostQ3;
                    n = n + 1;
                    tempsLostQ3 = tempsLostQ3 + 1;
                }
            }
            //mise à zéro de tous les champs du tableau pour signifier l'élimination
            for (g = 0; g < len - 1; g++) {
                for (l = 0; l < 10; l++) {
                    if (copie_array[g].vId == voitElimQ2[l][0]) {
                        copie_array[g].bestToursPerso = (float) voitElimQ2[l][1];
                        copie_array[g].s1 = 0;
                        copie_array[g].s2 = 0;
                        copie_array[g].s3 = 0;
                        copie_array[g].tTour[0] = 0;
                        copie_array[g].tTour[1] = 0;
                        copie_array[g].eliminated = 1;
                        break;
                    }
                }
            }
            //fonction tri de la structure
            for (k = 0; k < len - 1; k++) {
                for (r = 0; r < len - k - 2; r++) {
                    if (copie_array[r].bestToursPerso > copie_array[r + 1].bestToursPerso) {
                        voitTemp = copie_array[r];
                        copie_array[r] = copie_array[r + 1];
                        copie_array[r + 1] = voitTemp;
                    }
                }
            }

            return copie_array;
            break;
        case '7':
            //Session Course
            memcpy(array_lect, lectureFichier(session), 20 * 2 * sizeof(int));
            if (depart){
                for (int z = 0; z < 20; z++) {
                    for (int b = 0; b < 20; b++) {
                        if (copie_array[z].vId == array_lect[b][0]) {
                            position[b] = copie_array[z].vId;
                            array[z].tempsDeriere1er = (float)b;
                            copie_array[z].tempsDeriere1er = (float)b;
                            copie_array[z].s1 = 0;
                            copie_array[z].s2 = 0;
                            copie_array[z].s3 = 0;
                            copie_array[z].tTour[0] = 0;
                            copie_array[z].tTour[1] = 0;
                            copie_array[z].eliminated = 0;
                            copie_array[z].bestToursPerso = 0;
                            copie_array[z].status = 0;
                            copie_array[z].total = b;
                            //nbrTourFait[z] = 0;
                            break;
                        }
                    }
                }

                for (k = 0; k < len - 1; k++) {
                    for (r = 0; r < len-k-1; r++) {
                        if (copie_array[r].total > copie_array[r +1].total) {
                            voitTemp = copie_array[r];
                            copie_array[r] = copie_array[r+1];
                            copie_array[r+1] = voitTemp;
                        }
                    }
                }
                return copie_array;
            }
            else {
                //Temps de la première place
                for (int z = 0; z < 20; z++) {
                    if (copie_array[z].vId == position[0]) {
                       temps1erPlace = copie_array[z].total;
                    }
                }
                for (int z = 0; z < 20; z++){
                    array[z].tempsDeriere1er = copie_array[z].total + array[z].tempsDeriere1er - temps1erPlace;
                }
                qsort(copie_array, 20, sizeof(Voiture), comparer);
                for (int z = 0; z < 20; z++) {
                    position[z] = copie_array[z].vId;
                }
                /*for (k = 0; k < len - 1; k++) {
                    for (r = 0; r < len - k - 1; r++) {
                        if ((copie_array[r].total + copie_array[r].tempsDeriere1er) >
                            (copie_array[r + 1].total + copie_array[r + 1].tempsDeriere1er)) {
                            voitTemp = copie_array[r];
                            copie_array[r] = copie_array[r + 1];
                            copie_array[r + 1] = voitTemp;
                        }
                    }
                }*/
            }
            return copie_array;
            break;
        case '8':
            return copie_array;
            break;
        default:
            printf("%s", "Session inconnue\n");

    }
}
