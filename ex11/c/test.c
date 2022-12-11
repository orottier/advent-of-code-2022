#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX(x,y) (((x) >= (y)) ? (x) : (y))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

typedef struct Monkey {
    unsigned long items[255];
    size_t items_len;
    char operator;
    unsigned long operator_val;
    unsigned long divisible;
    size_t target_true;
    size_t target_false;
    unsigned long activity_count;
} Monkey;

int compareMonkey (const void * a, const void * b)
{
  if ( ((Monkey*)a)->activity_count > ((Monkey*)b)->activity_count ) return -1;
  if ( ((Monkey*)a)->activity_count < ((Monkey*)b)->activity_count ) return 1;
  return 0;
}

void debug_monkey(Monkey * monkey) {
    printf("Monkey items (%zu):\n", monkey->items_len);
    for (int i = 0; i < monkey->items_len; i++) {
        printf("%lu ", monkey->items[i]);
    }
    printf("\n operator %c val %lu\n", monkey->operator, monkey->operator_val);
    printf("divisble %lu if true %zu else %zu\n\n", monkey->divisible, monkey->target_true, monkey->target_false);
}

void do_monkey(Monkey * monkeys, size_t index, unsigned long modulo) {
    Monkey *monkey = &monkeys[index];
    // debug_monkey(monkey);

    for (int i = 0; i < monkey->items_len; i++) {
        unsigned long item = monkey->items[i];
        
        switch (monkey->operator) {
            case '^': item *= item; break;
            case '*': item *= monkey->operator_val; break;
            case '+': item += monkey->operator_val; break;
            default: assert(0);
        }

        //item /= 3;
        item = item % modulo;

        size_t target_monkey;
        if (item % monkey->divisible == 0) {
            target_monkey = monkey->target_true;
        } else {
            target_monkey = monkey->target_false;
        }

        // printf("   give %lu to monkey %zu\n", item, target_monkey);

        monkeys[target_monkey].items[monkeys[target_monkey].items_len] = item;
        monkeys[target_monkey].items_len += 1;
    }

    monkey->activity_count += monkey->items_len;
    monkey->items_len = 0;
}

void run_round(Monkey * monkeys, size_t monkey_count, unsigned long modulo) {
    for (int i = 0; i < monkey_count; i++) {
        // printf(" monkey %d\n", i);
        do_monkey(monkeys, i, modulo);
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

    Monkey monkeys[8];
    size_t i = 0;
    
    while (1) {
        Monkey* monkey = &monkeys[i++];

        // consume "Monkey x:"
        read = getline(&line, &len, fp);
        size_t monkey_id;
        sscanf(line, "Monkey %zd:", &monkey_id);
        assert(i == monkey_id + 1);

        // consume "Starting items: 79, 98, .."
        read = getline(&line, &len, fp);
        size_t item_index = 0;
        int readCharCount;
        sscanf(line, "  Starting items: %ld%n", &monkey->items[item_index++], &readCharCount);
        int offset = readCharCount;
        while(sscanf(line + offset, ", %ld%n", &monkey->items[item_index++], &readCharCount) > 0){
            offset += readCharCount;
        }
        monkey->items_len = item_index - 1;

        // consume "Operation: new = old * 19"
        read = getline(&line, &len, fp);
        char operator_val[3] = {0};
        sscanf(line, "  Operation: new = old %c %s\n", &monkey->operator, operator_val);
        if (strcmp(operator_val, "old") == 0) {
            monkey->operator = '^'; // special case "old * old"
        } else {
            sscanf(operator_val, "%ld", &monkey->operator_val);
        }

        // consume "Test: divisible by 13"
        read = getline(&line, &len, fp);
        sscanf(line, "  Test: divisible by %ld", &monkey->divisible);

        // consume "throw to"
        read = getline(&line, &len, fp);
        sscanf(line, "    If true: throw to monkey %zd", &monkey->target_true);
        read = getline(&line, &len, fp);
        sscanf(line, "    If false: throw to monkey %zd", &monkey->target_false);

        monkey->activity_count = 0;

        // consume possible newline
        read = getline(&line, &len, fp);
        if (read == EOF) {
            break;
        }
    }

    size_t monkey_count = i;
    for (int i = 0; i < monkey_count; i++) {
        debug_monkey(&monkeys[i]);
    }

    unsigned long modulo = 1;
    for (int m = 0; m < monkey_count; m++) {
        modulo *= monkeys[m].divisible;
    }

    for (int i = 0; i < 10000; i++) {
        // printf("round %d\n", i + 1);
        run_round(monkeys, monkey_count, modulo);
    }

    printf("\nActivity counts:\n");
    for (int i = 0; i < monkey_count; i++) {
        printf("monkey %d activity count %ld\n", i, monkeys[i].activity_count);
    }

    qsort (monkeys, monkey_count, sizeof(Monkey), compareMonkey);
    printf("\nTop two\n");
    for (int i = 0; i < 2; i++) {
        printf("monkey %d activity count %ld\n", i, monkeys[i].activity_count);
    }
    printf("\nMultiplied = %lu\n", monkeys[0].activity_count * monkeys[1].activity_count);

    fclose(fp);
    if (line) {
        free(line);
    }

    exit(EXIT_SUCCESS);
}
