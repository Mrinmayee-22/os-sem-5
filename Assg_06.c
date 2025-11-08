#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int i, j;

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input Max Matrix
    printf("Enter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Calculate Need Matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Safety Algorithm
    int finish[n], safeSeq[n], count = 0;
    for(i = 0; i < n; i++)
        finish[i] = 0;

    int found;
    while(count < n) {
        found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int flag = 1;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    for(j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for(i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    // Resource Request Algorithm
    int req_proc, request[m];
    printf("\nEnter process number for resource request (0 to %d): ", n-1);
    scanf("%d", &req_proc);
    printf("Enter resource request for process %d:\n", req_proc);
    for(j = 0; j < m; j++)
        scanf("%d", &request[j]);

    // Check if request <= need
    int can_grant = 1;
    for(j = 0; j < m; j++) {
        if(request[j] > need[req_proc][j]) {
            can_grant = 0;
            break;
        }
    }
    if(!can_grant) {
        printf("Error: Process has exceeded its maximum claim.\n");
        return 0;
    }

    // Check if request <= available
    for(j = 0; j < m; j++) {
        if(request[j] > avail[j]) {
            can_grant = 0;
            break;
        }
    }
    if(!can_grant) {
        printf("Resources are not available. Process must wait.\n");
        return 0;
    }

    // Pretend to allocate requested resources
    for(j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[req_proc][j] += request[j];
        need[req_proc][j] -= request[j];
    }

    // Safety check after allocation
    for(i = 0; i < n; i++)
        finish[i] = 0;
    count = 0;
    int avail_temp[m];
    for(j = 0; j < m; j++)
        avail_temp[j] = avail[j];

    while(count < n) {
        found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int flag = 1;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail_temp[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    for(j = 0; j < m; j++)
                        avail_temp[j] += alloc[i][j];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if(!found) {
            printf("After resource request, system is NOT in a safe state. Request cannot be granted.\n");
            return 0;
        }
    }
    printf("After resource request, system is STILL in a safe state. Request can be granted.\n");

    return 0;
}