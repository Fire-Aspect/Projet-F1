#include <stdio.h>
#include <stdlib.h>
#include "showOutput.h"

int showOutput(Voiture v[], size_t len) {

    char *rowC[] = {"Numero", "Secteur 1", "Secteur 2", "Secteur 3", "Temps par tour"};
    

    printf("%*s | %*s | %*s | %*s | %*s\n", -6, rowC[0], -12, rowC[1], -12, rowC[2], -12, rowC[3], -15, rowC[4]);
    printf("%*s | %*s | %*s | %*s | %*s\n", -3, "------", 12, "------------", 12, "------------", 12, "------------", -31, "-------------------------------");
    for (int i = 0; i < len; ++i) {
    
    
        printf("%-6d | %-12.3f | %-12.3f | %-12.3f | %.0f%s%-11.3f\n", v[i].vId, v[i].s1, v[i].s2, v[i].s3, v[i].tTour[0], ".", v[i].tTour[1]);
        }
	printf("%s", "======================================================================================\n");

}
