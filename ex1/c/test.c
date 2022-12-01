#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t current_sum = 0;
    size_t max = 0;
    size_t three_max[3] = {0, 0, 0};
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

            // poor man's sort
            if (current_sum > three_max[0] || current_sum > three_max[1] || current_sum > three_max[2]) {
                if (three_max[0] <= three_max[1] && three_max[0] <= three_max[2]) {
                    three_max[0] = current_sum;
                } else if (three_max[1] <= three_max[0] && three_max[1] <= three_max[2]) {
                    three_max[1] = current_sum;
                } else {
                    three_max[2] = current_sum;
                }
            }

            current_sum = 0;
            continue;
        }

        size_t val = atoi(line);
        //printf("value: %zu\n", val);
        current_sum += val;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("max: %zu\n", max);

    printf("max[0]: %zu\n", three_max[0]);
    printf("max[1]: %zu\n", three_max[1]);
    printf("max[2]: %zu\n", three_max[2]);
    printf("max of three: %zu\n", three_max[0] + three_max[1] + three_max[2]);

    exit(EXIT_SUCCESS);
}
