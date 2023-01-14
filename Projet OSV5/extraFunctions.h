//Mis à jour le 12/01/2023

//Différents includes
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "showOutput.h"

//Fonction vieVoiture (param : )
//But : Compléter un tableau de 8 cases représentant les temps de tour d'une voiture

int vieVoiture(Voiture* array, int numCase, int pid, int tempsSess) {

    int numero_Voiture[21] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9, 999};
    float temps[5] = {};
    time_t secondeDepart;
    time_t secondePendant;
    secondeDepart = time(NULL);

    //Boucle de remplissage de tableau
    do {
        for (int j = 0; j < 20; j++){
            timeGenerator(temps);
        }
        //Patiente 1 sec avant de refaire un temps
        sleep(1);
        for (int i = 0; i <= 10; i++) {
            switch (i) {
                case 0:
                    array[numCase].s1 = temps[0];
                    break;
                case 1:
                    array[numCase].s2 = temps[1];
                    break;
                case 2:
                    array[numCase].s3 = temps[2];
                    break;
                case 3:
                    array[numCase].tTour[0] = temps[3];
                    break;
                case 4:
                    array[numCase].tTour[1] = temps[4];
                    break;
                case 5:
                    array[numCase].vId = numero_Voiture[numCase];
                    break;
                case 6:
                    array[numCase].total = temps[0] + temps[1] + temps[2];
                    break;
                case 7 :
                    array[numCase].pidFils = pid;
                    break;
                case 8 :
                    //statut de la voiture : 0 COURSE 1 PIT-STANDS 2 OUT
                    array[numCase].status = 0;
                    break;
                case 9:
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
            }

            //aux stands
            if (array[numCase].status == 1){
                array[numCase].total += 25;
            }
        }

        secondePendant = time(NULL);

    } while (secondePendant <= secondeDepart + tempsSess);

    exit(0);
}


//Fonction pour écrire en fichier PROTOTYPE À AMÉLIORER param : pointeur vers array
int ecritureFichier(char* nomFichier, Voiture* classementFinal, char session) {

    int **classPourOrdi;
    classPourOrdi = (int **) malloc(20 * sizeof(int *));
    for (int i = 0; i < 20; i++) {
        classPourOrdi[i] = (int *) malloc(2 * sizeof(int ));
    }
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
            }
        }
    }

    char fichierAffi[15];
    sprintf(fichierAffi, "A_%s", nomFichier);
    //Ouverture du fichier
    //S'il n'arrive pas à ouvrir le fichier, il le cré et il l'ouvre
    FILE *f = fopen(nomFichier,"w");

    //Vérification de la bonne ouverture du fichier sinon erreur
    if (f == NULL) {
        printf("\nImpossible d'ouvrir le fichier\n");
        return -1;
    }

    switch (session) {
        case '1':
        case '2':
        case '3':
            //écriture en fichier pour P1, P2 et P3
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            fwrite(classPourOrdi,sizeof(Voiture), 20, f);

            break;

        case '4':
            //écriture en fichier pour Q1
            //élimination des 5 dernières voitures
            for(int i = 15; i < 20; i ++){
                classPourOrdi[i][1] = 1;
            }
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            fwrite(classPourOrdi,sizeof(Voiture), 20, f);
            break;

        case '5':
            //écriture en fichier pour Q2
            //élimination des 10 dernières voitures
            for(int i = 10; i < 20; i ++){
                classPourOrdi[i][1] = 1;
            }
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            fwrite(classPourOrdi,sizeof(Voiture), 20, f);
            break;

        case '6':
        case '7':
        case '8':
            freopen(fichierAffi, "w", stdout);
            showOutput(classementFinal, 21);
            fclose(stdout);
            fwrite(classPourOrdi,sizeof(Voiture), 20, f);
            break;
    }

    //Ferme le fichier + erreur de fermeture fichier
    fclose(f);

    // Libération de la mémoire allouée
    for (int i = 0; i < 20; i++) {
        free(classPourOrdi[i]);
    }
    free(classPourOrdi);
}


//Fonction pour lire en fichier PROTOTYPE A AMELIORER

int **lectureFichier(char session ) {

    char *nomFichier;
    switch (session) {
        case 5:
            nomFichier ="Q1.txt";
            break;
        case 6:
            nomFichier = "Q2.txt";
            break;
        case 7:
            nomFichier ="Q3.txt";
            break;
        case 8:
            nomFichier = "Q3.txt";
            break;
    }

    FILE *f = fopen(nomFichier, "r");

    // Si l'ouverture du fichier a réussi, on continue sinon erreur
    if (f == NULL) {
        printf("\nImpossible d'ouvrir le fichier\n");
    }

    int lignes, colonnes;
    fscanf(f, "%d %d", &lignes, &colonnes);

    int **classDepuisFichier = (int **) malloc(lignes * sizeof(int *));
    for (int i = 0; i < lignes; i++) {
        classDepuisFichier[i] = (int *) malloc(colonnes * sizeof(int));
    }

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            fscanf(f, "%d", &classDepuisFichier[i][j]);
        }
    }
    // Fermeture fichier + vérification erreur
    if (fclose(f) == EOF) {
        printf("Fermeture du fichier impossible \n");
    }

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%d ", classDepuisFichier[i][j]);
        }
        printf("\n");
    }
    return classDepuisFichier;
}