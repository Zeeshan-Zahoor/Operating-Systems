#include <stdio.h>
#include <stdlib.h>

int pid[100], at[100], bt[100];
int tat[100], ct[100], wt[100];

void fcfs(int n) {
    // sort according to arrival time
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(at[j] > at[j+1]) {
                // swap arrival time
                int temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                // swap pid
                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;

                // swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j+1] = temp;
            }
        }
    }

    int current_time = 0;

    for(int i=0; i<n; i++) {
        // CPU idle case
        if(current_time < at[i]) {
            current_time = at[i];
        }

        current_time += bt[i];

        // calculate times
        ct[i] = current_time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    } 

    // output
    float avg_wt = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            pid[i], at[i], bt[i], ct[i], tat[i], wt[i]
        );

        avg_wt += wt[i];
    }
    avg_wt /= n;

    printf("Average waiting time in FCFS: %.2f\n", avg_wt);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    //input
    for(int i=0; i<n; i++) {
        pid[i] = i + 1;
        printf("Process P%d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }


    fcfs(n);
    return 0;
}