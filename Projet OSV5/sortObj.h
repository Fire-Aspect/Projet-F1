//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"
#include "showOutput.h"

//Fonction sortObj (param : structure Voiture et Longueur)
//But : trier les temps de tours dans différents secteurs d'une voiture
void sortObj(Voiture v[], int len) {
    int i, j;
    Voiture temp;
    //tri de la structure
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (v[i].total > v[j].total) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    //showOutput(v, len);
}

//à améliorer plus tard