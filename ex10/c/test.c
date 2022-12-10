#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void add_cycle(unsigned long* cycle, long value, long* result) {
    *cycle += 1;

    if ((*cycle + 20) % 40 == 0) {
        printf("cycle = %ld, value = %ld\n", *cycle, value);
        *result += *cycle * value;
    }
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../input", "r");
    if (fp == NULL) {
        fprintf(stderr, "Input file not found\n");
        exit(EXIT_FAILURE);
    }

    long value = 1;
    long result = 0;
    unsigned long cycle = 1;

    while ((read = getline(&line, &len, fp)) != -1) {
        add_cycle(&cycle, value, &result);

        // printf("Retrieved line of length %zu:\n", read);
        if (strcmp(line, "noop\n") != 0) {

            int count;
            sscanf(line, "addx %d", &count);
            value += count;

            add_cycle(&cycle, value, &result);
        }

        // printf("cycle %ld value %ld\n", cycle, value);
    }

    printf("result: %ld\n", result);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
