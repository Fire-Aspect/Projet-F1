//Mis à jour le 21/12/2022

//Différents includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timeGen.h"
#include "structVoiture.h"
#include "extraFunctions.h"
#include "showOutput.h"


//Fonction faireTourner (param : tempsSession ==> temps de session)
//But : Faire tourner une voiture

int faireTourner(int tempsSession) {
    srand(time(0));

    int shmid;
    Voiture *circuit;    //Création d'un tableau contenant des voitures
    shmid = shmget(69, 21 * sizeof(Voiture), IPC_CREAT | 0666); //Création de la mémoire partagée
    circuit = (Voiture *)shmat(shmid, 0, 0);     //Liaison de la mémoire partagée à Circuit

    float test[5] = {};

    printf("%d \n", shmid);     //Outil de debug

    //Assignation à la dernière voiture de valeurs différentes de 0
    circuit[20].vId = 999;
    circuit[20].s1 = 999;
    circuit[20].s2 = 999;
    circuit[20].s3 = 999;
    circuit[20].total = 999;

    //Boucle de création de fils (20)
    for (int k = 0; k < 20; k++) {
        timeGenerator(test);
        if (fork() == 0) {
            //Fils
            int pidFils = getpid();
            vieVoiture(circuit, k, pidFils, tempsSession);
        }
    }

    //Fonction d'affichage future
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    do{
        secondePendant = time(NULL);
        printf("\033[2J"); // Clear the terminal window
        showOutput(sortObj(circuit, 21, session), 21);
        //Patiente 2 secondes avant de ré-afficher
        sleep(2);
    }
    while (secondePendant <= secondeDepart + tempsSession+1);


    //ecritureFichier();
    shmdt(circuit);
    shmctl(shmid, IPC_RMID, NULL);

    printf("%s\n","Père Fini");





}

