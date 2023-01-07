//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
int sortObj(Voiture* array, int len) {
    Voiture copie_array[21];
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
}

//à améliorer plus tard