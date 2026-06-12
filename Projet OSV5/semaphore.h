//Sémaphores System V — mutex binaire pour protéger array[20] (meilleurs temps globaux)

#ifndef PROJET_FORMULE_1_SEMAPHORE_H
#define PROJET_FORMULE_1_SEMAPHORE_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define SEM_KEY 70  // clé différente de la mémoire partagée (69)

// Opération P : attendre (verrouiller)
void sem_wait_mutex(int semid) {
    struct sembuf op = {0, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop wait");
        exit(-1);
    }
}

// Opération V : signaler (déverrouiller)
void sem_signal_mutex(int semid) {
    struct sembuf op = {0, +1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop signal");
        exit(-1);
    }
}

// Créer et initialiser le sémaphore à 1 (mutex libre)
int sem_create() {
    // Détruire un éventuel sémaphore orphelin du crash précédent
    int old = semget(SEM_KEY, 1, 0666);
    if (old != -1) semctl(old, 0, IPC_RMID);

    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(-1);
    }
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl SETVAL");
        exit(-1);
    }
    return semid;
}

// Détruire le sémaphore
void sem_destroy(int semid) {
    semctl(semid, 0, IPC_RMID);
}

#endif //PROJET_FORMULE_1_SEMAPHORE_H
