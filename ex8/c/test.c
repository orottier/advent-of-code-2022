#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(x,y) (((x) >= (y)) ? (x) : (y))

bool check_visible(char map[][100], int row, int col) {
    char height = map[row][col];
    bool visible;

    // from left:
    visible = true;
    for (int i=0; i<col; i++) {
        if (map[row][i] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }

    // from right:
    visible = true;
    for (int i=99; i>col; i--) {
        if (map[row][i] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }

    // from top:
    visible = true;
    for (int i=0; i<row; i++) {
        if (map[i][col] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }

    // from right:
    visible = true;
    for (int i=99; i>row; i--) {
        if (map[i][col] >= height) {
            visible = false;
            break;
        }
    }
    return visible;
}

unsigned long scenic_score(char map[][100], int row, int col, size_t map_w, size_t map_h) {
    char height = map[row][col];

    // looking left:
    unsigned long left_score = 0;
    for (int i=col - 1; i>=0; i--) {
        left_score++;
        if (map[row][i] >= height) {
            break;
        }
    }

    // looking right:
    unsigned long right_score = 0;
    for (int i=col + 1; i<map_w; i++) {
        right_score++;
        if (map[row][i] >= height) {
            break;
        }
    }

    // looking up:
    unsigned long up_score = 0;
    for (int i=row - 1; i>=0; i--) {
        up_score++;
        if (map[i][col] >= height) {
            break;
        }
    }

    // looking down:
    unsigned long down_score = 0;
    for (int i=row + 1; i<map_h; i++) {
        down_score++;
        if (map[i][col] >= height) {
            break;
        }
    }

    return left_score * right_score * up_score * down_score;
}

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

    char map[100][100] = {0};

    size_t map_w;
    int row = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        map_w = strlen(line) - 1;
        // printf("Retrieved line of length %zu:\n", read);
        for (int col=0; col<strlen(line) - 1; col++) {
            map[row][col] = line[col];
        }

        row++;
    }

    size_t map_h = row;

    unsigned long visible = 0;
    unsigned long max_scenic_score = 0;

    for (int i=0; i<row; i++) {
        int j = 0;
        do {
            if (check_visible(map, i, j)) {
                visible++;
            }
            max_scenic_score = MAX(max_scenic_score, scenic_score(map, i, j, map_w, map_h));
            j++;
        } while (map[i][j]);
    }

    printf("visible: %ld\n", visible);
    printf("max scenic score: %ld\n", max_scenic_score);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
