#include <stdio.h>
#include <stdlib.h>

typedef struct CharLinkedList {
    char c;
    struct CharLinkedList * next;
} CharLinkedList;

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

    CharLinkedList* positions[10] = {0};

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        if (read <= 1) {
            // next up, move instructions
            break;
        }
        
        for (int i=0; i<read; i++) {
            char c = line[i];
            if (c >= 'A' && c <= 'Z') {
                //printf("found char %c\n", c);
                CharLinkedList* item = (CharLinkedList*) malloc (sizeof(CharLinkedList));
                item->c = c;
                item->next = NULL;

                size_t index = (i - 1) / 4;
                if (positions[index] == NULL) {
                    //printf("is null\n");
                    positions[index] = item;
                } else {
                    //printf("append\n");
                    // append to list
                    CharLinkedList* current = positions[index];
                    while (1) {
                        if (current->next != NULL) {
                            current = current->next;
                        } else {
                            break;
                        }
                    };
                    current->next = item;
                } 
            }
        }
    }

    int num, from, to;
    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "move %d from %d to %d", &num, &from, &to);
        printf("move %d from %d to %d\n", num, from, to);

        /* CrateMover 9000 */
        /*
        for (int i=0; i<num; i++) {
            CharLinkedList* from_item = positions[from - 1];
            //printf("now moving %c\n", from_item->c);
            CharLinkedList* from_parent = from_item->next;
            CharLinkedList* to_item = positions[to - 1];

            positions[from - 1] = from_parent;
            positions[to - 1] = from_item;
            positions[to - 1]->next = to_item;
        }
        */

        /* CrateMover 9001 */
        CharLinkedList* from_item = positions[from - 1];
        CharLinkedList* pickup_item = positions[from - 1];
        for (int i=1; i<num; i++) {
            pickup_item = pickup_item->next;
        }
        //printf("now moving %c\n", pickup_item->c);
        CharLinkedList* from_parent = pickup_item->next;
        CharLinkedList* to_item = positions[to - 1];
        positions[from - 1] = from_parent;
        positions[to - 1] = from_item;
        pickup_item->next = to_item;
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    for (int i=0; i<10; i++) {
        char c = '_';
        if (positions[i] != NULL) {
            c = positions[i]->c;
            printf("%c", c);
        }
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}
