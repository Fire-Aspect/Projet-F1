//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"

//Fonction sortObj (param : pointeur vers un tableau et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
int sortObj(Voiture* array, int len) {
    //Voiture *copie_array = malloc(len * sizeof(Voiture));
    //Voiture copie_array[21];
    //memcpy(copie_array, array, len * s<izeof(Voiture));
    //int *voit = malloc(sizeof (Voiture));
    //int *classementTrier = malloc(len * sizeof(Voiture));

    int i, j;
    Voiture *classementTrier = array;    // Copie de l'array circuit
    Voiture temp[21];               // Structure Voiture temporaire pour faire le tri

    //fonction tri de la structure
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (classementTrier[i].total > classementTrier[j].total) {
                temp[20] = classementTrier[i];
                classementTrier[i] = classementTrier[j];
                classementTrier[j] = temp[20];
            }
        }
    }
}

//à améliorer plus tard