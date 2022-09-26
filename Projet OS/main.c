#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, n, a ;
    time_t t;

    n = 3;

    srand((unsigned) time(&t));

    for (i = 0; i < n; i++) {
        a = rand()%(45-25+1)+25;
        printf("%d secondes\n", a  );

    }

    return (0);

}
