#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Rozmiar pamięci współdzielonej

// Struktura pamięci współdzielonej
struct shared_memory {
    char message[100];
};

// Funckje do operacji na semaforach
void sem_lock(int semid) {
    struct sembuf sb = {0, -1, 0}; // Blokowanie semafora
    semop(semid, &sb, 1);
}

void sem_unlock(int semid) {
    struct sembuf sb = {0, 1, 0}; // Odblokowywanie semafora
    semop(semid, &sb, 1);
}

int main() {
    key_t key;
    int shmid, semid;
    struct shared_memory *data;

    // Generowanie unikalnego klucza
    key = ftok("shmfile", 65);

    // Tworzenie segmentu pamięci współdzielonej
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Tworzenie semafora
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Ustawienie początkowej wartości semafora na 1 (dostępny)
    semctl(semid, 0, SETVAL, 1);

    // Dołączenie segmentu pamięci współdzielonej
    data = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (data == (struct shared_memory *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Wysyłanie naprzemiennie "CIEPŁO" i "ZIMNO"
    while (1) {
        sem_lock(semid);
        strcpy(data->message, "CIEPLO");
        sem_unlock(semid);
        sleep(1);

        sem_lock(semid);
        strcpy(data->message, "ZIMNO");
        sem_unlock(semid);
        sleep(1);
    }

    // Odłączenie segmentu pamięci współdzielonej
    shmdt(data);

    return 0;
}
