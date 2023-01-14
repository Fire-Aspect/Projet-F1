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
    float somme;
    float minut;
    float sec;

    float rest = 0;
    float temp = 0;

    //Boucle de génération aléatoire de 3 temps
    for (int i = 0; i < n; i++) {
        nbrRand = ((float) rand() / RAND_MAX) * (float) (45.0 - 25.0 + 1.0) + 25.0;
        temps[i] = nbrRand;
    }
    somme = temps[0] + temps[1] + temps[2];

    temp = somme;

    //Boucle de conversion de la somme des temps (secondes) en un temps en minutes et secondes
    for (int j = 0; temp > 60; j++) {
        if (temp > 60) {
            temp = temp - 60;
            rest = rest + 1;
        }
    }
    minut = rest;
    sec = temp;
    temps[3] = minut;
    temps[4] = sec;

    return (0);
}

