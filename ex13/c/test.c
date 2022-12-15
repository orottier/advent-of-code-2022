#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define INFINITY 9999
#define MAX_HEIGHT 42
#define MAX_WIDTH 160
#define TOTAL (MAX_HEIGHT * MAX_WIDTH)

bool right_is_larger(char * left, char * right, int depth_left, int depth_right) {
    printf("comparing '%s' versus '%s'\n", left, right);
    char c_left = left[0];
    if (c_left == ',') {
        c_left = left[1];
        left++;
    }
    char c_right = right[0];
    if (c_right == ',') {
        c_right = right[1];
        right++;
    }

    if (c_left == 0) {
        return true;
    }
    if (c_right == 0) {
        return false;
    }

    if (
            (c_left == '[' && c_right == '[')
            || (c_left == ',' && c_right == ',')
            || (c_left == ']' && c_right == ']')
       ) {
        return right_is_larger(left + 1, right + 1, depth_left + 1, depth_right + 1);
    }

    if (c_left == ']') {
        if (depth_left > depth_right) {
            return right_is_larger(left + 1, right, depth_left - 1, depth_right);
        }
        return true;
    } else {
        if (c_right == ']') {
            if (depth_right > depth_left) {
                return right_is_larger(left, right + 1, depth_left, depth_right - 1);
            }
            return false;
        }
    }

    if (c_left == '[') {
        return right_is_larger(left + 1, right, depth_left + 1, depth_right);
    }
    if (c_right == '[') {
        return right_is_larger(left, right + 1, depth_left, depth_right + 1);
    }

    unsigned int left_num, right_num, read_left = 0, read_right = 0;
    assert(sscanf(left, "%d,%n", &left_num, &read_left) == 1);
    assert(sscanf(right, "%d,%n", &right_num, &read_right) == 1);

    if (right_num > left_num) {
        return true;
    }
    if (right_num < left_num) {
        return false;
    }
    if (read_left == 0) {
        read_left = 1;
    }
    if (read_right == 0) {
        read_right = 1;
    }
    printf("jump next %d %d\n", read_left, read_right);
    return right_is_larger(left + read_left, right + read_right, depth_left, depth_right);
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

    char left[512], right[512];
    size_t counter = 0, sum = 0;

    bool readnext = true;
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);

        if (readnext) {
            // clear inputs, ensure null terminated
            memset(left, 0, 512);
            memset(right, 0, 512);

            memcpy(left, line, read - 1);
            readnext = false;

            continue;
        }

        memcpy(right, line, read - 1);
        counter++;

        if (right_is_larger(left, right, 0, 0)) {
            sum += counter;
            printf("right is larger for item %zu, sum = %zu\n", counter, sum);
        } else {
            printf("left is larger for item %zu\n", counter);
        }

        // consume newline
        if (getline(&line, &len, fp) == -1) {
            break;
        }
        readnext = true;
    }

    printf("sum = %zu\n", sum);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
