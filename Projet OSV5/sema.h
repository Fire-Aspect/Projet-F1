#include <semaphore.h>

sem_t sem;
int counter = 0;

// initialisation des sémaphores

void init_semaphore() {
    sem_init(&sem, 0, 1);
}
