//Mis à jour le 21/12/2022

//Différents includes
#include<stdio.h>
#include <unistd.h>
#include <time.h>
#include "structVoiture.h"

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
        for (int i = 0; i <= 9; i++) {
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
                    array[numCase].out = false;
                    break;
            }
        }

        secondePendant = time(NULL);

    } while (secondePendant <= secondeDepart + tempsSess);

    exit(0);
}


// Fonction qui renvoie le contenu de la dernière case d'une structure.
/*
int affichePre () {
       int copie =

};*/



//Fonction pour écrire en fichier PROTOTYPE A AMELIORER param : pointeur vers array

/*
int ecritureFichier(int* classementFinal) {
    FILE *fp;

    // Ouvre le fichier en écriture
    fp = fopen("formule.txt", "w");

    //Boucle pour écrire dans le fichier chaque donnée du classement final
    for (int i = 0; i < sizeof(classementFinal); i++) {
        fprintf(fp, "%d", classementFinal[i]);
    }
    //Ferme le fichier
    fclose(fp);

    return 0;
}
*/


int lectureFichier()
{
    // Ouvre le fichier en lecture
    FILE* file = fopen("formule.txt", "r");

    // Vérifie si l'ouverture du fichier a réussi
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n");
        return 1;
    }

    // Lit et affiche les données du fichier ligne par ligne
    int value;
    while (fscanf(file, "%d", &value) == 1)
    {
        printf("%d\n", value);
    }

    // Ferme le fichier
    fclose(file);

    return 0;
}
