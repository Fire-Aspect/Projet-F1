//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "showOutput.h"

#define MAX_NUMBERS 4
#define MAX_VALUE 20

//Fonction vieVoiture
//But : Compléter un tableau de 10 cases représentant les temps de tour d'une voiture

int vieVoiture(Voiture *circuit, int numCase, int tempsSess, char session, int nbrTour, int *nbrTourTotal) {

    int numero_Voiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};
    float temps[5] = {};
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);
    int numbers[MAX_NUMBERS];
    int last_generated = -1;
    int count[MAX_VALUE] = {0};
    bool generated[MAX_VALUE] = {false};
    int stand_time = rand() % 2;
    int out_rand = rand() % 15;
    int voitRan = rand() % 20;

    //Regarde si on est en session de course ou non
    if (session != '7' && session != '8') {
        //Boucle de remplissage de tableau
        do {
            int p;
            for (int j = 0; j < 20; j++) {
                timeGenerator(temps);
            }


            //Patiente 1 sec avant de refaire un temps
            sleep(1);

            for (int i = 0; i <= 9; i++) {
                if (circuit[numCase].eliminated == 1) {
                    break;
                }
                switch (i) {
                    case 0:
                        if (out_rand == 3) {
                            circuit[voitRan].status = 2;
                        }
                        if (circuit[numCase].status == 2) {
                            continue;
                        }
                        circuit[numCase].status = 0;
                        //Logique pour aller au stand aléatoirement
                        if (stand_time == 0) {
                            for (p = 0; p < MAX_NUMBERS; p++) {
                                int rnd = rand() % MAX_VALUE;
                                if (rnd != last_generated && (count[rnd] < 3)) {
                                    numbers[p] = rnd;
                                    last_generated = rnd;
                                    count[rnd]++;
                                    if (count[rnd] == 3) generated[rnd] = true;
                                    if (numbers[p] == numCase) {
                                        circuit[numCase].status = 1;
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
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s1 = circuit[numCase].s1;
                            break;
                        }
                        circuit[numCase].s1 = temps[0];

                        break;
                    case 2:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s2 = circuit[numCase].s2;
                            break;
                        }
                        circuit[numCase].s2 = temps[1];
                        break;
                    case 3:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s3 = circuit[numCase].s3;
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].s3 = temps[2] + 25;
                        } else {
                            circuit[numCase].s3 = temps[2];
                        }
                        break;
                    case 4:
                        if (circuit[numCase].eliminated == 1) {
                            circuit[numCase].tTour[0] = 0;
                            break;
                        }
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].tTour[0] = circuit[numCase].tTour[0];
                            break;
                        }
                        circuit[numCase].tTour[0] = temps[3];
                        break;
                    case 5:
                        if (circuit[numCase].eliminated == 1) {
                            circuit[numCase].tTour[1] = 0;
                            break;
                        }
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].tTour[1] = circuit[numCase].tTour[1];
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].tTour[1] = temps[4] + 25;
                            if (circuit[numCase].tTour[1] > 60) {
                                circuit[numCase].tTour[1] -= 60;
                                circuit[numCase].tTour[0] += 1;
                            }
                        } else {
                            circuit[numCase].tTour[1] = temps[4];
                        }
                        break;
                    case 6:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].total = circuit[numCase].s1 + circuit[numCase].s2 + circuit[numCase].s3;
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].total = temps[0] + temps[1] + temps[2] + 25;
                        } else {
                            circuit[numCase].total = temps[0] + temps[1] + temps[2];
                        }
                        break;
                    case 7 :
                        circuit[numCase].vId = numero_Voiture[numCase];
                        break;
                        //Vérification des best temps de la session
                    case 8:
                        if (circuit[numCase].status == 2 && circuit[numCase].s1 == 0 && circuit[numCase].s2 == 0 &&
                            circuit[numCase].s3 == 0) {
                            circuit[numCase].total = 980;
                            continue;
                        }
                        if (circuit[numCase].s1 < circuit[20].s1) {
                            circuit[20].s1 = circuit[numCase].s1;
                            circuit[20].idBest[0] = circuit[numCase].vId;
                        }
                        if (circuit[numCase].s2 < circuit[20].s2) {
                            circuit[20].s2 = circuit[numCase].s2;
                            circuit[20].idBest[1] = circuit[numCase].vId;
                        }
                        if (circuit[numCase].s3 < circuit[20].s3) {
                            circuit[20].s3 = circuit[numCase].s3;
                            circuit[20].idBest[2] = circuit[numCase].vId;
                        }
                        break;
                    default:
                        printf("Erreur fils");
                        exit(-1);
                }
            }
            secondePendant = time(NULL);


        } while (secondePendant <= secondeDepart + tempsSess);
    }
    else {
        do {
            int p;
            for (int j = 0; j < 20; j++) {
                timeGenerator(temps);
            }

            //Patiente 1 sec avant de refaire un temps
            sleep(1);

            for (int i = 0; i <= 9; i++) {
                switch (i) {
                    case 0:
                        if (out_rand == 3) {
                            circuit[voitRan].status = 2;
                        }
                        if (circuit[numCase].status == 2) {
                            continue;
                        }
                        circuit[numCase].status = 0;
                        //Logique pour aller au stand aléatoirement
                        if (stand_time == 0) {
                            for (p = 0; p < MAX_NUMBERS; p++) {
                                int rnd = rand() % MAX_VALUE;
                                if (rnd != last_generated && (count[rnd] < 3)) {
                                    numbers[p] = rnd;
                                    last_generated = rnd;
                                    count[rnd]++;
                                    if (count[rnd] == 3) generated[rnd] = true;
                                    if (numbers[p] == numCase) {
                                        circuit[numCase].status = 1;
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
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s1 = circuit[numCase].s1;
                            break;
                        }
                        circuit[numCase].s1 = temps[0];

                        break;
                    case 2:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s2 = circuit[numCase].s2;
                            break;
                        }
                        circuit[numCase].s2 = temps[1];
                        break;
                    case 3:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].s3 = circuit[numCase].s3;
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].s3 = temps[2] + 25;
                        } else {
                            circuit[numCase].s3 = temps[2];
                        }
                        break;
                    case 4:
                            circuit[numCase].tTour[0] = 0;
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].tTour[0] = circuit[numCase].tTour[0];
                            break;
                        }
                        circuit[numCase].tTour[0] = temps[3];
                        break;
                    case 5:
                        circuit[numCase].tTour[1] = 0;

                        if (circuit[numCase].status == 2) {
                            circuit[numCase].tTour[1] = circuit[numCase].tTour[1];
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].tTour[1] = temps[4] + 25;
                            if (circuit[numCase].tTour[1] > 60) {
                                circuit[numCase].tTour[1] -= 60;
                                circuit[numCase].tTour[0] += 1;
                            }
                        } else {
                            circuit[numCase].tTour[1] = temps[4];
                        }
                        break;
                    case 6:
                        if (circuit[numCase].status == 2) {
                            circuit[numCase].total = circuit[numCase].s1 + circuit[numCase].s2 + circuit[numCase].s3;
                            break;
                        }
                        if (circuit[numCase].status == 1) {
                            circuit[numCase].total = temps[0] + temps[1] + temps[2] + 25;
                        } else {
                            circuit[numCase].total = temps[0] + temps[1] + temps[2];
                        }
                        break;
                    case 7 :
                        circuit[numCase].vId = numero_Voiture[numCase];
                        break;
                        //Vérification des best temps de la session
                    case 8:
                        if (circuit[numCase].status == 2 && circuit[numCase].s1 == 0 && circuit[numCase].s2 == 0 &&
                            circuit[numCase].s3 == 0) {
                            circuit[numCase].total = 980;
                            continue;
                        }
                        if (circuit[numCase].s1 < circuit[20].s1) {
                            circuit[20].s1 = circuit[numCase].s1;
                            circuit[20].idBest[0] = circuit[numCase].vId;
                        }
                        if (circuit[numCase].s2 < circuit[20].s2) {
                            circuit[20].s2 = circuit[numCase].s2;
                            circuit[20].idBest[1] = circuit[numCase].vId;
                        }
                        if (circuit[numCase].s3 < circuit[20].s3) {
                            circuit[20].s3 = circuit[numCase].s3;
                            circuit[20].idBest[2] = circuit[numCase].vId;
                        }
                        break;
                    default:
                        printf("Erreur fils");
                        exit(-1);
                }
            }
            nbrTourTotal[numCase]++;
        } while (nbrTourTotal[numCase] <= nbrTour);
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

