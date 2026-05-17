#include <stdio.h>
#include <unistd.h>

int main () {
    pid_t  pid;

    pid = fork();

    if(pid == 0) {
        // child process
        printf("This is Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        sleep(20);
    } 

    if(pid > 0) {
        // parent process
        printf("This is Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        sleep(20);
    }

    if(pid < 0) {
        printf("Fork Failed!\n");
    }

    return 0;
}