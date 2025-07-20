#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;

    pipe(fd);
    pid1 = fork();

    if (pid1 == 0) {
        write(fd[1], "HALLO!", 7);
        close(fd[1]);
    } else if (pid1 > 0) {
        pid2 = fork();
        
        if (pid2 == 0) {
            wait(&pid1);

            char str[7];
            read(fd[0], str, 7);
            printf("%s\n", str);
        }
    }
}
