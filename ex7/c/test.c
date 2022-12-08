#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// https://github.com/tidwall/hashmap.c
#include "hashmap.h"

// http://www.cse.yorku.ca/~oz/hash.html
uint64_t hash(const char *str) {
    uint64_t hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

typedef struct DirSize {
    char * path;
    unsigned long size;
} DirSize;

int dirSizeCompare(const void *a, const void *b, void *udata) {
    const DirSize *dsa = a;
    const DirSize *dsb = b;
    return strcmp(dsa->path, dsb->path);
}

uint64_t dirSizeHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const DirSize *ds = item;
    return hash(ds->path);
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

    struct hashmap *map = hashmap_new(sizeof(DirSize), 0, 0, 0, dirSizeHash, dirSizeCompare, NULL, NULL);
    char * dir_stack = calloc(100, sizeof(char));
    char * dir_stack_iter = calloc(100, sizeof(char));
    bool assert_ls = false;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        if (assert_ls) {
            // printf("assert ls: %s", line);
            assert_ls = false;
            assert(strcmp(line, "$ ls\n") == 0);
            continue;
        }
        if (strcmp(line, "$ cd ..\n") == 0) {
            // move dir up
            char * slash = strrchr(dir_stack, '/');
            assert(slash != NULL);
            *slash = 0;
            continue;
        }
        if (strncmp(line, "$ cd ", 5) == 0) {
            assert_ls = true;
            size_t len = strlen(dir_stack);
            if (len > 0) {
                dir_stack[len] = '/';
                len++;
            }
            strcpy(&dir_stack[len], &line[5]);
            dir_stack[len + strlen(line) - 6] = 0;
            printf("dir stack '%s'\n", dir_stack);

            char * dir_stack_clone = malloc(strlen(dir_stack) + 1);
            strcpy(dir_stack_clone, dir_stack);
            hashmap_set(map, &(DirSize){ .path=dir_stack_clone, .size=0 });

            continue;
        }
        if (strncmp(line, "dir ", 4) == 0) {
            continue;
        }

        unsigned long filesize;
        sscanf(line, "%ld", &filesize);
        
        strcpy(dir_stack_iter, dir_stack);
        do {
            DirSize * dirSize = hashmap_get(map, &(DirSize){ .path=dir_stack_iter });
            assert(dirSize != NULL);
            dirSize->size += filesize;

            char * slash = strrchr(dir_stack_iter, '/');
            assert(slash != NULL);
            *slash = 0;
        } while (strlen(dir_stack_iter) > 0);
    }

    unsigned long sumSmall = 0;

    size_t iter = 0;
    void *item;
    while (hashmap_iter(map, &iter, &item)) {
        const DirSize *ds = item;
        printf("dir %s (size=%ld)\n", ds->path, ds->size);

        if (ds->size <= 100000) {
            sumSmall += ds->size;
        }
    }

    printf("sum of small dirs: %ld\n", sumSmall);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
