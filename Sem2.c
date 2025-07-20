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

// Funkcje do operacji na semaforach
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

    // Dołączenie segmentu pamięci współdzielonej
    data = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (data == (struct shared_memory *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Odczytywanie danych z pamięci współdzielonej
    while (1) {
        sem_lock(semid);
        if (strcmp(data->message, "CIEPLO") == 0 || strcmp(data->message, "ZIMNO") == 0) {
            printf("Received: %s\n", data->message);
        } else {
            printf("Error: Invalid message '%s'\n", data->message);
        }
        sem_unlock(semid);
        sleep(1);
    }

    // Odłączenie segmentu pamięci współdzielonej
    shmdt(data);

    return 0;
}
