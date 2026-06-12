//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "semaphore.h"
#include "showOutput.h"


//Fonction vieVoiture
//But : Compléter un tableau de 10 cases représentant les temps de tour d'une voiture

int vieVoiture(Voiture *array, int numCase, int tempsSess, int semid) {

    // Graine unique par processus pour éviter des temps identiques entre fils
    srand((unsigned int)(time(NULL) ^ getpid()));

    int numero_Voiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};
    float temps[3] = {0};
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    int pit_count = 0;       // nombre d'arrêts aux stands pour cette voiture
    int out_triggered = 0;

    //Boucle de remplissage de tableau
    do {
        timeGenerator(temps);
        for (int i = 0; i <= 8; i++) {
            if (array[numCase].eliminated == 1) {
                break;
            }
            switch (i) {
                case 0:
                    // Abandon aléatoire : 1 chance sur 100 par tour, une seule fois par session
                    if (!out_triggered && (rand() % 100) == 3) {
                        int victime = rand() % 20;
                        sem_wait_mutex(semid);
                        if (array[victime].eliminated == 0) {
                            array[victime].status = 2;
                        }
                        sem_signal_mutex(semid);
                        out_triggered = 1;
                    }
                    sem_wait_mutex(semid);
                    if (array[numCase].status == 2) {
                        sem_signal_mutex(semid);
                        continue;
                    }
                    // Retour des stands : remettre EN COURSE après un tour au stand
                    if (array[numCase].status == 1) {
                        array[numCase].status = 0;
                        sem_signal_mutex(semid);
                        break;
                    }
                    array[numCase].status = 0;
                    // Arrêt aux stands : 1 chance sur 20 par tour, max 3 arrêts
                    if (pit_count < 3 && (rand() % 20) == 0) {
                        array[numCase].status = 1;
                        pit_count++;
                    }
                    sem_signal_mutex(semid);
                    break;
                //Remplissage des temps par secteurs (temps courant du tour)
                case 1:
                    if (array[numCase].status == 2) {
                        break;
                    }
                    array[numCase].curS1 = temps[0];
                    // Meilleur S1 personnel
                    if (array[numCase].s1 == 0 || temps[0] < array[numCase].s1) {
                        array[numCase].s1 = temps[0];
                    }
                    break;
                case 2:
                    if (array[numCase].status == 2) {
                        break;
                    }
                    array[numCase].curS2 = temps[1];
                    if (array[numCase].s2 == 0 || temps[1] < array[numCase].s2) {
                        array[numCase].s2 = temps[1];
                    }
                    break;
                case 3:
                    if (array[numCase].status == 2) {
                        break;
                    }
                    {
                        float s3cur = (array[numCase].status == 1) ? temps[2] + 25 : temps[2];
                        array[numCase].curS3 = s3cur;
                        if (array[numCase].s3 == 0 || s3cur < array[numCase].s3) {
                            array[numCase].s3 = s3cur;
                        }
                    }
                    break;
                case 4:
                    // cases 4 and 5 are handled together in case 6; skip here
                    break;
                case 5:
                    break;
                case 6:
                    if (array[numCase].status == 2) {
                        break;
                    }
                    {
                        float lapTotal = (array[numCase].status == 1)
                            ? temps[0] + temps[1] + temps[2] + 25
                            : temps[0] + temps[1] + temps[2];
                        // Pit laps never count as the personal best lap
                        if (array[numCase].status != 1) {
                            if (array[numCase].total == 0 || lapTotal < array[numCase].total) {
                                array[numCase].total = lapTotal;
                                float min = 0, sec = lapTotal;
                                while (sec > 60) { sec -= 60; min += 1; }
                                array[numCase].tTour[0] = min;
                                array[numCase].tTour[1] = sec;
                            }
                        }
                    }
                    break;
                case 7 :
                    array[numCase].vId = numero_Voiture[numCase];
                    break;
                //Vérification des best temps de la session (globaux) — section critique
                case 8:
                    if (array[numCase].status == 2) {
                        if (array[numCase].total == 0) {
                            array[numCase].total = 980;
                        }
                        break;
                    }
                    sem_wait_mutex(semid);   // P — entrée section critique
                    if (array[numCase].curS1 > 0 && array[numCase].curS1 < array[20].s1) {
                        array[20].s1 = array[numCase].curS1;
                        array[20].idBest[0] = array[numCase].vId;
                    }
                    if (array[numCase].curS2 > 0 && array[numCase].curS2 < array[20].s2) {
                        array[20].s2 = array[numCase].curS2;
                        array[20].idBest[1] = array[numCase].vId;
                    }
                    if (array[numCase].curS3 > 0 && array[numCase].curS3 < array[20].s3) {
                        array[20].s3 = array[numCase].curS3;
                        array[20].idBest[2] = array[numCase].vId;
                    }
                    sem_signal_mutex(semid); // V — sortie section critique
                    break;
                default:
                    printf("Erreur fils");
                    exit(-1);
            }


        }

        //Patiente 1 sec avant de refaire un temps (après écriture,
        //pour que le premier affichage montre déjà des temps)
        sleep(1);
        secondePendant = time(NULL);

    } while (secondePendant <= secondeDepart + tempsSess);

    exit(0);
}


