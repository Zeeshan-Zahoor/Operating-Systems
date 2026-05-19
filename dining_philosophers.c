#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5

sem_t forks[N];
sem_t room;

void * philosopher(void* arg) {
    int id = *(int*)arg;

    while(1) {
        // thinking
        printf("Philosospher %d is Thinking...\n", id);
        sleep(1);

        //enter the room
        sem_wait(&room);

        //pick up left fork
        sem_wait(&forks[id]);
        
        //pick up right fork
        sem_wait(&forks[(id+1) % N]);

        // Eating
        printf("Philosopher %d is Eating..\n", id);
        sleep(2);

        // release forks
        sem_post(&forks[id]);
        sem_post(&forks[(id+1) % N]);

        //leave the room
        sem_post(&room);

    }
    return NULL;
}

int main () {

    pthread_t p[N];
    int ids[N];

    //initialize semaphores
    sem_init(&room, 0, N-1);  // allow only 4
    for(int i=0; i<N; i++) {
        sem_init(&forks[i], 0, 1); 
    }

    // create threads
    for(int i=0; i<N; i++) {
        ids[i] = i;
        pthread_create(&p[i], NULL, philosopher, &ids[i]);
    }

    // join threads 
    for(int i=0; i<N; i++) {
        pthread_join(p[i], NULL);
    }
    
    return 0;
}