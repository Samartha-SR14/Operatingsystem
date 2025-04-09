#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int period;
    int deadline;
    int remaining_bt;
};

struct Process p[5];
int n = 5;
int time = 0;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int calculate_lcm_of_periods() {
    int result = p[0].period;
    for (int i = 1; i < n; i++) {
        result = (result * p[i].period) / gcd(result, p[i].period);
    }
    return result;
}

void rate_monotonic(int sim_time) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = 0;
    }

    printf("\n--- Rate Monotonic Scheduling ---\n");
    time = 0;

    while (time < sim_time) {
        int idx = -1;
        int min_period = 9999;

        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_bt = p[i].burst;
            }
            if (p[i].remaining_bt > 0 && p[i].period < min_period) {
                min_period = p[i].period;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("Time %2d: Task %d\n", time, p[idx].pid);
            p[idx].remaining_bt--;
        } else {
            printf("Time %2d: Idle\n", time);
        }

        time++;
    }
}

void earliest_deadline_first(int sim_time) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = 0;
        p[i].deadline = p[i].period;
    }

    printf("\n--- Earliest Deadline First Scheduling ---\n");
    time = 0;

    while (time < sim_time) {
        int idx = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_bt = p[i].burst;
                p[i].deadline = time + p[i].period;
            }
            if (p[i].remaining_bt > 0 && p[i].deadline < min_deadline) {
                min_deadline = p[i].deadline;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("Time %2d: Task %d\n", time, p[idx].pid);
            p[idx].remaining_bt--;
        } else {
            printf("Time %2d: Idle\n", time);
        }

        time++;
    }
}

void main() {
    printf("Enter Arrival Time, Burst Time, Period for 5 processes:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst);
        printf("Process %d Period: ", p[i].pid);
        scanf("%d", &p[i].period);
    }

    int sim_time = calculate_lcm_of_periods();
    printf("\nSimulation Time (LCM of periods): %d\n", sim_time);

    rate_monotonic(sim_time);
    earliest_deadline_first(sim_time);
}