//Fonction vieVoitureCourse — un fils par voiture pour la course sprint / du dimanche
//Nombre de tours fixe, classement par temps cumulé, arrêts aux stands en secteur 3
int vieVoitureCourse(Voiture *array, int numCase, int nbTours, int pitObligatoire, int semid) {

    srand((unsigned int)(time(NULL) ^ getpid()));

    float temps[3] = {0};
    int pit_count = 0;

    for (int tour = 1; tour <= nbTours; tour++) {
        if (array[numCase].status == 2) {
            break;  //abandon : la voiture s'arrête
        }
        timeGenerator(temps);

        // Abandon aléatoire : ~1 chance sur 200 par tour
        if ((rand() % 200) == 3) {
            sem_wait_mutex(semid);
            array[numCase].status = 2;
            sem_signal_mutex(semid);
            break;
        }

        // Arrêt aux stands (secteur 3) : 1 chance sur 10 par tour, max 3 arrêts.
        // Course du dimanche : 1 arrêt obligatoire, forcé en fin de course si pas encore fait
        int pit = 0;
        if (pit_count < 3 && (rand() % 10) == 0) pit = 1;
        if (pitObligatoire && pit_count == 0 && tour == nbTours - 1) pit = 1;
        if (pit) pit_count++;

        float s3 = pit ? temps[2] + 25 : temps[2];
        float lapTotal = temps[0] + temps[1] + s3;

        sem_wait_mutex(semid);
        array[numCase].status = pit ? 1 : 0;
        array[numCase].curS1 = temps[0];
        array[numCase].curS2 = temps[1];
        array[numCase].curS3 = s3;
        array[numCase].cumul += lapTotal;
        array[numCase].laps = tour;

        // Meilleurs temps personnels par secteur
        if (array[numCase].s1 == 0 || temps[0] < array[numCase].s1) array[numCase].s1 = temps[0];
        if (array[numCase].s2 == 0 || temps[1] < array[numCase].s2) array[numCase].s2 = temps[1];
        if (array[numCase].s3 == 0 || s3 < array[numCase].s3) array[numCase].s3 = s3;

        // Meilleur tour personnel (un tour avec arrêt ne compte pas)
        if (!pit && (array[numCase].total == 0 || lapTotal < array[numCase].total)) {
            array[numCase].total = lapTotal;
            float min = 0, sec = lapTotal;
            while (sec > 60) { sec -= 60; min += 1; }
            array[numCase].tTour[0] = min;
            array[numCase].tTour[1] = sec;
        }

        // Meilleurs temps globaux par secteur
        if (temps[0] < array[20].s1) { array[20].s1 = temps[0]; array[20].idBest[0] = array[numCase].vId; }
        if (temps[1] < array[20].s2) { array[20].s2 = temps[1]; array[20].idBest[1] = array[numCase].vId; }
        if (s3       < array[20].s3) { array[20].s3 = s3;       array[20].idBest[2] = array[numCase].vId; }

        // Meilleur tour global de la course
        if (!pit && lapTotal < array[20].total) {
            array[20].total = lapTotal;
            array[20].idBestLap = array[numCase].vId;
            float min = 0, sec = lapTotal;
            while (sec > 60) { sec -= 60; min += 1; }
            array[20].tTour[0] = min;
            array[20].tTour[1] = sec;
        }
        sem_signal_mutex(semid);

        sleep(1);   //1 seconde = 1 tour simulé
    }

    exit(0);
}


