#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Rozmiar pamięci współdzielonej

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generowanie unikalnego klucza
    key = ftok("shmfile", 65);

    // Tworzenie segmentu pamięci współdzielonej
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Dołączenie segmentu pamięci współdzielonej
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Wysyłanie naprzemiennie "CIEPŁO" i "ZIMNO"
    while (1) {
        strcpy(data, "CIEPLO");
        sleep(1);
        strcpy(data, "ZIMNO");
        sleep(1);
    }

    // Odłączenie segmentu pamięci współdzielonej
    shmdt(data);

    return 0;
}
