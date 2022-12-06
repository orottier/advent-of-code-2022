#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char prev[15] = {0}; // include null terminator
    read = getline(&line, &len, fp);
    for (int i = 0; i < read; i++) {
        memmove(prev + sizeof(char), prev, 13);
        prev[0] = line[i];
        //printf("evaluating %s\n", prev);

        for (int j=0; j<14; j++) {
            for (int k=0; k<j; k++) {
                if (prev[j] == prev[k]) {
                    goto cont;
                }
            }
        }

        printf("message at %i\n", i + 1);
        break;

cont:
        ;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
