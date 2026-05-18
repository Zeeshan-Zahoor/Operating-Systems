#include <stdio.h>
#include <stdlib.h>

int pid[100], at[100], bt[100], pr[100], completed[100] = {0}, rem_bt[100];
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

                // to avoid conflict in other algorithms
                temp = pr[j];
                pr[j] = pr[j+1];
                pr[j+1] = temp;
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
    printf("FCFS Scheduling: \n");
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

void priority(int n) {
    for(int i = 0; i < n; i++) {
        completed[i] = 0;
    }   
   int current_time = 0;
   int finished = 0;

   while(finished < n) {

        int selected = -1;
        int highest_pr = -1;

        //search for highest priority processes
        for(int i=0; i<n; i++) {
            if(at[i] <= current_time && completed[i] == 0) {
                if(pr[i] > highest_pr) {
                    highest_pr = pr[i];
                    selected = i;
                }
            }
        }

        //cpu idle case
        if(selected == -1) {
            current_time ++;
            continue;
        }

        // execute the process completely
        current_time += bt[selected];
        ct[selected] = current_time;
        tat[selected] = ct[selected] - at[selected];
        wt[selected] = tat[selected] - bt[selected];

        completed[selected] = 1;
        finished ++;
   }

   // output
    float avg_wt = 0;
    printf("\nPriority Scheduling: \n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
            pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]
        );

        avg_wt += wt[i];
    }
    avg_wt /= n;

    printf("Average waiting time in Priority Scheduling: %.2f\n", avg_wt);
   
}

void srtf(int n) {
    for(int i = 0; i < n; i++) {

        ct[i] = 0;
        tat[i] = 0;
        wt[i] = 0;
    }

    // copy the burst times
    for(int i=0; i<n; i++) {
        rem_bt[i] = bt[i];
    }

    int finished = 0;
    int current_time = 0;
    
    while(finished < n) {
        
        int selected = -1;
        int min_remaining_bt = 9999;

        for(int i=0; i<n; i++) {
            if(at[i] <= current_time && rem_bt[i] > 0) {
                if(min_remaining_bt > rem_bt[i]) {
                    min_remaining_bt = rem_bt[i];
                    selected = i;
                }
            }
        }

        // cpu idle case
        if(selected == -1) {
            current_time ++;
            continue;
        }

        // execute selected process for one unit time

        rem_bt[selected] --;
        current_time ++;

        // if process finished
        if(rem_bt[selected] == 0) {
            // calculate times
            ct[selected] = current_time;
            tat[selected] = ct[selected] - at[selected];
            wt[selected] = tat[selected] - bt[selected];
            finished ++;
        }

    }

    // output
    float avg_wt = 0;
    printf("\nSRTF Scheduling: \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
            pid[i], at[i], bt[i], ct[i], tat[i], wt[i]
        );
        avg_wt += wt[i];
    }
    avg_wt /= n;
    printf("The Average waiting time with SRTF: %.2f\n", avg_wt);
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
        printf("Priority: ");
        scanf("%d", &pr[i]);
    }


    fcfs(n);
    priority(n);
    srtf(n);

    return 0;
}