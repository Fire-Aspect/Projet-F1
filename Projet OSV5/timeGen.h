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

    //Boucle de génération aléatoire de 3 temps (1 par secteur)
    for (int i = 0; i < 3; i++) {
        temps[i] = ((float) rand() / RAND_MAX) * 20.0f + 25.0f;
    }

    return (0);
}

