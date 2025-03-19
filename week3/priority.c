#include <stdio.h>

#define MAX 100

void priorityPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], rem_bt[n], is_completed[n];
    int time = 0, completed = 0, min_priority, index;

    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        is_completed[i] = 0;
    }

    while (completed < n) {
        min_priority = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority && rem_bt[i] > 0) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            rem_bt[index]--;
            time++;

            if (rem_bt[index] == 0) {
                ct[index] = time;
                is_completed[index] = 1;
                completed++;
            }
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

void priorityNonPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], is_completed[n], rem_bt[n];
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        rem_bt[i] = bt[i];
    }

    while (completed < n) {
        int min_priority = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            time += bt[index];
            ct[index] = time;
            is_completed[index] = 1;
            completed++;
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, and Priority P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Preemptive Priority Scheduling\n");
    printf("2. Non-Preemptive Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        priorityPreemptive(n, at, bt, pr);
    } else if (choice == 2) {
        priorityNonPreemptive(n, at, bt, pr);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
