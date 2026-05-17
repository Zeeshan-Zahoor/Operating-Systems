#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

int main() {
    
    int fd[2];
    pipe(fd);

    int a = 5, b = 24, c = 9;

    int b_square;
    int four_ac;

    pid_t pid;
    pid = fork();

    if(pid > 0) {
        // parent
        b_square = b * b;
        read(fd[0], &four_ac, sizeof(four_ac));

        float result = sqrt(b_square - four_ac);
        printf("Result = %2f\n", result);

    } else if (pid == 0) {
        // child 
        four_ac = 4 * a * c;
        write(fd[1], &four_ac, sizeof(four_ac));

    } else {
        printf("Fork Failed. \n");
    }

    return 0;
}