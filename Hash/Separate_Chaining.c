#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20011 // big prime

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

Node *table[TABLE_SIZE];

static inline int hash(int key) {
    return key % TABLE_SIZE;
}

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}

void insert(int key, int value) {
    int idx = hash(key);

    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;

    node->next = table[idx];
    table[idx] = node;
}

int search (int key) {
    int idx = hash(key);
    Node *curr = table[idx];

    while (curr) {
        if (curr->key == key) return curr->value;
        curr = curr->next;
    }
    return -1;
}

void delete_key(int key) {
    int idx = hash(key);
    Node *curr = table[idx];
    Node *prev = NULL;

    while (curr) {
        if (curr->key == key) {
            if (prev == NULL) table[idx] = curr->next;
            else prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main() {
    insert(1, 100);
    insert(2, 200);
    insert(10008, 999); // same bucket as key=1 if TABLE_SIZE=10007
    printf("search(1) = %d\n", search(1));      // 100
    printf("search(2) = %d\n", search(2));      // 200
    printf("search(10008) = %d\n", search(10008)); // 999

    delete_key(1);
    printf("search(1) after delete = %d\n", search(1)); // -1

    return 0;
}