//Mis à jour le 14/01/2023

//Différents includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timeGen.h"
#include "sortObj.h"


//Fonction faireTourner (param : tempsSession ==> temps de session)
//But : Faire tourner plusieurs voitures

int faireTourner() {
    srand(time(0));

    char session;
    int tempsSession = 0;
    int nbrTour = 0;
    char *nomFichier;
    char parcours[2];

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
    printf("%s", "Veuillez taper quelle session démarrer:\n -P1 = 1\n -P2 = 2\n -P3 = 3\n -Q1 = 4\n -Q2 = 5\n "
                 "-Q3 = 6\n -Course = 7\n -Course Sprint = 8\n");

    scanf("%s", &session);

    // Choix de la session
    switch (session) {
        case '1':
            nomFichier = "P1";
            tempsSession = 60;
            break;
        case '2':
            nomFichier = "P2";
            tempsSession = 60;
            break;
        case '3':
            nomFichier = "P3";
            tempsSession = 60;
            break;
        case '4':
            nomFichier = "Q1";
            tempsSession = 18;
            break;
        case '5':
            nomFichier = "Q2";
            tempsSession = 15;
            break;
        case '6':
            nomFichier = "Q3";
            tempsSession = 12;
            break;
        case '7':
            nomFichier = "Course";
            printf("%s", "Veuillez choisir un parcours :\n -Sakhir = 1\n -Djeddah = 2\n -Melbourne = 3\n "
                         "-Imola = 4\n -Miami = 5\n -Montmelo = 6\n -Monaco= 7\n -Bakou = 8\n -Montréal = 9\n "
                         "-Silverstone = 10\n -Spielberg = 11\n -Castellet = 12\n -Mogyrod = 13\n  "
                         "-Spa-Francorchamps = 14\n -Zandvoort = 15\n -Monza = 16\n -Marina Bay = 17\n -Suzuka = 18\n "
                         "-Austin = 19\n -Mexico = 20\n -Sao Paulo = 21\n -Yas Marina = 22\n");
            scanf("%s", parcours);
            nbrTour = combienDeToursCourse(atoi(parcours));
            break;
        case '8':
            nomFichier = "CourseSprint";
            printf("%s", "Veuillez choisir un parcours :\n -Sakhir = 1\n -Djeddah = 2\n -Melbourne = 3\n "
                         "-Imola = 4\n -Miami = 5\n -Montmelo = 6\n -Monaco= 7\n -Bakou = 8\n -Montréal = 9\n "
                         "-Silverstone = 10\n -Spielberg = 11\n -Castellet = 12\n -Mogyrod = 13\n  "
                         "-Spa-Francorchamps = 14\n -Zandvoort = 15\n -Monza = 16\n -Marina Bay = 17\n -Suzuka = 18\n "
                         "-Austin = 19\n -Mexico = 20\n -Sao Paulo = 21\n -Yas Marina = 22\n");
            scanf("%s", parcours);
            nbrTour = combienDeToursCourseSprint(atoi(parcours));
            break;
        default:
            printf("%s", "Session inconnue, veuillez réessayer");
            exit(-1);
    }

    int shmidCircuit;
    int shmidTours;
    //Création d'un tableau contenant des voitures
    Voiture *circuit;
    //Variable contenant le nombre de tours parcourus par les voitures fils
    int *toursParcourus;

    // Création de la mémoire partagée pour le stockage des voitures
    shmidCircuit = shmget(69, 21 * sizeof(Voiture), IPC_CREAT | 0666);
    circuit = shmat(shmidCircuit, 0, 0);     //Liaison de la mémoire partagée à Circuit

    // Création de la mémoire partagée pour le stockage des tours parcourus par les voitures fils
    shmidTours = shmget(70, 20 * sizeof(int), IPC_CREAT | 0666);
    toursParcourus = shmat(shmidTours, 0, 0);     //Liaison de la mémoire partagée à toursParcourus

    //Assignation à la dernière voiture de valeurs différentes de 0.
    circuit[20].vId = 999;
    circuit[20].s1 = 999;
    circuit[20].s2 = 999;
    circuit[20].s3 = 999;
    circuit[20].total = 999;

    float tempsDebug[5];


    //Boucle de création de fils (20)
    for (int k = 0; k < 20; k++) {
        timeGenerator(tempsDebug);
        if (fork() == 0) {
            //Fils
            vieVoiture(circuit, k, tempsSession, session, nbrTour,toursParcourus);
        }
    }

    //Fonction d'affichage
    if (session != '7' && session != '8') {
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
    }
    else {
        do {
            sleep(1);
            showOutput(sortObj(circuit, 21, session), 21);
            //Patiente 2 secondes avant de re-afficher
            sleep(1);
        } while (!tlmATerminer(toursParcourus, nbrTour));
    }

    //écritureFichier();
    ecritureFichier(nomFichier, sortObj(circuit, 21, session), session);

    //libération de la mémoire partagée
    shmdt(toursParcourus);
    shmctl(shmidTours, IPC_RMID, NULL);
    shmdt(circuit);
    shmctl(shmidCircuit, IPC_RMID, NULL);



}

