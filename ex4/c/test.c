#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("../test.input", "r");
    if (fp == NULL) {
        fprintf(stderr, "Input file not found\n");
        exit(EXIT_FAILURE);
    }

    int full_overlap = 0;
    int overlap = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        int a1, a2, b1, b2;
        sscanf(line, "%d-%d,%d-%d", &a1, &a2, &b1, &b2);

        if (a1 <= b1 && a2 >= b2 || b1 <= a1 && b2 >= a2) {
            full_overlap += 1;
        }

        if (
                a1 <= b1 && a2 >= b1
                || a1 <= b2 && a2 >= b2
                || b1 <= a1 && b2 >= a1
                || b1 <= a2 && b2 >= a2
            ) {
            overlap += 1;
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("full_overlap: %d\n", full_overlap);
    printf("overlap: %d\n", overlap);

    exit(EXIT_SUCCESS);
}
