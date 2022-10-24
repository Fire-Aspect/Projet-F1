#include <stdio.h>
#include <stdlib.h>
#include "faireTourner.h"
#include "showOutput.h"
#include "structVoiture.h"

float showBest(Voiture v[]) {

	struct Info {
		float BS1;
		float BS2;
		float BS3;
		float BTMinute;
		float BTSeconde;
	};
	struct Info getBest() {
	
		int v1, v2, v3, vT;
    
    
		for (int j = 0; j < 10; j++) {
                                
        	        if (v[j].tTour[1] < Info.BTSeconde && v[j].tTour[0] <= Info.BTMinute) {
        			Info.BTMinute = v[j].tTour[0];
        			Info.BTSeconde = v[j].tTour[1];
        			vT = v[j].vId;
        		}

        		if (v[j].s1 < Info.BS1) {
        			Info.BS1 = v[j].s1;
        			v1 = v[j].vId;
        		}
        		if (v[j].s2 < Info.BS2) {
        			Info.BS2 = v[j].s2;
        			v2 = v[j].vId;
        		}
        		if (v[j].s3 < Info.BS3) {
        			Info.BS3 = v[j].s3;
        			v3 = v[j].vId;
        		}
	
		}
	
		Tuple r = {v[0].s1, v[0].s2, v[0].s3, v[0].tTour[0], v[0].tTour[1]}
	
	}

	struct Info t = getBest();

}
