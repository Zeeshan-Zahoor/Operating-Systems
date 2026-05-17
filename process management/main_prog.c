#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid;

    pid = fork();

    if(pid == 0) {
        char * args[] = {"./myadder", "10", "20", NULL};

        execvp(args[0], args);

        printf("Exec Failed!\n");
    } 

    if(pid > 0) {
        printf("Parent Process. \n");
    }

    printf("\n");
    return 0;
}