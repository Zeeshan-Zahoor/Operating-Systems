#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex;
sem_t mutex2;
sem_t wrt;
sem_t readTry;

int readCount = 0;
int writeCount = 0;

void* reader(void *arg) {

    int id = *(int*)arg;

    //check if reader is allowed
    sem_wait(&readTry);

    sem_wait(&mutex);
    readCount++;
    if(readCount == 1) {
        sem_wait(&wrt);
    }

    sem_post(&mutex);

    sem_post(&readTry);

    // CS 
    printf("Reader %d is Reading..\n", id);
    sleep(2);

    // exit CS

    sem_wait(&mutex);
    readCount--;
    if(readCount == 0) {
        sem_post(&wrt);
    }

    sem_post(&mutex);

    return NULL;
}

void* writer(void *arg) {
    int id = *(int*)arg;

    sem_wait(&mutex2);
    writeCount ++;
    if(writeCount == 1) {
        sem_wait(&readTry);
    }
    sem_post(&mutex2);

    sem_wait(&wrt);
    // CS
    printf("Writer %d is Writing...\n", id);
    sleep(2);
    //exit CS

    sem_post(&wrt);

    sem_wait(&mutex2);
    writeCount--;
    if(writeCount == 0) {
        sem_post(&readTry);
    }
    sem_post(&mutex2);

    return NULL;
}

int main() {

    pthread_t r[3], w[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    // initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    //create reader threads
    for(int i=0; i<3; i++) {
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }

    //create writer threads
    for(int i=0; i<2; i++) {
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    //wait for readers
    for(int i=0; i<3; i++) {
        pthread_join(r[i], NULL);
    }

    //wait for writers
    for(int i=0; i<2; i++) {
        pthread_join(w[i], NULL);
    }


    //destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}