#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define INFINITY 9999
#define MAX_HEIGHT 42
#define MAX_WIDTH 160
#define TOTAL (MAX_HEIGHT * MAX_WIDTH)

size_t find_neighbours(size_t pos, size_t* neighbours, char* map) {
    char max_elevation = map[pos] + 1;
    size_t found = 0;

    size_t row = pos / MAX_WIDTH;
    size_t col = pos % MAX_WIDTH;

    // look up
    if (row > 0 && map[pos - MAX_WIDTH] <= max_elevation) {
        neighbours[found++] = pos - MAX_WIDTH;
    }
    // look down
    if (map[pos + MAX_WIDTH] != 0 && map[pos + MAX_WIDTH] <= max_elevation) {
        neighbours[found++] = pos + MAX_WIDTH;
    }
    // look left
    if (col > 0 && map[pos - 1] <= max_elevation) {
        neighbours[found++] = pos - 1;
    }
    // look right
    if (map[pos + 1] != 0 && map[pos + 1] <= max_elevation) {
        neighbours[found++] = pos + 1;
    }

    return found;
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

    char map[TOTAL] = {0};
    size_t row = 0;
    char * search;
    size_t startpos = INFINITY, endpos = INFINITY;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);

        // find S, replace with 'a' in map
        search = (char*) memchr(line, 'S', read);
        if (search != NULL) {
            startpos = row * MAX_WIDTH + search - line;
            *search = 'a';
        }

        // find E, replace with 'z' in map
        search = (char*) memchr(line, 'E', read);
        if (search != NULL) {
            endpos = row * MAX_WIDTH + search - line;
            *search = 'z';
        }

        memcpy(&map[row * MAX_WIDTH], line, read - 1);
        row++;
    }

    assert(startpos != INFINITY);
    assert(endpos != INFINITY);

    // print map
    /*
    for (int i = 0; i < MAX_HEIGHT; i++) {
        if (map[i * MAX_WIDTH] == 0)
            break;
        printf("%s\n", map + i * MAX_WIDTH);
    }
    */
    printf("start %zu %c end %zu %c\n", startpos, map[startpos], endpos, map[endpos]);

    // move `pos` through map, keep track of previous positions with `visited_stack`
    size_t pos = startpos;
    unsigned int visited_stack[TOTAL] = {startpos};
    size_t visited_stack_len = 1;

    // total distance map, inititalize to `INF` at first, except startpos (=0)
    unsigned int distance[TOTAL];
    for (int i = 0; i < TOTAL; i++)
        distance[i] = INFINITY;
    distance[startpos] = 0;

    // fill this array with neighbours on map position
    size_t neighbours[4];

    while (1) {
        size_t found = find_neighbours(pos, neighbours, map);

        bool stuck = true;
        for (size_t i = 0; i < found; i++) {
            size_t neighbour = neighbours[i];
            if (distance[neighbour] > distance[pos] + 1) {
                stuck = false;

                // move into this position
                distance[neighbour] = distance[pos] + 1;
                pos = neighbours[i];
                visited_stack[visited_stack_len++] = pos;
                break;
            } else {
                // printf("not visiting %zu again\n", neighbour);
            }
        }

        if (stuck) {
            if (visited_stack_len == 1) {
                break; // stuck at startpos, we are done
            }
            pos = visited_stack[--visited_stack_len - 1];
        }
    }

    printf("distance to end: %d\n", distance[endpos]);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
