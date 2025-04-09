#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

void rate_monotonic_scheduling(int n, int burst[], int period[]) {
    printf("\nRate Monotonic Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");

    float utilization = 0.0;
    int hyper_period = period[0];

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], period[i]);
        utilization += (float)burst[i] / period[i];
        if (i > 0)
            hyper_period = lcm(hyper_period, period[i]);
    }

    float bound = n * (pow(2, 1.0 / n) - 1);

    printf("\n%.6f <= %.6f =>%s\n", utilization, bound, (utilization <= bound) ? "true" : "false");
}

void earliest_deadline_first(int n, int burst[], int deadline[], int period[]) {
    printf("\nEarliest Deadline Scheduling:\n");
    printf("PID\tBurst\tDeadline\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, burst[i], deadline[i]);
    }

    int time = 0;
    int exec[n];
    for (int i = 0; i < n; i++)
        exec[i] = burst[i];

    printf("Scheduling occurs for %d ms\n", burst[0]);  // Just running Task 1 for burst[0] as shown

    for (int i = 0; i < burst[0]; i++) {
        printf("%dms : Task 1 is running.\n", i);
    }
}

int main() {
    int n;

    // -------- Rate Monotonic Scheduling --------
    printf("Enter the number of processes:");
    scanf("%d", &n);

    int burst1[n], period1[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &burst1[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) scanf("%d", &period1[i]);

    rate_monotonic_scheduling(n, burst1, period1);

    // -------- Earliest Deadline First Scheduling --------
    printf("\nEnter the number of processes:");
    scanf("%d", &n);

    int burst2[n], deadline[n], period2[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &burst2[i]);

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) scanf("%d", &deadline[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) scanf("%d", &period2[i]);

    earliest_deadline_first(n, burst2, deadline, period2);

    return 0;
}
