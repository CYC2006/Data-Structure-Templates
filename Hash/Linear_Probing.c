#include <stdio.h>
#include <stdlib.h>

#define EMPTY_KEY -1
#define DELETED_KEY -2
#define TABLE_SIZE 20011 // big prime (near 2 * n)

typedef struct {
    int key;
    int value;
} Entry;

Entry table[TABLE_SIZE];

static inline int hash(int key) {
    return key % TABLE_SIZE;
}

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = EMPTY_KEY;
    }
}

void insert(int key, int value) {
    int idx = hash(key);
    while (table[idx].key != EMPTY_KEY && table[idx].key != DELETED_KEY) {
        idx++;
        if (idx == TABLE_SIZE) idx = 0;
    }
    table[idx].key = key;
    table[idx].value = value;
}

int search(int key) {
    int idx = hash(key);
    while (table[idx].key != EMPTY_KEY) {
        if (table[idx].key == key) return table[idx].value;
        idx++;
        if (idx == TABLE_SIZE) idx = 0;
    }
    return -1;
}

void remove_key(int key) {
    int idx = hash(key);
    while (table[idx].key != EMPTY_KEY) {
        if (table[idx].key == key) {
            table[idx].key = DELETED_KEY;
            return;
        }
        idx++;
        if (idx == TABLE_SIZE) idx = 0;
    }
}

int main() {
    init_table();

    insert(10, 100);
    insert(21, 210);
    insert(32, 320);
    insert(43, 430);

    printf("search(10) = %d\n", search(10));  // 100
    printf("search(21) = %d\n", search(21));  // 210
    printf("search(32) = %d\n", search(32));  // 320
    printf("search(43) = %d\n", search(43));  // 430
    printf("search(99) = %d\n", search(99));  // -1

    printf("Deleting 21...\n");
    remove_key(21);
    printf("search(21) = %d\n", search(21));  // -1

    insert(21, 555);
    printf("search(21) = %d\n", search(21));  // 555

    return 0;
}