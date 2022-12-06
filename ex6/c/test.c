#include <stdio.h>
#include <stdlib.h>

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

    char prev[4] = {0};
    read = getline(&line, &len, fp);
    for (int i = 0; i < read; i++) {
        prev[0] = prev[1];
        prev[1] = prev[2];
        prev[2] = prev[3];
        prev[3] = line[i];

        if (
                prev[0] != 0
                && prev[0] != prev[1] && prev[0] != prev[2] && prev[0] != prev[3]
                && prev[1] != prev[2] && prev[1] != prev[3]
                && prev[2] != prev[3]
        ) {
            printf("pos: %d\n", i + 1);
            break;
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
