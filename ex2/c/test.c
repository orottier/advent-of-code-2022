#include <stdio.h>
#include <stdlib.h>

enum pick { ROCK = 'A', PAPER = 'B', SCISSORS = 'C' };
enum outcome { LOSE = 'X', DRAW = 'Y', WIN = 'Z' };

unsigned int score_game(enum pick other, enum pick me) {
    unsigned int score = 0;

    switch (me) {
        case ROCK:
            score += 1;
            switch (other) {
                case ROCK:
                    score += 3;
                    break;
                case SCISSORS:
                    score += 6;
                    break;
                default:
                    break;
            }
            break;
        case PAPER:
            score += 2;
            switch (other) {
                case ROCK:
                    score += 6;
                    break;
                case PAPER:
                    score += 3;
                    break;
                default:
                    break;
            }
            break;
        case SCISSORS:
            score += 3;
            switch (other) {
                case PAPER:
                    score += 6;
                    break;
                case SCISSORS:
                    score += 3;
                    break;
                default:
                    break;
            }
            break;
    }

    return score;
}

unsigned int score_outcome(char other, char outcome) {
    switch (outcome) {
        case LOSE:
            switch (other) {
                case ROCK:
                    return score_game(other, SCISSORS);
                case PAPER:
                    return score_game(other, ROCK);
                case SCISSORS:
                    return score_game(other, PAPER);
            }
        case DRAW:
            return score_game(other, other);
        case WIN:
            switch (other) {
                case ROCK:
                    return score_game(other, PAPER);
                case PAPER:
                    return score_game(other, SCISSORS);
                case SCISSORS:
                    return score_game(other, ROCK);
            }
    }

    return -1;
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    unsigned int score_a = 0;
    unsigned int score_b = 0;

    fp = fopen("../input", "r");
    if (fp == NULL) {
        fprintf(stderr, "Input file not found\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        enum pick other = line[0];
        enum pick me = line[2] - ('X' - 'A');
        score_a += score_game(other, me);

        char outcome = line[2];
        score_b += score_outcome(other, outcome);
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    printf("score a: %d\n", score_a);
    printf("score b: %d\n", score_b);

    exit(EXIT_SUCCESS);
}
