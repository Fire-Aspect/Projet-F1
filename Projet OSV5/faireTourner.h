//Mis à jour le 14/01/2023

//Différents includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "semaphore.h"
#include "timeGen.h"
#include "sortObj.h"

//Nombre de tours (1 seconde = 1 tour simulé)
#define NB_TOURS_COURSE 15   // ~300 km le dimanche
#define NB_TOURS_SPRINT 5    // ~100 km le samedi


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
    if (scanf(" %c", &session) != 1 || session < '1' || session > '8') {
        printf("Session invalide\n");
        return -1;
    }

    int shmid;
    Voiture *circuit;
    // Détruire un éventuel segment orphelin du crash précédent
    int old = shmget(69, 21 * sizeof(Voiture), 0666);
    if (old != -1) shmctl(old, IPC_RMID, NULL);

    shmid = shmget(69, 21 * sizeof(Voiture), IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); return -1; }
    circuit = shmat(shmid, 0, 0);
    if (circuit == (void *)-1) { perror("shmat"); return -1; }

    // Créer le sémaphore avant de forker (hérité par les fils)
    int semid = sem_create();

    //Assignation à la dernière voiture de valeurs différentes de 0.
    circuit[20].vId = 999;
    circuit[20].s1 = 999;
    circuit[20].s2 = 999;
    circuit[20].s3 = 999;
    circuit[20].total = 999;

    int numero_Voiture[20] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9};
    int estCourse = (session == '7' || session == '8');
    int nbTours = (session == '7') ? NB_TOURS_COURSE : NB_TOURS_SPRINT;

    //Pour Q2/Q3 : marquer en mémoire partagée les voitures éliminées
    //à la session précédente, pour qu'elles ne roulent pas
    if (session == '5' || session == '6') {
        int *classPrec = lectureFichier(session);
        for (int z = 0; z < 20; z++) {
            if (classPrec[z * 2 + 1] == 1) {
                for (int k = 0; k < 20; k++) {
                    if (numero_Voiture[k] == classPrec[z * 2]) {
                        circuit[k].vId = numero_Voiture[k];
                        circuit[k].eliminated = 1;
                        break;
                    }
                }
            }
        }
    }

    //Pour les courses : grille de départ depuis le fichier (Q3 ou CourseSprint)
    //Décalage de 0.5s par position de grille
    if (estCourse) {
        int *grille = lectureFichier(session);
        for (int pos = 0; pos < 20; pos++) {
            for (int k = 0; k < 20; k++) {
                if (numero_Voiture[k] == grille[pos * 2]) {
                    circuit[k].vId = numero_Voiture[k];
                    circuit[k].cumul = (float) pos * 0.5f;
                    break;
                }
            }
        }
    }

    //Boucle de création de fils (20)
    for (int k = 0; k < 20; k++) {
        if (circuit[k].eliminated == 1) {
            continue;   //pas de fils pour une voiture éliminée
        }
        if (fork() == 0) {
            //Fils
            if (estCourse) {
                vieVoitureCourse(circuit, k, nbTours, session == '7', semid);
            } else {
                vieVoiture(circuit, k, tempsSession, semid);
            }
        }
    }

    //Boucle d'affichage
    if (estCourse) {
        //La course se termine quand toutes les voitures ont fini ou abandonné
        int finis;
        do {
            sleep(1);
            showOutput(sortObj(circuit, 21, session), 21);
            finis = 0;
            for (int k = 0; k < 20; k++) {
                if (circuit[k].laps >= nbTours || circuit[k].status == 2) {
                    finis++;
                }
            }
        } while (finis < 20);
    } else {
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
        default:
            printf("Session invalide\n");
            shmdt(circuit);
            shmctl(shmid, IPC_RMID, NULL);
            sem_destroy(semid);
            return -1;
    }

    // Attendre la fin de tous les fils avant de détruire la mémoire partagée
    while (wait(NULL) > 0);

    ecritureFichier(nomFichier, sortObj(circuit, 21, session), session);
    shmdt(circuit);
    shmctl(shmid, IPC_RMID, NULL);
    sem_destroy(semid);

    printf("%s\n", "Père Fini");

    return 0;
}

