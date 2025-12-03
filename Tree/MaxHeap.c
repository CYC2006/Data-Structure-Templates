#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Max Heap with Root index = 1

typedef struct {
    int arr[MAX_SIZE + 1];
    int size;
} MaxHeap;

void initHeap(MaxHeap *h) {
    h->size = 0;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(MaxHeap *h, int i) {
    while (i > 1) {
        int parent  = i / 2;
        if (h->arr[i] > h->arr[parent]) {
            swap(&h->arr[i], &h->arr[parent]);
            i = parent;
        }
        else break;
    }
}

void heapifyDown(MaxHeap *h, int i) {
    while (1) {
        int left = 2 *i ;
        int right = 2 * i + 1;
        int largest = i;
        
        if (left <= h->size && h->arr[left] > h->arr[largest]) largest = left;
        if (right <= h->size && h->arr[right] > h->arr[largest]) largest = right;

        if (largest != i) {
            swap(&h->arr[i], &h->arr[largest]);
            i = largest;
        }
        else break;
    }
}

void insert(MaxHeap *h, int val) {
    if (h->size == MAX_SIZE) {
        printf("Heap is Full!\n");
        return;
    }
    h->arr[++h->size] = val;
    heapifyUp(h, h->size);
}

int extractMax(MaxHeap *h) {
    if (h->size == 0) {
        printf("Heap is Empty!\n");
        exit(EXIT_FAILURE);
    }
    int max = h->arr[1];
    h->arr[1] = h->arr[h->size--];
    heapifyDown(h, 1);
    return max;
}

void printHeap(MaxHeap *h) {
    for (int i = 1; i <= h->size; i++) printf("%d ", h->arr[i]);
    printf("\n");
}

int main() {
    MaxHeap h;
    initHeap(&h);

    insert(&h, 10);
    insert(&h, 40);
    insert(&h, 20);
    insert(&h, 30);

    printHeap(&h);
    printf("Extract max: %d\n", extractMax(&h));
    printHeap(&h);
    return 0;
}