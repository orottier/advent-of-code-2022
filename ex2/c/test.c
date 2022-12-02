#include <stdio.h>
#include <stdlib.h>

// opponent: A = rock, B = paper, C = scissor
// me: X = rock (1), Y = paper (2), Z = scissor (3)
// outcome: X = lose, Y = draw, Z = win

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

unsigned int score_outcome(char other, char outcome) {
    switch (outcome) {
        case 'X':
            switch (other) {
                case 'A':
                    return score_game(other, 'Z');
                case 'B':
                    return score_game(other, 'X');
                case 'C':
                    return score_game(other, 'Y');
            }
        case 'Y':
            switch (other) {
                case 'A':
                    return score_game(other, 'X');
                case 'B':
                    return score_game(other, 'Y');
                case 'C':
                    return score_game(other, 'Z');
            }
        case 'Z':
            switch (other) {
                case 'A':
                    return score_game(other, 'Y');
                case 'B':
                    return score_game(other, 'Z');
                case 'C':
                    return score_game(other, 'X');
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
        char other = line[0];
        char me = line[2];
        score_a += score_game(other, me);

        char outcome = me;
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
