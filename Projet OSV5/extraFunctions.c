#include<stdio.h>
#include <unistd.h>

int main(){

    // Multiprocessing - creating multiple childs
    for(int i=0;i<5;i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            exit(0);
        }
    }
    for(int i=0;i<5;i++) // loop will run n times (n=5)
        wait(NULL);

}
int main(){
    int timeLimiter() {

        for (int i = 0; i < 60; i++) {
            sleep(1);
            printf("%d\n", i);

        }

    }

    timeLimiter();

    return 0;
}