#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a, b, sum;

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    sum = a + b;

    printf("The Sum is:  %d\n", sum);

    return 0;
}