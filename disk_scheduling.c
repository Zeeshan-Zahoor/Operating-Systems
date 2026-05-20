#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int requests[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
}

void sstf(int requests[], int n, int head)
{

    int visited[100] = {0};

    int movement = 0;
    int current = head;
    printf("\n ---------SSTF--------- ");
    printf("\nService Sequence: ");
    for (int i = 0; i < n; i++)
    {
        int minDist = 99999;
        int index = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int dist = abs(current - requests[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    index = j;
                }
            }
        }
        visited[index] = 1;
        movement += abs(current - requests[index]);
        current = requests[index];
        printf("%d ", requests[index]);
    }

    printf("\nHead Movement in SSTF: %d\n", movement);
}

void look(int requests[], int n, int head) {

    int arr[100];
    for(int i=0; i<n; i++) {
        arr[i] = requests[i];
    }
    // sort arr
    sort(arr, n);

    int movement = 0;
    int current = head;

    printf("\n---------LOOK---------\n");
    printf("Service sequence: ");
    //move right first
    for(int i=0; i<n; i++) {
        if(arr[i] >= head) {
            movement += abs(current - arr[i]);
            current = arr[i];
            printf("%d ", current);
        }
    }

    // reverse direction
    for(int i=n-1; i>=0; i--) {
        if(arr[i] < head) {
            movement += abs(current - arr[i]);
            current = arr[i];
            printf("%d ", current);
        }
    }

    printf("\nHead Movement in LOOK: %d\n", movement);
}

void cscan(int requests[], int n, int head) {
    int arr[100];
    for(int i=0; i<n; i++) {
        arr[i] = requests[i];
    }

    sort(arr, n);

    int movement = 0;
    int current = head;

    printf("\n---------C-SCAN---------\n");
    printf("Service sequence: ");
    // move right
    for(int i=0; i<n; i++) {
        if(arr[i] >= head) {
            movement += abs(current - arr[i]);
            current = arr[i];
            printf("%d ", current);
        }
    }

    // go till end
    movement += abs(current - 4999);
    current = 4999;
    printf("%d ", current);
    // jump to beginning
    movement += 4999;
    current = 0;
    printf("%d ", current);

    // continue sevicing
    for(int i=0; i<n; i++) {
        if(arr[i] < head) {
            movement += abs(current - arr[i]);
            current = arr[i];
            printf("%d ", current);
        }
    }

    printf("\nHead Movement in C-SCAN: %d\n", movement);
}

int main(int argc, char *argv[])
{
    int head = atoi(argv[1]);

    int requests[10];
    srand(time(NULL));
    printf("Requests: ");
    for (int i = 0; i < 10; i++)
    {
        requests[i] = rand() % 5000;
        printf("%d ", requests[i]);
    }

    sstf(requests, 10, head);
    look(requests, 10, head);
    cscan(requests, 10, head);

    return 0;
}