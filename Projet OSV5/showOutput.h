 //Mis à jour le 14/01/2023

//Différents includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structVoiture.h"

static void printTable(FILE *out, Voiture *array, int len) {
    int kTemp;
    Voiture classement[21];
    memcpy(classement, array, len * sizeof(Voiture));

    char *rowC[] = {"Numéro", "S1 (tour)", "S2 (tour)", "S3 (tour)", "Meilleur tour", "Différence", "statut"};

    fprintf(out, "%s", "+========+==============+==============+==============+=================+=====================+============+\n");
    fprintf(out, "|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\n",
            -6, rowC[0], -12, rowC[1], -12, rowC[2], -12, rowC[3], -15, rowC[4], -18, rowC[5], -10, rowC[6]);
    fprintf(out, "+%*s+%*s+%*s+%*s+%*s+%*s+%*s+\n",
            -3, "--------", 12, "--------------", 12, "--------------", 12, "--------------",
            -15, "-----------------", 18, "---------------------", 10, "------------");

    for (int i = 0; i < len - 1; ++i) {
        const char *status_str;
        const char *color;

        if (classement[i].eliminated == 1) {
            status_str = "ELIMINATED";
            color = "\033[1;31m";  // bold red
        } else if (classement[i].status == 2) {
            status_str = "OUT";
            color = "\033[1;31m";  // bold red
        } else if (classement[i].status == 1) {
            status_str = "STANDS";
            color = "\033[0;33m";  // yellow
        } else {
            status_str = "EN COURSE";
            color = "\033[0;32m";  // green
        }

        if (i == 0) {
            fprintf(out, "| %-6d | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m | %.0f.%-13.3f |                     | %s%-10s\033[0m |\n",
                    classement[i].vId,
                    classement[i].curS1, classement[i].curS2, classement[i].curS3,
                    classement[i].tTour[0], classement[i].tTour[1],
                    color, status_str);
        } else {
            kTemp = i - 1;
            fprintf(out, "| %-6d | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m | %.0f.%-13.3f | \033[0;33m+%-18.3f\033[0m | %s%-10s\033[0m |\n",
                    classement[i].vId,
                    classement[i].curS1, classement[i].curS2, classement[i].curS3,
                    classement[i].tTour[0], classement[i].tTour[1],
                    fabsf(classement[i].total - classement[kTemp].total),
                    color, status_str);
        }
    }

    fprintf(out, "%s", "+========+==============+==============+==============+=================+=====================+============+\n");
    fprintf(out, "| \033[1;31m%-6s\033[0m | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m |\n",
            "Best", classement[20].idBest[0], classement[20].idBest[1], classement[20].idBest[2]);
    fprintf(out, "|        | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m | \033[0;36m%-12.3f\033[0m |\n",
            classement[20].s1, classement[20].s2, classement[20].s3);
    fprintf(out, "%s", "+=====================================================+\n");
    if (classement[20].idBestLap != 0) {
        fprintf(out, "| \033[1;35mMeilleur tour\033[0m : \033[0;36m#%-4d\033[0m  %.0f.%.3f%18s|\n",
                classement[20].idBestLap, classement[20].tTour[0], classement[20].tTour[1], "");
        fprintf(out, "%s", "+=====================================================+\n");
    }
}

void showOutput(Voiture *array, int len) {
    system("clear");
    printTable(stdout, array, len);
}

void showOutputToFile(FILE *f, Voiture *array, int len) {
    printTable(f, array, len);
}
