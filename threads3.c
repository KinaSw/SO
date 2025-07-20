#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int g_number = 0;
pthread_mutex_t mutex_id;

void *print_array(void *arg) {
    pthread_mutex_lock(&mutex_id);

    int tmp;
    for (int i = 0; i < 10; i++) {
        tmp = g_number;
        tmp = tmp + 1;
        sleep(1);
        g_number = tmp;
    }

    pthread_mutex_unlock(&mutex_id);

    return 0;
}

int main() {
    pthread_t thread_id;

    if (pthread_mutex_init(&mutex_id, NULL)) { 
        perror("Error occured on pthread_mutex_init");
        return -1; 
    } 

    if (pthread_create(&thread_id, NULL, print_array, NULL)) {
        perror("Error occured on pthread_create");
        return -1;
    }

    pthread_mutex_lock(&mutex_id);
    for (int i = 0; i < 10; i++) {
        g_number++;
        sleep(1);
    }
    pthread_mutex_unlock(&mutex_id);

    if (pthread_join(thread_id, NULL)) {
        perror("Error occured on pthread_join");
        return -1;
    }
    pthread_mutex_destroy(&mutex_id);

    printf("Number = %d\n", g_number);

    return 0;
}
