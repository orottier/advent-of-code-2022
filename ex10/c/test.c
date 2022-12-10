#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(x,y) (((x) >= (y)) ? (x) : (y))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

void add_cycle(unsigned long* cycle, long value, long* result, char* buffer) {
    *cycle += 1;
    long cycle_mod = *cycle % 40;

    unsigned long max = MAX(cycle_mod, value);
    unsigned long min = MIN(cycle_mod, value);
    if (max - min <= 1) {
        buffer[cycle_mod] = '#';
    }

    if ((*cycle + 20) % 40 == 0) {
        // printf("cycle = %ld, value = %ld\n", *cycle, value);
        *result += *cycle * value;
    }

    if (cycle_mod == 0) {
        printf("-- %s --\n", buffer);
        memset(buffer, '.', 40);
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
    unsigned long cycle = 0;

    char buffer[41];
    memset(buffer, '.', 40);
    buffer[40] = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        add_cycle(&cycle, value, &result, buffer);

        // printf("Retrieved line of length %zu:\n", read);
        if (strcmp(line, "noop\n") != 0) {

            int count;
            sscanf(line, "addx %d", &count);
            value += count;

            add_cycle(&cycle, value, &result, buffer);
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
