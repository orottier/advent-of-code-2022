#include <stdio.h>
#include <stdlib.h>

unsigned int score_game(char other, char me) {
    unsigned int score = 0;

    switch (me) {
        case 'X':
            score += 1;
            switch (other) {
                case 'A':
                    score += 3;
                    break;
                case 'C':
                    score += 6;
                    break;
            }
            break;
        case 'Y':
            score += 2;
            switch (other) {
                case 'A':
                    score += 6;
                    break;
                case 'B':
                    score += 3;
                    break;
            }
            break;
        case 'Z':
            score += 3;
            switch (other) {
                case 'B':
                    score += 6;
                    break;
                case 'C':
                    score += 3;
                    break;
            }
            break;
    }

    return score;
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    unsigned int score = 0;

    fp = fopen("../input", "r");
    if (fp == NULL) {
        fprintf(stderr, "Input file not found\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char other = line[0];
        char me = line[2];
        score += score_game(other, me);
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("score: %d\n", score);

    exit(EXIT_SUCCESS);
}
