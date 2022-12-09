#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// https://github.com/tidwall/hashmap.c
#include "hashmap.h"

typedef struct Position {
    long x;
    long y;
} Position;

int dirSizeCompare(const void *a, const void *b, void *udata) {
    const Position *pa = a;
    const Position *pb = b;

    if (pa->x != pb->x) {
        return pa->x - pb->x;
    }
    return pa->y - pb->y;
}

uint64_t dirSizeHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const Position *p = item;

    // sorry
    return p->x + 10000 + 100000*(p->y + 10000);
}

int sign(int x) {
    return (x > 0) - (x < 0);
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

    struct hashmap *map1 = hashmap_new(sizeof(Position), 0, 0, 0, dirSizeHash, dirSizeCompare, NULL, NULL);
    struct hashmap *map9 = hashmap_new(sizeof(Position), 0, 0, 0, dirSizeHash, dirSizeCompare, NULL, NULL);

    long x[10] = {0}, y[10] = {0};

    while ((read = getline(&line, &len, fp)) != -1) {
        char c;
        int d;
        sscanf(line, "%c %d", &c, &d);

        int step_x = 0; int step_y = 0;
        switch (c) {
            case 'R': step_x = 1; break;
            case 'L': step_x = -1; break;
            case 'U': step_y = 1; break;
            case 'D': step_y = -1; break;
            default: assert(0);
        }

        for (int i = 0; i < d; i++) {
            for (int j = 0; j < 10; j++) {
                if (j == 0) {
                    x[0] += step_x;
                    y[0] += step_y;
                    continue;
                }

                int dx = x[j-1] - x[j];
                int dy = y[j-1] - y[j];

                bool adjacent = dx * dx + dy * dy <= 2;
                if (!adjacent) {
                    x[j] += sign(dx);
                    y[j] += sign(dy);
                }

                if (j == 1) {
                    hashmap_set(map1, &(Position){ .x=x[j], .y=y[j] });
                } else if (j == 9) {
                    hashmap_set(map9, &(Position){ .x=x[j], .y=y[j] });
                }

                // printf("head now at %ld, %ld\n", hx, hy);
                // printf("tail now at %ld, %ld\n", tx, ty);
                // printf("moved %d\n", hashmap_count(map));
            }
        }
    }

    printf("moved 1 %zu\n", hashmap_count(map1));
    printf("moved 9 %zu\n", hashmap_count(map9));

    hashmap_free(map1);
    hashmap_free(map9);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