//fonction pour renvoyer le nombre de tours en fonction du circuit choisi pour la course du Dimanche

int combienDeToursCourse(int parcours) {
    int nbTours;
    switch (parcours) {
        case 1:
            nbTours = ceil(325/5.411);
            break;
        case 2:
            nbTours = ceil(325/6.174);
            break;
        case 3:
            nbTours = ceil(325/5.303);
            break;
        case 4:
            nbTours = ceil(325/4.909);
            break;
        case 5:
            nbTours = ceil(325/5.410);
            break;
        case 6:
            nbTours = ceil(325/4.675);
            break;
        case 7:
            nbTours = ceil(325/3.367);
            break;
        case 8:
            nbTours = ceil(325/6.003);
            break;
        case 9:
            nbTours = ceil(325/4.361);
            break;
        case 10:
            nbTours = ceil(325/5.891);
            break;
        case 11:
            nbTours = ceil(325/4.318);
            break;
        case 12:
            nbTours = ceil(325/5.800);
            break;
        case 13:
            nbTours = ceil(325/4.381);
            break;
        case 14:
            nbTours = ceil(325/6.947);
            break;
        case 15:
            nbTours = ceil(325/4.259);
            break;
        case 16:
            nbTours = ceil(325/5.793);
            break;
        case 17:
            nbTours = ceil(325/5.063);
            break;
        case 18:
            nbTours = ceil(325/5.807);
            break;
        case 19:
            nbTours = ceil(325/5.513);
            break;
        case 20:
            nbTours = ceil(325/4.304);
            break;
        case 21:
            nbTours = ceil(325/5.411);
            break;
        case 22:
            nbTours = ceil(325/5.281);
            break;
        default:
            printf("Parcours inconnu");
            exit(-1);
    }
    return nbTours;
}

