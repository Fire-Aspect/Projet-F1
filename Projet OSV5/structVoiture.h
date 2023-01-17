//Mis à jour le 14/01/2023

#ifndef PROJET_FORMULE_1_STRUCTVOITURE_H
#define PROJET_FORMULE_1_STRUCTVOITURE_H

//Différents includes
#include <stdlib.h>
#include <stdbool.h>

//Création de la structure Voiture
typedef struct {
    int vId;
    float s1;
    float s2;
    float s3;
    float total;
    float tTour[2]; // Tour en minute et en secondes
    float bestToursPerso; // Meilleur tour d'une voiture
    float tempsDeriere1er; // Temps derrière la première voiture ==> Pour les dépassements
    int pidFils;
    int idBest[3];
    int status; // STAND, OUT, EN COURSE
    int eliminated; // éliminé de la course

} Voiture;


#endif //PROJET_FORMULE_1_STRUCTVOITURE_H
