#include <stdio.h>

#define MAX 10

typedef struct {
    int id;         
    int arrival;    
    int burst;      
    int priority;  
    int waiting;    
    int turnaround; 
    int completion; 
} Process;

void sort_by_arrival(Process arr[], int n) {
    int i, j;
    Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i].arrival > arr[j].arrival) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    Process q1[MAX], q2[MAX]; 
    int q1_count = 0, q2_count = 0;
    int total_time = 0, total_wait = 0, total_turnaround = 0;
    float avg_wait, avg_turnaround;

    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    Process processes[MAX];

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nEnter details for Process[%d]:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst);
        printf("Priority (Lower value = Higher priority): ");
        scanf("%d", &processes[i].priority);

        if (processes[i].priority <= 3) {
            q1[q1_count++] = processes[i]; 
        } else {
            q2[q2_count++] = processes[i]; 
        }
    }

    sort_by_arrival(q1, q1_count);
    sort_by_arrival(q2, q2_count);

    printf("\nExecuting Queue 1 (Higher Priority, FCFS):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < q1_count; i++) {
        if (total_time < q1[i].arrival)
            total_time = q1[i].arrival;  

        q1[i].waiting = total_time - q1[i].arrival;
        q1[i].turnaround = q1[i].waiting + q1[i].burst;
        q1[i].completion = total_time + q1[i].burst;
        total_wait += q1[i].waiting;
        total_turnaround += q1[i].turnaround;
        total_time += q1[i].burst;

        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                q1[i].id, q1[i].arrival, q1[i].burst, q1[i].completion, q1[i].waiting, q1[i].turnaround);
    }

    printf("\nExecuting Queue 2 (Lower Priority, FCFS):\n");
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < q2_count; i++) {
        if (total_time < q2[i].arrival)
            total_time = q2[i].arrival;  

        q2[i].waiting = total_time - q2[i].arrival;
        q2[i].turnaround = q2[i].waiting + q2[i].burst;
        q2[i].completion = total_time + q2[i].burst;
        total_wait += q2[i].waiting;
        total_turnaround += q2[i].turnaround;
        total_time += q2[i].burst;

        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                q2[i].id, q2[i].arrival, q2[i].burst, q2[i].completion, q2[i].waiting, q2[i].turnaround);
    }

    avg_wait = (float)total_wait / n;
    avg_turnaround = (float)total_turnaround / n;

    printf("\nAverage Waiting Time: %.2f", avg_wait);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}