//Fonction pour écrire en fichier
int ecritureFichier(char *nomFichier, Voiture *classementFinal, char session) {

    FILE *f;
    int classPourOrdi[20][2];
    // Initialisation des valeurs
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 2; j++) {
            switch (j) {
                case 0:
                    classPourOrdi[i][j] = classementFinal[i].vId;
                    break;
                case 1:
                    classPourOrdi[i][j] = classementFinal[i].eliminated;
                    break;
                default:
                    printf("Erreur");
                    exit(-1);
            }
        }
    }

    char fichierAffi[32];
    snprintf(fichierAffi, sizeof(fichierAffi), "A_%s.txt", nomFichier);

    //Ouverture du fichier
    //S'il n'arrive pas à ouvrir le fichier, il le cré et il l'ouvre
    if ((f = fopen(nomFichier, "wb")) == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(-1);
    }

    FILE *fAff = fopen(fichierAffi, "w");
    if (fAff == NULL) {
        printf("Impossible d'ouvrir le fichier d'affichage\n");
        fclose(f);
        exit(-1);
    }

    switch (session) {
        case '1':
        case '2':
        case '3':
            //écriture en fichier pour P1, P2 et P3
            showOutputToFile(fAff, classementFinal, 21);
            fclose(fAff);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                fclose(f);
                exit(-1);
            }
            fclose(f);
            break;

        case '4':
            //écriture en fichier pour Q1 — élimination des 5 dernières voitures
            for (int i = 15; i < 20; i++) {
                classPourOrdi[i][1] = 1;
            }
            showOutputToFile(fAff, classementFinal, 21);
            fclose(fAff);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                fclose(f);
                exit(-1);
            }
            fclose(f);
            break;

        case '5':
            //écriture en fichier pour Q2 — élimination des 10 dernières voitures
            for (int i = 10; i < 20; i++) {
                classPourOrdi[i][1] = 1;
            }
            showOutputToFile(fAff, classementFinal, 21);
            fclose(fAff);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                fclose(f);
                exit(-1);
            }
            fclose(f);
            break;

        case '6':
        case '7':
        case '8':
            showOutputToFile(fAff, classementFinal, 21);
            fclose(fAff);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                fclose(f);
                exit(-1);
            }
            fclose(f);
            break;
        default:
            fclose(fAff);
            fclose(f);
            printf("Erreur switch");
            exit(-1);
    }
    return 0;
}


//Fonction pour lire en fichier

int *lectureFichier(char session) {
    FILE *f;
    char *nomFichier;
    switch (session) {
        case '5':
            nomFichier = "Q1";
            break;
        case '6':
            nomFichier = "Q2";
            break;
        case '7': {
            //Week-end sprint : la grille du dimanche vient du résultat de la course sprint
            FILE *t = fopen("CourseSprint", "rb");
            if (t != NULL) {
                fclose(t);
                nomFichier = "CourseSprint";
            } else {
                nomFichier = "Q3";
            }
            break;
        }
        case '8':
            nomFichier = "Q3";
            break;
        default:
            printf("Erreur switch");
            exit(-1);
    }
    static int classDepuisFichier[20][2];
    static int *pointClassDepuisFichier = &classDepuisFichier[0][0];

    if ((f = fopen(nomFichier, "rb")) == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(-1);
    }

    if (fread(classDepuisFichier, sizeof(int), 20 * 2, f) != 20 * 2) {
        if (feof(f)) {
            printf("\nFin prématurée du fichier\n");
            exit(-1);
        } else {
            printf("\nErreur de lecture\n");
        }
        exit(-1);
    }

    // Fermeture fichier + vérification erreur
    if (fclose(f) == EOF) {
        printf("Fermeture du fichier impossible \n");
        exit(-1);
    }
    return pointClassDepuisFichier;
}