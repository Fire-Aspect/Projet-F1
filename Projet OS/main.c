#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int i, n, a ;

    n = 3;

    srand(time(0));

    for (i = 0; i < n; i++) {
        a = rand()%(45-25+1)+25;
        printf("%d secondes\n", a  );

    }

    return (0);

}
