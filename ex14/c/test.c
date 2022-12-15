#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define GRID_SIZE 1024

void draw(char map[GRID_SIZE][GRID_SIZE], size_t col1, size_t row1, size_t col2, size_t row2) {
    int dc = col1 == col2 ? 0 : (col1 < col2 ? 1 : -1);
    int dr = row1 == row2 ? 0 : (row1 < row2 ? 1 : -1);
    while (1) {
        map[row1][col1] = '#';

        if (col1 == col2 && row1 == row2) {
            break;
        }

        col1 += dc;
        row1 += dr;
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

    char map[GRID_SIZE][GRID_SIZE];
    memset(map, '.', GRID_SIZE * GRID_SIZE);
    size_t col1, row1, col2, row2;
    size_t max_row = 0;;
    int offset, next;

    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%zu,%zu -> %zu,%zu%n", &col1, &row1, &col2, &row2, &offset);
        draw(map, col1, row1, col2, row2);

        if (row1 > max_row)
            max_row = row1;

        while (sscanf(line + offset, " -> %zu,%zu%n", &col1, &row1, &next) > 1) {
            draw(map, col1, row1, col2, row2);

            if (row1 > max_row)
                max_row = row1;

            col2 = col1;
            row2 = row1;

            offset += next;
            if (line[offset] == '\n') {
                break;
            }
        }
    }

    /*
    for (size_t row = 0; row < 15; row++) {
        for (size_t col = 490; col < GRID_SIZE; col++) {
            printf("%c", map[row][col]);
        }
        printf("\n");
    }
    for (size_t row = 0; row < GRID_SIZE; row++) {
        for (size_t col = 0; col < GRID_SIZE; col++) {
            if (map[row][col] != '.') {
                printf("row %zu col %zu\n", row, col);
            }
        }
    }
    */

    size_t floor = max_row + 2;
    assert(floor < GRID_SIZE);
    memset(map[floor], '#', GRID_SIZE);

    size_t counter = 0;
    while (1) {
        size_t row = 0, col = 500;
        while (1) {
            assert(col > 0 && col < GRID_SIZE);
            if (row >= GRID_SIZE - 1) {
                goto done;
            }
            if (map[row+1][col] == '.') {
                row++;
                continue;
            }
            if (map[row+1][col-1] == '.') {
                row++;
                col--;
                continue;
            }
            if (map[row+1][col+1] == '.') {
                row++;
                col++;
                continue;
            }
            map[row][col] = 'o';

            if (row == 0 && col == 500) {
                counter++;
                goto done;
            }

            break;
        }
        counter++;
    }

done:
    printf("stable: %zu\n", counter);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
