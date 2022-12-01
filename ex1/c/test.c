#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_sorted(int * sorted, size_t len, int value) {
    for (int i = 0; i < len; i++) {
        if (sorted[i] < value) {
            if (len - i > 1) {
                memmove(sorted + sizeof(int), sorted, len - i);
            }

            sorted[i] = value;

            return;
        }
    }
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int current_sum = 0;
    int max = 0;
    int three_max[3] = {0, 0, 0};
    ssize_t read;

    fp = fopen("../input", "r");
    if (fp == NULL) {
        fprintf(stderr, "Input file not found\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        if (read == 1) {
            if (current_sum > max) {
                max = current_sum;
            }

            insert_sorted(three_max, 3, current_sum);

            current_sum = 0;
            continue;
        }

        int val = atoi(line);
        //printf("value: %zu\n", val);
        current_sum += val;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("max: %d\n", max);

    printf("max[0]: %d\n", three_max[0]);
    printf("max[1]: %d\n", three_max[1]);
    printf("max[2]: %d\n", three_max[2]);
    printf("max of three: %d\n", three_max[0] + three_max[1] + three_max[2]);

    exit(EXIT_SUCCESS);
}
