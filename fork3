#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char *fifoPath = "/tmp/fifo";
    pid_t pid1, pid2;

    mkfifo(fifoPath, 0666);
    pid1 = fork();

    if (pid1 == 0) {
        int fd = open(fifoPath, O_WRONLY);
        write(fd, "HALLO!", 7);
        close(fd);
    } else if (pid1 > 0) {
        pid2 = fork();
        
        if (pid2 == 0) {
            wait(&pid1);

            char str[7];

            int fd = open(fifoPath, O_RDONLY);
            read(fd, str, 7);
            printf("%s\n", str);
            close(fd);
        }
    }
}