//fonction pour renvoyer le nombre de tours en fonction du circuit choisi pour la course sprint

int combienDeToursCourseSprint(int parcours) {
    int nbTours;
    switch (parcours) {
        case 1:
            nbTours = ceil(100/5.411);
            break;
        case 2:
            nbTours = ceil(100/6.174);
            break;
        case 3:
            nbTours = ceil(100/5.303);
            break;
        case 4:
            nbTours = ceil(100/4.909);
            break;
        case 5:
            nbTours = ceil(100/5.410);
            break;
        case 6:
            nbTours = ceil(100/4.675);
            break;
        case 7:
            nbTours = ceil(100/3.367);
            break;
        case 8:
            nbTours = ceil(100/6.003);
            break;
        case 9:
            nbTours = ceil(100/4.361);
            break;
        case 10:
            nbTours = ceil(100/5.891);
            break;
        case 11:
            nbTours = ceil(100/4.318);
            break;
        case 12:
            nbTours = ceil(100/5.800);
            break;
        case 13:
            nbTours = ceil(100/4.381);
            break;
        case 14:
            nbTours = ceil(100/6.947);
            break;
        case 15:
            nbTours = ceil(100/4.259);
            break;
        case 16:
            nbTours = ceil(100/5.793);
            break;
        case 17:
            nbTours = ceil(100/5.063);
            break;
        case 18:
            nbTours = ceil(100/5.807);
            break;
        case 19:
            nbTours = ceil(100/5.513);
            break;
        case 20:
            nbTours = ceil(100/4.304);
            break;
        case 21:
            nbTours = ceil(100/5.411);
            break;
        case 22:
            nbTours = ceil(100/5.281);
            break;
        default:
            printf("Parcours inconnu");
            exit(-1);
    }
    return nbTours;
}

// booléen pour savoir quand une voiture a fini son nombre de tours total

bool tlmATerminer(const int *nbrToursEffectuer, int nbrTours) {
    int voitureArrivees = 0;
    for (int i = 0; i < 20; i++) {
        if (nbrToursEffectuer[i] > nbrTours) {
            voitureArrivees++;
        }
    }
    return voitureArrivees == 20;
}