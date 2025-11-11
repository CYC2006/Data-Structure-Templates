#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int QueueElement;

typedef struct {
    QueueElement *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (QueueElement*)malloc(sizeof(QueueElement) * capacity);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

bool isEmpty(Queue* q) { return q->size == 0; }

bool isFull(Queue* q) { return q->size == q->capacity; }

void enqueue(Queue* q, QueueElement val) {
    if (isFull(q)) {
        printf("Queue is Full!\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = val;
    q->size++;
}

QueueElement dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
        exit(EXIT_FAILURE);
    }
    QueueElement val = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return val;
}

QueueElement front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
        exit(EXIT_FAILURE);
    }
    return q->data[q->front];
}

void freeQueue(Queue* q) {
    free(q->data);
    free(q);
}

int main() {
    Queue* q = createQueue(5);

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("Front: %d\n", front(q));
    printf("Dequeue: %d\n", dequeue(q));
    printf("Front after dequeue: %d\n", front(q));

    freeQueue(q);
    
    return 0;
}