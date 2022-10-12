#ifndef PROJET_FORMULE_1_SHOWOUTPUT_H
#define PROJET_FORMULE_1_SHOWOUTPUT_H

#include <stdlib.h>

typedef struct {
    int vId;
    float s1;
    float s2;
    float s3;
    float tTour[2];
}Voiture;

int showOutput(Voiture v[], size_t len);

#endif //PROJET_FORMULE_1_SHOWOUTPUT_HPUT_H
