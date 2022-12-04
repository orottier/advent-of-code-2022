#include <stdio.h>
#include <stdlib.h>

char overlap(char * buf, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char needle = buf[i];
        for (size_t j = len / 2; j < len; j++) {
            if (needle == buf[j]) {
                return buf[j];
            }
        }
    }

    return -1;
}

int score(char c) {
    if (c > 'a' && c <= 'z') {
        return c + 1 - 'a';
    }
    return c + 1 - 'A' + 26;
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

    int result = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("line len: %zu\n", read);

        char o = overlap(line, read - 1);
        //printf("common: %c\n", o);

        result += score(o);
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("result: %d\n", result);

    exit(EXIT_SUCCESS);
}
