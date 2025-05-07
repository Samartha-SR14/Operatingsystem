#include <stdio.h>

static int mark[20];
int i, j, np, nr;

int main() {
    int alloc[10][10], request[10][10], avail[10], r[10], w[10], need[10][10], safe_sequence[10];
    int finish[10], count = 0;

    printf("\nEnter the number of processes: ");
    scanf("%d", &np);
    printf("\nEnter the number of resources: ");
    scanf("%d", &nr);

    for (i = 0; i < nr; i++) {
        printf("\nTotal amount of resource R%d: ", i + 1);
        scanf("%d", &r[i]);
    }

    printf("\nEnter the request matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &request[i][j]);

    printf("\nEnter the allocation matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);

    // Calculate available resources
    for (j = 0; j < nr; j++) {
        avail[j] = r[j];
        for (i = 0; i < np; i++) {
            avail[j] -= alloc[i][j];
        }
    }

    // Calculate need matrix
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            need[i][j] = request[i][j] - alloc[i][j];

    // Initialize work with available resources
    for (j = 0; j < nr; j++)
        w[j] = avail[j];

    // Initialize finish array
    for (i = 0; i < np; i++)
        finish[i] = 0;

    // Safety algorithm
    while (count < np) {
        int found = 0;
        for (i = 0; i < np; i++) {
            if (!finish[i]) {
                int canBeProcessed = 1;
                for (j = 0; j < nr; j++) {
                    if (need[i][j] > w[j]) {
                        canBeProcessed = 0;
                        break;
                    }
                }
                if (canBeProcessed) {
                    for (j = 0; j < nr; j++)
                        w[j] += alloc[i][j];
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("\nDeadlock detected\n");
            return 0;
        }
    }

    printf("\nSafe sequence: ");
    for (i = 0; i < np; i++)
        printf("P%d ", safe_sequence[i]);
    printf("\n");

    return 0;
}
