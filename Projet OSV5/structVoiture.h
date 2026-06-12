//Mis à jour le 14/01/2023

#ifndef PROJET_FORMULE_1_STRUCTVOITURE_H
#define PROJET_FORMULE_1_STRUCTVOITURE_H

//Différents includes
#include <stdlib.h>
#include <stdbool.h>

//Création de la structure Voiture
typedef struct {
    int vId;
    float s1;       // best S1 of the session
    float s2;       // best S2 of the session
    float s3;       // best S3 of the session
    float total;    // best lap total (used for ranking)
    float tTour[2]; // best lap time as [minutes, seconds]
    float curS1;    // current lap S1
    float curS2;    // current lap S2
    float curS3;    // current lap S3
    float cumul;    // course : temps cumulé depuis le départ
    int laps;       // course : tours bouclés
    int idBestLap;  // (case 20) voiture détenant le meilleur tour
    int pidFils;
    int idBest[3];
    int status; // 0=EN COURSE, 1=STAND, 2=OUT
    int eliminated; // éliminé de la course

} Voiture;


#endif //PROJET_FORMULE_1_STRUCTVOITURE_H
