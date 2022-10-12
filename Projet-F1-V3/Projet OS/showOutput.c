#include <stdio.h>
#include <stdlib.h>
#include "showOutput.h"

int showOutput(Voiture v[], size_t len) {

    char *rowC[] = {"Numero", "Secteur 1", "Secteur 2", "Secteur 3", "Temps"};
    

    printf("%*s | %*s | %*s | %*s | %*s\n", -6, rowC[0], -15, rowC[1], -15, rowC[2], -15, rowC[3], -15, rowC[4]);
    printf("%*s | %*s | %*s | %*s | %*s\n", -3, "------", 15, "---------------", 15, "---------------", 15, "---------------", -31, "-------------------------------");
    for (int i = 0; i < len; ++i) {
    
    	if (v[i].tTour[0] == 1) {
    
        	printf("%-6d | %d %-12s | %d %-12s | %d %-12s | %d %s %d %-11s\n", v[i].vId, v[i].s1, 		"secondes" , v[i].s2, "secondes" , v[i].s3, "secondes" , v[i].tTour[0], "minute", 			v[i].tTour[1], "secondes");
        }
        else {
        	printf("%-6d | %d %-12s | %d %-12s | %d %-12s | %d %s %d %-11s\n", v[i].vId, v[i].s1, 		"secondes" , v[i].s2, "secondes" , v[i].s3, "secondes" , v[i].tTour[0], "minutes", 			v[i].tTour[1], "secondes");
        }
    }


}
