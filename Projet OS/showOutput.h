#ifndef PROJET_FORMULE_1_SHOWOUTPUT_H
#define PROJET_FORMULE_1_SHOWOUTPUT_H

#include <stdlib.h>

typedef struct {
    int vId;
    int s1;
    int s2;
    int s3;
    int tTour[2];
}Voiture;

int showOutput(Voiture v[], size_t len);

#endif //PROJET_FORMULE_1_SHOWOUTPUT_H
