#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printFrames(int frames[], int numframes) 
{   
    for(int i=0; i<numframes; i++) {
        if(frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

int isPresent(int page, int frames[], int numframes)
{
    for(int i=0; i<numframes; i++) {
        if(frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void fifo(int pages[], int len, int numframes)
{
    int frames[100];
    for (int i = 0; i < numframes; i++)
    {
        frames[i] = -1;
    }

    int index = 0;
    int faults = 0;
    // algorithm
    printf("FIFO: \n");
    for (int i = 0; i < len; i++)
    {
        int page = pages[i];
        if (!isPresent(page, frames, numframes))
        {
            // fault
            printf(".....FAULT.....   Frames: ");
            frames[index] = page;
            index = (index + 1) % numframes;
            faults++;
            printFrames(frames, numframes);
        }
        else
        {
            // hit
            printf(".....HIT.....     Frames: ");
            printFrames(frames, numframes);
        }
    }

    printf("Page faults in FIFO: %d\n", faults);
}

void lru(int pages[], int len, int numframes) {
    int frames[100];
    for(int i=0; i<numframes; i++) {
        frames[i] = -1;
    }

    // track numframes-1 recently used pages
    int recentlyUsed[numframes-1];
    
    // algorithm
    int faults = 0;

    printf("\nLRU: \n");
    for(int i=0; i<len; i++) {
        int page = pages[i];

        if(!isPresent(page, frames, numframes)) {
            // fault
            printf(".....FAULT.....   Frames: ");
            faults ++;
            
            // check if empty frame exits
            int exists = 0;
            for(int j=0; j<numframes; j++) {
                if(frames[j] == -1) {
                    exists = 1;
                    frames[j] = page;
                    recentlyUsed[j] = page;
                    break;
                }
            }

            if(!exists) {
                // replace lru
                // find the lru
                for(int j=0; j<numframes; j++) {
                    if(!isPresent(frames[j], recentlyUsed, numframes-1)) {
                        // replace
                        frames[j] = page;
                        recentlyUsed[j] = page;
                    }
                }
            }

            printFrames(frames, numframes);
        } else {
            //hit
            printf(".....HIT.....     Frames: ");
            printFrames(frames, numframes);
        }
    }

    printf("Page faults in LRU: %d\n", faults);
}

void optimal(int pages[], int len, int numframes) {
    int frames[100];
    for(int i=0; i<numframes; i++) {
        frames[i] = -1;
    }   

    //algorithm
    int faults = 0;
    for(int i=0; i<len; i++) {
        int page = pages[i];

        if(!isPresent(page, frames, numframes)) {
            // fault
            printf(".....FAULT.....  Frames: ");
            faults ++;
            // check if empty frame exists
            int exist = 0;
            for(int j=0; j<numframes; j++) {
                if(frames[j] == -1) {
                    exist = 1;
                    // insert page
                    frames[j] = page;
                    break;
                }
            }

            if(!exist) {
                // replace victim (farthest)
                // find the farthest page
                int farthest = -1;
                for(int j=0; j<numframes; j++) {
                    int k;
                    for(k = i+1; k<len; k++) {
                        if(frames[j] == pages[k]) {
                            farthest = max(farthest, k);
                            break;
                        }
                    }
                    if(k >= len) {
                        //replace frames[j]
                        frames[j] = page;
                        break;
                    }
                }
                for(int j=0; j<numframes; j++) {
                    if(frames[j] == pages[farthest]) {
                        frames[j] = page;
                        break;
                    }
                }
            }
            printFrames(frames, numframes);

        } else {
            printf(".....HIT.....    Frames: ");
            printFrames(frames, numframes);
        }
    }
    printf("Page faults in Optimal: %d\n", faults);
}

int main(int argc, char *argv[])
{
    int len = atoi(argv[1]);
    int frames = atoi(argv[2]);

    int pages[100];
    srand(time(NULL));

    printf("Page Reference String: ");
    for (int i = 0; i < len; i++)
    {
        pages[i] = rand() % 10;
        printf("%d ", pages[i]);
    }
    printf("\n");

    fifo(pages, len, frames);
    lru(pages, len, frames);
    optimal(pages, len, frames);
    return 0;
}