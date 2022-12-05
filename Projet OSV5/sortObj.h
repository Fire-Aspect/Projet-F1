#include <stdio.h>
#include <stdlib.h>
#include "structVoiture.h"
#include "showOutput.h"


void sortObj(Voiture v[], int len) {
    int i, j;
    Voiture temp;
    //tri de la structure
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            if (v[i].total > v[j].total) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    //showOutput(v, len);
}

