#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main () {
    time_t t;

    time(&t);

    printf("Current time: %s\n", ctime(&t));

    sleep(20);

    return 0;
}