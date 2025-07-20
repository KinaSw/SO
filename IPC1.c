#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Definiowanie struktury komunikatu
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generowanie unikalnego klucza
    key = ftok("progfile", 65);

    // Tworzenie kolejki komunikatów
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Wysyłanie komunikatu
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello, this is a message.");

    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message.msg_text);

    // Odbieranie komunikatu
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Message received: %s\n", message.msg_text);

    // Usuwanie kolejki komunikatów
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
