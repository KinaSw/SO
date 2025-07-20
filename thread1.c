#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* thread_fun(void *arg) {
    int* arr = (int*)arg;
    for(int i = 0 ; i < 10 ; i++) {
        printf("%d\n", arr[i]);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int arr[10];
    for(int i = 0 ; i < 10 ; i++) {
        arr[i] = i + 11;
    }
    if(pthread_create(&thread, NULL, thread_fun, (void*)arr)) {
        perror("Error occured in line 28: pthread_create");
        return -1;
    }
    if(pthread_join(thread, NULL)) {
        perror("Error in line 32: pthread_join");
        return -1;
    }
    return 0;
}
