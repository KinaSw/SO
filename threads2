#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int g_number = 0;

void *print_array(void *new) {
    int tmp;
    for (int i = 0; i < 10; i++) {
        tmp = g_number;
        tmp = tmp + 1;
        sleep(1);
        g_number = tmp;
    }
    printf("\n");

    return 0;
}

int main() {

    pthread_t thread_id;

    if (pthread_create(&thread_id, NULL, print_array, NULL)) {
        perror("Error occured on pthread_create");
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        g_number++;
        sleep(1);
    }

    if (pthread_join(thread_id, NULL)) {
        perror("Error occured on pthread_join");
        return -1;
    }

    printf("Number = %d\n", g_number);

    return 0;
}
