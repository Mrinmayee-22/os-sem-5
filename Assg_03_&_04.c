#include <stdio.h>

void printResults(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[], float avg_wt, float avg_tat) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);
}

void printGantt(int gantt_pid[], int gantt_start[], int gantt_end[], int g_count) {
    printf("\n\nGantt Chart:\n");

    // Club consecutive same processes
    int final_pid[200], final_start[200], final_end[200], count = 0;

    final_pid[count] = gantt_pid[0];
    final_start[count] = gantt_start[0];
    final_end[count] = gantt_end[0];

    for (int i = 1; i < g_count; i++) {
        if (gantt_pid[i] == final_pid[count]) {
            final_end[count] = gantt_end[i]; // Extend current block
        } else {
            count++;
            final_pid[count] = gantt_pid[i];
            final_start[count] = gantt_start[i];
            final_end[count] = gantt_end[i];
        }
    }
    count++;

    // Print top border
    printf(" ");
    for (int i = 0; i < count; i++) printf(" -------");
    printf("\n|");

    // Print process labels
    for (int i = 0; i < count; i++) {
        if (final_pid[i] == -1) printf(" Idle  |");
        else printf("  P%-2d  |", final_pid[i]);
    }

    // Print bottom border
    printf("\n ");
    for (int i = 0; i < count; i++) printf(" -------");
    printf("\n");

    // Print timeline
    printf("%d", final_start[0]);
    for (int i = 0; i < count; i++) {
        printf("      %d", final_end[i]);
    }
    printf("\n");
}

void printSortedTable(int n, int pid[], int at[], int bt[]) {
    printf("\nSorted Input (by Arrival Time):\n");
    printf("Process\tAT\tBT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\n", pid[i], at[i], bt[i]);
    }
}

// ----- SJF Non-Preemptive -----
void sjf_nonpreemptive(int n, int pid[], int at[], int bt[]) {
    int ct[n], tat[n], wt[n], completed[n];
    float avg_wt=0, avg_tat=0;
    int time=0, count=0;

    for (int i=0; i<n; i++) completed[i] = 0;

    int gantt_pid[2*n], gantt_start[2*n], gantt_end[2*n], g_count=0;

    while (count<n) {
        int idx=-1, min_bt=9999;
        for (int i=0;i<n;i++){
            if (!completed[i] && at[i]<=time && bt[i]<min_bt){
                min_bt=bt[i]; idx=i;
            }
        }
        if (idx==-1){
            gantt_pid[g_count]=-1; gantt_start[g_count]=time; time++; gantt_end[g_count++]=time;
        } else {
            gantt_pid[g_count]=pid[idx]; gantt_start[g_count]=time;
            time+=bt[idx]; gantt_end[g_count++]=time;
            ct[idx]=time; tat[idx]=ct[idx]-at[idx]; wt[idx]=tat[idx]-bt[idx];
            avg_wt+=wt[idx]; avg_tat+=tat[idx]; completed[idx]=1; count++;
        }
    }
    printResults(n, pid, at, bt, ct, tat, wt, avg_wt, avg_tat);
    printGantt(gantt_pid, gantt_start, gantt_end, g_count);
}

// ----- SRTF Preemptive -----
void srtf_preemptive(int n, int pid[], int at[], int bt[]) {
    int rt[n], ct[n], tat[n], wt[n], done[n];
    int completed=0, time=0;
    float avg_wt=0, avg_tat=0;

    for (int i=0;i<n;i++) { rt[i]=bt[i]; done[i]=0; }

    int gantt_pid[100], gantt_start[100], gantt_end[100], g_count=0;

    while (completed<n){
        int idx=-1, min_rt=9999;
        for (int i=0;i<n;i++){
            if (at[i]<=time && !done[i] && rt[i]<min_rt){
                min_rt=rt[i]; idx=i;
            }
        }
        if (idx==-1){
            gantt_pid[g_count]=-1; gantt_start[g_count]=time; time++; gantt_end[g_count++]=time;
        } else {
            gantt_pid[g_count]=pid[idx]; gantt_start[g_count]=time;
            rt[idx]--; time++; gantt_end[g_count++]=time;
            if (rt[idx]==0){
                ct[idx]=time; tat[idx]=ct[idx]-at[idx]; wt[idx]=tat[idx]-bt[idx];
                avg_wt+=wt[idx]; avg_tat+=tat[idx]; done[idx]=1; completed++;
            }
        }
    }
    printResults(n, pid, at, bt, ct, tat, wt, avg_wt, avg_tat);
    printGantt(gantt_pid, gantt_start, gantt_end, g_count);
}

