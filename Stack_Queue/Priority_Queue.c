#include <stdio.h>

#define MAXN 200005

// max heap
int heap[MAXN];
int heapSize = 0;

#define PARENT(i) ((i) / 2)
#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)

void push(int x) {
    heap[++heapSize] = x;
    int i = heapSize;
    while (i > 1 && heap[PARENT(i)] < heap[i]) {
        int temp = heap[i];
        heap[i] = heap[PARENT(i)];
        heap[PARENT(i)] = temp;
        i = PARENT(i);
    }
}

int top() {
    return heapSize ? heap[1] : -1;
}

void pop() {
    if (heapSize == 0) return;
    heap[1] = heap[heapSize--];
    int i = 1;
    while(1) {
        int largest = i;
        if (LEFT(i) <= heapSize && heap[LEFT(i)] > heap[largest]) largest = LEFT(i);
        if (RIGHT(i) <= heapSize && heap[RIGHT(i)] > heap[largest]) largest = RIGHT(i);
        if (largest == i) break;
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        i = largest;
    }
}

int empty() {
    return heapSize == 0;
}


int main() {
    push(5);
    push(10);
    push(3);
    push(8);
    push(6);

    printf("Current Max: %d\n", top());

    while (!empty()) {
        printf("Pop %d\n", top());
        pop();
    }

    return 0;
}