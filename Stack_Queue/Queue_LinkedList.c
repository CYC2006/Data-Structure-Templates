#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int QueueElement;

typedef struct Node {
    QueueElement data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

bool isEmpty(Queue* q){ return q->front == NULL; }

void enqueue(Queue* q, QueueElement val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = n;
    }
    else {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

QueueElement dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = q->front;
    QueueElement val = temp->data;
    q->front =  temp->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->size--;
    return val;
}

QueueElement front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
        exit(EXIT_FAILURE);
    }
    return q->front->data;
}

void freeQueue(Queue* q) {
    while (!isEmpty(q)) dequeue(q);
    free(q);
}

int main() {
    Queue* q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("Front: %d\n", front(q));
    printf("Dequeue: %d\n", dequeue(q));
    printf("Front after dequeue: %d\n", front(q));

    freeQueue(q);
    return 0;
}