// ----- FCFS Non-Preemptive -----
void fcfs_nonpreemptive(int n, int pid[], int at[], int bt[]) {
    int ct[n], tat[n], wt[n];
    float avg_wt=0, avg_tat=0;
    int gantt_pid[n], gantt_start[n], gantt_end[n], time=0;

    for (int i=0;i<n;i++){
        if (time<at[i]) time=at[i];
        gantt_pid[i]=pid[i]; gantt_start[i]=time; time+=bt[i]; gantt_end[i]=time;
        ct[i]=time; tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i];
        avg_wt+=wt[i]; avg_tat+=tat[i];
    }
    printResults(n, pid, at, bt, ct, tat, wt, avg_wt, avg_tat);
    printGantt(gantt_pid, gantt_start, gantt_end, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n];

    for (int i=0;i<n;i++){
        pid[i]=i+1;
        printf("\nEnter Arrival Time of P%d: ", pid[i]); scanf("%d",&at[i]);
        printf("Enter Burst Time of P%d: ", pid[i]); scanf("%d",&bt[i]);
    }

    // Sort by arrival time
    for (int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (at[i]>at[j]){
                int temp=at[i]; at[i]=at[j]; at[j]=temp;
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=pid[i]; pid[i]=pid[j]; pid[j]=temp;
            }
        }
    }

    printSortedTable(n, pid, at, bt);

    int choice;
    do {
        printf("\n\nChoose Scheduling Algorithm:\n");
        printf("1. SJF Non-Preemptive\n");
        printf("2. SRTF Preemptive\n");
        printf("3. FCFS Non-Preemptive\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: sjf_nonpreemptive(n, pid, at, bt); break;
            case 2: srtf_preemptive(n, pid, at, bt); break;
            case 3: fcfs_nonpreemptive(n, pid, at, bt); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice!=4);

    return 0;
}


/* PS D:\vs code\sem 5\os> gcc Assg_03.c -o Assg_03.exe
>> 
PS D:\vs code\sem 5\os> .\Assg_03.exe
>> 
Enter the number of processes: 4

Enter Arrival Time of P1: 0
Enter Burst Time of P1: 7

Enter Arrival Time of P2: 2
Enter Burst Time of P2: 4

Enter Arrival Time of P3: 4
Enter Burst Time of P3: 1

Enter Arrival Time of P4: 5
Enter Burst Time of P4: 7

Sorted Input (by Arrival Time):
Process AT      BT
P1      0       7
P2      2       4
P3      4       1
P4      5       7


Choose Scheduling Algorithm:
1. SJF Non-Preemptive
2. SRTF Preemptive
3. FCFS Non-Preemptive
4. Exit
Enter choice: 1

Process AT      BT      CT      TAT     WT
P1      0       7       7       7       0
P2      2       4       12      10      6
P3      4       1       8       4       3
P4      5       7       19      14      7

Average Waiting Time: 4.00
Average Turnaround Time: 8.75


Gantt Chart:
  ------- ------- ------- -------
|  P1   |  P3   |  P2   |  P4   |
  ------- ------- ------- -------
0      7      8      12      19


Choose Scheduling Algorithm:
1. SJF Non-Preemptive
2. SRTF Preemptive
3. FCFS Non-Preemptive
4. Exit
Enter choice: 2

Process AT      BT      CT      TAT     WT
P1      0       7       12      12      5
P2      2       4       7       5       1
P3      4       1       5       1       0
P4      5       7       19      14      7

Average Waiting Time: 3.25
Average Turnaround Time: 8.00


Gantt Chart:
  ------- ------- ------- ------- ------- -------
|  P1   |  P2   |  P3   |  P2   |  P1   |  P4   |
  ------- ------- ------- ------- ------- -------
0      2      4      5      7      12      19


Choose Scheduling Algorithm:
1. SJF Non-Preemptive
2. SRTF Preemptive
3. FCFS Non-Preemptive
4. Exit
Enter choice: 3

Process AT      BT      CT      TAT     WT
P1      0       7       7       7       0
P2      2       4       11      9       5
P3      4       1       12      8       7
P4      5       7       19      14      7

Average Waiting Time: 4.75
Average Turnaround Time: 9.50


Gantt Chart:
  ------- ------- ------- -------
|  P1   |  P2   |  P3   |  P4   |
  ------- ------- ------- -------
0      7      11      12      19


Choose Scheduling Algorithm:
1. SJF Non-Preemptive
2. SRTF Preemptive
3. FCFS Non-Preemptive
4. Exit
Enter choice: 4
Exiting...
PS D:\vs code\sem 5\os> */