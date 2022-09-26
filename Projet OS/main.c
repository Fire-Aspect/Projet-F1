#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, n, a ;
    time_t t;

    n = 5;

    srand((unsigned) time(&t));

    for (i = 0; i < n; i++) {
        a = rand()*3600/RAND_MAX+1;
        printf("%d minutes,%d secondes\n", a/60, a%60  );

    }

    return (0);

}