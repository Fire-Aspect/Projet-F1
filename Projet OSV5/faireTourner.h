//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "structVoiture.h"
#include "sortObj.h"
#include "extraFunctions.h"

//Fonction faireTourner (param : tempsSession ==> temps de session)
//But : Faire tourner une voiture

int faireTourner(int tempsSession) {

    //ID des différentes voitures
    //Dernière case pour les meilleures temps
    int numeroVoiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};

    //Création d'un tableau de 21 cases
    Voiture v[21];

    int shmid;

    //Création d'une voiture qui est un pointeur Circuit
    Voiture *circuit;

    //Création de la mémoire partagée
    //Taille : 21 voitures
    shmid = shmget(69, 21 * sizeof(Voiture), IPC_CREAT | 0666);

    //Outil de debug
    printf("%d \n", shmid);

    //Liaison de la mémoire partagée à Circuit
    circuit = shmat(shmid, 0, 0);

    //Assignation à la dernière voiture de valeurs différentes de 0
    circuit[20].vId = 999;
    circuit[20].s1 = 999;
    circuit[20].s2 = 999;
    circuit[20].s3 = 999;
    circuit[20].total = 999;

    //Enregistrement de la longueur d'une voiture
    size_t length = (sizeof(v) / sizeof(v[0])) - 1;

    //Boucle de création de fils (20)
    for (int k = 0; k < length; k++) {
        if (fork() == 0) {
            //fils
            int pidFils = getpid();
            vieVoiture(circuit[k], k, pidFils, tempsSession);

        }
    }

    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    do{
        secondePendant = time(NULL);
        //affichage
    }
    while (secondePendant <= secondeDepart + tempsSession+1) ;


    //showOutput(v, length);
    //sortObj(v, length);
    //showOutput(v, length);

}



