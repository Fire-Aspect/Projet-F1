#include <stdio.h>
#include <stdlib.h>
#include "tri.h"
#include <time.h>
#include "faireTourner.h"


int main() {

    srand(time(0));

    faireTourner(10,1);

    return 0;
}
