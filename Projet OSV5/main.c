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


    faireTourner(5);

    return 0;
}

/*  TRUC A FAIRE POUR PERIODE D'ESSAIS
 *
Savoir si une voiture est aux stands (P)
Savoir si une voiture est out (abandon de la séance)
Dans ces 2 derniers cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement
Conserver sur fichier le classement final à la fin de chaque séance ainsi que les meilleurs temps S1, S2 et S3 et le meilleur tour.
 */


/* TRUC A FAIRE POUR PERIODE QUALIFS
 *
Savoir si une voiture est aux stands (P)
Savoir si une voiture est out (abandon de la séance)
Dans ces 2 derniers cas, on conserve toujours le meilleur temps de la voiture et celle-ci reste dans le classement
A la fin de Q1, il reste 15 voitures qualifiées pour Q2 et les 5 dernières sont placées à la fin de la grille de départ (places 16 à 20)
A la fin de Q2, il reste 10 voitures qualifiées pour Q3 et les 5 dernières sont placées dans les places 11 à 15 de la grille de départ
Le classement de Q3 attribue les places 1 à 10 de la grille de départ
Conserver sur fichier le classement final à la fin des 3 séances (ce sera l’ordre de départ pour la course sprint
 s’il y en a une ou pour la course du dimanche ), ainsi que les meilleurs temps en S1, S2, S3 et le meilleur tour.
*/


/*COURSE DIMANCHE + SPRINT
 *
 */