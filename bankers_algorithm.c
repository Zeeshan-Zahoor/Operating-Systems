#include <stdio.h>

int main() {

    int n, m;
    int alloc[100][100];
    int max[100][100];
    int need[100][100];
    int avail[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    printf("Enter the allocation matrix: \n");
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the maximum need matrix: ");
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available vector: ");
    for(int i=0; i<m; i++) {
        scanf("%d", &avail[i]);
    }


    // calculate need matrix
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Print the current need matrix;
    printf("Current Need: \n");
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // banker's algorithm
    int count = 0;
    int finished[100] = {0};
    int safeSeq[100];

    while(count < n) {

        int found = 0;
        for(int i=0; i<n; i++) {
            if(finished[i] == 0) {
                int possible = 1;
                // check if the process can execute with available resources
                for(int j=0; j<m; j++) {
                    if(need[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                // if process can execute
                if(possible) {
                    for(int j=0; j<m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;
                    finished[i] = 1;
                    count ++;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            printf("The System is NOT in safe state..\n");
            return 0;
        }
    }

    printf("The System is in SAFE state..\nSafe Sequence: ");
    for(int i=0; i<n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    // ---------------------------------------------------
    // RESOURCE REQUEST PART
    // ---------------------------------------------------


    int p;
    int request[100];

    printf("\nEnter process number making request: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");

    for(int i = 0; i < m; i++) {

        scanf("%d", &request[i]);
    }

    // STEP 1: Check Request <= Need

    for(int i = 0; i < m; i++) {

        if(request[i] > need[p][i]) {

            printf("\nError: Process exceeded maximum claim.\n");

            return 0;
        }
    }

    // STEP 2: Check Request <= Available

    for(int i = 0; i < m; i++) {

        if(request[i] > avail[i]) {

            printf("\nResources not available. Process must wait.\n");

            return 0;
        }
    }

    // STEP 3: Pretend Allocation

    for(int i = 0; i < m; i++) {

        avail[i] -= request[i];

        alloc[p][i] += request[i];

        need[p][i] -= request[i];
    }

    // RESET finish array for safety check again

    for(int i = 0; i < n; i++) {

        finished[i] = 0;
    }

    count = 0;

    // RUN SAFETY ALGORITHM AGAIN

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finished[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(need[i][j] > avail[j]) {

                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {

                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;

                    finished[i] = 1;

                    count++;

                    found = 1;
                }
            }
        }

        // request causes unsafe state

        if(found == 0) {

            printf("\nRequest CANNOT be granted.\n");
            printf("System will enter unsafe state.\n");

            return 0;
        }
    }

    // request safe

    printf("\nRequest CAN be granted.\n");

    printf("New Safe Sequence: ");

    for(int i = 0; i < n; i++) {

        printf("P%d ", safeSeq[i]);
    }

    printf("\n");


    return 0;
}