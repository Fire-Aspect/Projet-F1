//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timeGen.h"
#include "structVoiture.h"
#include "extraFunctions.h"
#include "sortObj.h"


//Fonction faireTourner (param : tempsSession ==> temps de session)
//But : Faire tourner une voiture

int faireTourner(int tempsSession) {
    srand(time(0));

    char session;
    printf("%s","Veuillez taper quelle session démarrer:\n -P1 = 1\n -P2 = 2\n -P3 = 3\n -Q1 = 4\n -Q2 = 5\n -Q3 = 6\n"
                " -Course = 7\n -Course Sprint = 8\n");
    scanf("%s", &session);

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
        showOutput(sortObj(circuit, 21, session), 21);
        //Patiente 2 secondes avant de ré-afficher
        sleep(2);
    }
    while (secondePendant <= secondeDepart + tempsSession+1);


    //ecritureFichier();
    char* nomFichier;
    switch (session) {
        case '1':
            nomFichier = "P1.txt";
            break;
        case '2':
            strcpy(nomFichier, "P2.txt");
            break;
        case '3':
            strcpy(nomFichier, "P3.txt");
            break;
        case '4':
            strcpy(nomFichier, "Q1.txt");
            break;
        case '5':
            strcpy(nomFichier, "Q2.txt");
            break;
        case '6':
            strcpy(nomFichier, "Q3.txt");
            break;
        case '7':
            strcpy(nomFichier, "Course.txt");
            break;
        case '8':
            strcpy(nomFichier, "CourseSprint.txt");
            break;
    }
    ecritureFichier(nomFichier,sortObj(circuit, 21, session),session);
    shmdt(circuit);
    shmctl(shmid, IPC_RMID, NULL);

    printf("%s\n","Père Fini");





}

