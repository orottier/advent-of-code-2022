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

    struct hashmap *map = hashmap_new(sizeof(Position), 0, 0, 0, dirSizeHash, dirSizeCompare, NULL, NULL);
    long hx = 0, hy = 0, tx = 0, ty = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        char c;
        int d;
        sscanf(line, "%c %d", &c, &d);

        int dx = 0; int dy = 0;
        switch (c) {
            case 'R': dx = 1; break;
            case 'L': dx = -1; break;
            case 'U': dy = 1; break;
            case 'D': dy = -1; break;
            default: assert(0);
        }

        for (int i = 0; i < d; i++) {
            hx += dx;
            hy += dy;

            int dx = hx - tx;
            int dy = hy - ty;
            
            bool adjacent = dx * dx + dy * dy <= 2;
            if (!adjacent) {
                tx += sign(dx);
                ty += sign(dy);
            }

            hashmap_set(map, &(Position){ .x=tx, .y=ty });

            // printf("head now at %ld, %ld\n", hx, hy);
            // printf("tail now at %ld, %ld\n", tx, ty);
            // printf("moved %d\n", hashmap_count(map));
        }
    }

    printf("moved %zu\n", hashmap_count(map));

    hashmap_free(map);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
