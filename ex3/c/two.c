#include <stdio.h>
#include <stdlib.h>

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
    while (1) {
        int map[26+26] = {0};

        for (int i = 0; i < 3; i++) {
            read = getline(&line, &len, fp);
            if (read == -1) {
                goto done;
            }
            for (size_t j = 0; j < read; j++) {
                int value = score(line[j]);
                size_t index = value - 1;

                int prev = map[index];
                if (prev == i) {
                    map[index] = i + 1;

                    if (i + 1 == 3) {
                        result += value;
                        break;
                    }
                }
            }
        }
    }

done:
    fclose(fp);
    if (line) {
        free(line);
    }

    printf("result: %d\n", result);

    exit(EXIT_SUCCESS);
}
