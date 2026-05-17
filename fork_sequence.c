#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid;
    pid = fork();

    if(pid == 0) {
        printf("PCCSL407 ");
    }

    if(pid > 0) {
        printf("Operating Systems Lab \n");
        wait(NULL);
    }

    printf("\n");
    return 0;
}