//Mis à jour le 14/01/2023

//Différents includes
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


//Fonction timeGenerator (param : temps ==> temps du générateur)
//But : Générer un temps entre 25 et 45 secondes

int timeGenerator(float temps[]) {

    //Introduction de variables
    float nbrRand;
    const int n = 3;

    //Boucle de génération aléatoire de 3 temps
    for (int i = 0; i < n; i++) {
        nbrRand = ((float) rand() / RAND_MAX) * (float) (45.0 - 25.0 + 1.0) + 25.0;
        temps[i] = nbrRand;
    }

    return (0);
}

