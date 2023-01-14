//Mis à Jour le 12/01/2023
// Projet C Formule 1
// Participants :
//               - IGLESIAS CARLOS
//               - IV ANTHONY
//               - KALINOWSKA ARTHUR
//               - MOENS PENNEWAERT ANTOINE


//Différents includes
#include <stdlib.h>
#include <time.h>
#include "faireTourner.h"

//Fonction main
//Principale fonction du programme
int main() {

    srand(time(0));


    faireTourner(20);

    return 0;
}

/*  TRUC A FAIRE POUR PERIODE D'ESSAIS
 *
Savoir si une voiture est out (abandon de la séance)
Dans ce dernier cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement
 */

/* TRUC A FAIRE POUR PERIODE QUALIFS
 *
Savoir si une voiture est out (abandon de la séance)
Dans ce dernier cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement


Le classement de Q3 attribue les places 1 à 10 de la grille de départ
s’il y en a une ou pour la course du dimanche ), ainsi que les meilleurs temps en S1, S2, S3 et le meilleur tour.
*/

/*COURSE DIMANCHE + SPRINT
 *
 */