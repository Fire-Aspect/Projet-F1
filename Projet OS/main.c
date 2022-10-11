#include <stdio.h>
#include <stdlib.h>
#include "sortArray.h"
#include "timeGen.h"
#include <time.h>
#include "showOutput.h"

/*
typedef struct {
   int vId;
    int s1;
    int s2;
    int s3;
    int tTour[2];
}Voiture;
*/

int main() {
    //Initialiser l'array
    /*
    int result, arr[] = {5, 2, 8, 7, 1, 34, 2};
    int longueur = sizeof(arr)/sizeof(arr[0]);

    result = sortArray(arr, longueur);
     */
    // printf("%d ", result);

    int numeroVoiture[10]= {44, 63, 1, 11, 55, 16, 4, 3, 14, 31};
    int BS1[3]= {0,0,0};
    int BS2[3]= {0,0,0};
    int BS3[3]= {0,0,0};
    int BT[3]= {0,0,0};
    
    srand(time(0));
    


    Voiture v[10];
    int temps[5] = {};
    
    size_t length = sizeof(v)/sizeof(v[0]);

    
    for (int k = 0; k < length; k++) {
    	timeGenerator(temps);
    	for (int i = 0; i < 6; i++) {
    	    switch (i) {
    	        case 0:
    	            v[k].s1 = temps[0];
    	            break;
    	        case 1:
    	            v[k].s2 = temps[1];
    	            break;
    	        case 2:
    	            v[k].s3 = temps[2];
    	            break;
    	        case 3:
    	            v[k].tTour[0] = temps[3];
    	            break;
    	        case 4:
    	            v[k].tTour[1] = temps[4];
    	            break;
    	        case 5:
    	            v[k].vId = numeroVoiture[k];
    	            break;
    	    }
    	}
    }
  
  /*
    for (int j = 0; j < 2; j++) {
    printf("%d\n", v[j].s1);
    printf("%d\n", v[j].s2);
    printf("%d\n", v[j].s3);
    printf("%d\n", v[j].tTour[0]);
    printf("%d\n", v[j].tTour[1]);
    printf("%d\n", v[j].vId);
    }
    printf("\n");
*/
    showOutput(v, length);

    return 0;
}
