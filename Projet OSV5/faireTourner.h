//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timeGen.h"
#include "sortObj.h"


//Fonction faireTourner (param : tempsSession ==> temps de session)
//But : Faire tourner une voiture

int faireTourner(int tempsSession) {
    srand(time(0));

    char session;
    printf("%s", "                                   ##############################################  ###############\n"
                        "                       ########################################################   ###############\n"
                        "                     #########################################################  ###############\n"
                        "                  #########################################################   ###############\n"
                        "                ################                                            ###############\n"
                        "              ###############   ########################################  ###############\n"
                        "           ###############   ########################################  ###############\n"
                        "         ##############   ########################################   ###############\n"
                        "       ##############   ##############                             ###############\n"
                        "     ##############   #############                              ###############\n\n");
    printf("%s", "Veuillez taper quelle session démarrer:\n -P1 = 1\n -P2 = 2\n -P3 = 3\n -Q1 = 4\n -Q2 = 5\n -Q3 = 6\n"
                 " -Course = 7\n -Course Sprint = 8\n");
    scanf("%s", &session);

    int shmid;
    Voiture *circuit;    //Création d'un tableau contenant des voitures
    shmid = shmget(69, 21 * sizeof(Voiture), IPC_CREAT | 0666); //Création de la mémoire partagée
    circuit = shmat(shmid, 0, 0);     //Liaison de la mémoire partagée à Circuit
    float test[5] = {};

    printf("%d \n", shmid);     //Outil de debug

    //Assignation à la dernière voiture de valeurs différentes de 0.
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
            vieVoiture(circuit, k, tempsSession);
        }
    }

    //Fonction d'affichage future
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    do {
        sleep(1);
        secondePendant = time(NULL);
        showOutput(sortObj(circuit, 21, session), 21);
        //Patiente 2 secondes avant de re-afficher
        sleep(1);
    } while (secondePendant <= secondeDepart + tempsSession + 1);

    //écritureFichier();
    char *nomFichier;
    switch (session) {
        case '1':
            nomFichier = "P1";
            break;
        case '2':
            nomFichier = "P2";
            break;
        case '3':
            nomFichier = "P3";
            break;
        case '4':
            nomFichier = "Q1";
            break;
        case '5':
            nomFichier = "Q2";
            break;
        case '6':
            nomFichier = "Q3";
            break;
        case '7':
            nomFichier = "Course";
            break;
        case '8':
            nomFichier = "CourseSprint";
            break;
    }

    ecritureFichier(nomFichier, sortObj(circuit, 21, session), session);
    shmdt(circuit);
    shmctl(shmid, IPC_RMID, NULL);

    printf("%s\n","Père Fini");





}

