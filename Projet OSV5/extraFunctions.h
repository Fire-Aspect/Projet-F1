//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "showOutput.h"

#define MAX_NUMBERS 3
#define MAX_VALUE 20

//Fonction vieVoiture
//But : Compléter un tableau de 10 cases représentant les temps de tour d'une voiture

int vieVoiture(Voiture *array, int numCase, int tempsSess) {

    int numero_Voiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};
    float temps[5] = {};
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    int numbers[MAX_NUMBERS];
    int last_generated = -1;
    int count[MAX_VALUE] = {0};
    bool generated[MAX_VALUE] = {false};
    int sleep_time = rand() % 2;

    //Boucle de remplissage de tableau
    do {
        int p;
        for (int j = 0; j < 20; j++) {
            timeGenerator(temps);
        }
        //Patiente 1 sec avant de refaire un temps
        sleep(1);
        for (int i = 0; i <= 9; i++) {
            if (array[numCase].eliminated == 1) {
                break;
            }
            switch (i) {
                case 0:
                    array[numCase].status = 0;
                    //Logique pour aller au stand aléatoirement
                    if (sleep_time == 0) {
                        for (p = 0; p < MAX_NUMBERS; p++) {
                            int rnd = rand() % MAX_VALUE;
                            if (rnd != last_generated && (count[rnd] < 3)) {
                                numbers[p] = rnd;
                                last_generated = rnd;
                                count[rnd]++;
                                if (count[rnd] == 3) generated[rnd] = true;
                                if (numbers[p] == numCase) {
                                    array[numCase].status = 1;
                                }


                            } else {
                                // number already generated
                                p--;
                            }
                        }
                        break;
                    }
                    break;
                //Remplissage des temps par secteurs
                case 1:
                    array[numCase].s1 = temps[0];
                    break;
                case 2:
                    array[numCase].s2 = temps[1];
                    break;
                case 3:
                    if (array[numCase].status == 1) {
                        array[numCase].s3 = temps[2] + 25;
                    } else {
                        array[numCase].s3 = temps[2];
                    }
                    break;
                case 4:
                    array[numCase].tTour[0] = temps[3];
                    break;
                case 5:
                    if (array[numCase].status == 1) {
                        array[numCase].tTour[1] = temps[4] + 25;
                        if (array[numCase].tTour[1] > 60) {
                            array[numCase].tTour[1] -= 60;
                            array[numCase].tTour[0] += 1;
                        }
                    } else {
                        array[numCase].tTour[1] = temps[4];
                    }
                    break;
                case 6:

                    if (array[numCase].status == 1) {
                        array[numCase].total = temps[0] + temps[1] + temps[2] + 25;
                    } else {
                        array[numCase].total = temps[0] + temps[1] + temps[2];
                    }
                    break;
                case 7 :
                    array[numCase].vId = numero_Voiture[numCase];
                    break;
                //Vérification des best temps de la session
                case 8:
                    if (array[numCase].s1 < array[20].s1) {
                        array[20].s1 = array[numCase].s1;
                        array[20].idBest[0] = array[numCase].vId;
                    }
                    if (array[numCase].s2 < array[20].s2) {
                        array[20].s2 = array[numCase].s2;
                        array[20].idBest[1] = array[numCase].vId;
                    }
                    if (array[numCase].s3 < array[20].s3) {
                        array[20].s3 = array[numCase].s3;
                        array[20].idBest[2] = array[numCase].vId;
                    }
                    break;
                default:
                    printf("Erreur fils");
                    exit(-1);
            }

            //aux stands

        }

        secondePendant = time(NULL);

    } while (secondePendant <= secondeDepart + tempsSess);

    exit(0);
}


//Fonction pour écrire en fichier PROTOTYPE À AMÉLIORER param : pointeur vers array
int ecritureFichier(char* nomFichier, Voiture* classementFinal, char session) {

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

    char fichierAffi[15];
    sprintf(fichierAffi, "A_%s.txt", nomFichier);

    //Ouverture du fichier
    //S'il n'arrive pas à ouvrir le fichier, il le cré et il l'ouvre
    if ((f = fopen(nomFichier, "wb")) == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(-1);
    }

    switch (session) {
        case '1':
        case '2':
        case '3':
            //écriture en fichier pour P1, P2 et P3
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                exit(-1);
            }
            fclose(f);
            break;

        case '4':
            //écriture en fichier pour Q1
            //élimination des 5 dernières voitures
            for (int i = 0; i < 20; i++) {
                if (i >= 15) {
                    classPourOrdi[i][1] = 1;
                }
            }
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                exit(-1);
            }
            fclose(f);
            break;

        case '5':
            //écriture en fichier pour Q2
            //élimination des 10 dernières voitures
            for (int i = 0; i < 20; i++) {
                if (i >= 10) {
                    classPourOrdi[i][1] = 1;
                }
            }
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                exit(-1);
            }
            fclose(f);
            break;

        case '6':
        case '7':
        case '8':
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            if (fwrite(classPourOrdi, sizeof(int), 20 * 2, f) != 20 * 2) {
                printf("\nErreur d'écriture\n");
                exit(-1);
            }
            fclose(f);
            break;
        default:
            printf("Erreur switch");
            exit(-1);
    }
}


//Fonction pour lire en fichier PROTOTYPE A AMELIORER

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
        case '7':
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