#include<stdio.h>
#include <unistd.h>

    int timeLimiter() {

        for (int i = 0; i < 60; i++) {
            sleep(1);
            printf("%d\n", i);

        }

    }

    timeLimiter();
