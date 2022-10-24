#include <stdio.h>
#include <stdlib.h>
#include "showOutput.h"
#include "showBest.h"
#include "structVoiture.h"

#define COLOR_CYAN  "\033[0;36m"
#define COLOR_CYAN_OFF   "\033[0m"

int showOutput(Voiture v[], size_t len) {
    char *rowC[] = {"Numero", "Secteur 1", "Secteur 2", "Secteur 3", "Temps par tour"};
    
    printf("%s", "======================================================================================\n");
    printf("|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\033[0;32m %*s \033[0m|\n", -6, rowC[0], -12, rowC[1], -12, rowC[2], -12, rowC[3], -28, rowC[4]);
    printf("| %*s | %*s | %*s | %*s | %*s\n", -3, "------", 12, "------------", 12, "------------", 12, "------------", -31, "-----------------------------|");
    for (int i = 0; i < len; ++i) {
    
    
        printf("| %-6d | %-12.3f | %-12.3f | %-12.3f | %.0f%s%-26.3f |\n", v[i].vId, v[i].s1, v[i].s2, v[i].s3, v[i].tTour[0], ".", v[i].tTour[1]);
        }
	printf("%s", "======================================================================================\n");
	
	/*

		printf("|%-s%-7s%s | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m | \033[0;36m#%-11d\033[0m | \033[0;36m#%-27d\033[0m |\n", "\033[1;31m", "Best", "\033[0m", v1, v2, v3, vT);
		printf("| %-6s | %-12.3f | %-12.3f | %-12.3f | %.0f%s%-26.3f |\n", " ", BS1, BS2, BS3, BTMinute, ".", BTSeconde);
		printf("%s", "======================================================================================\n");
		*/
	
}
