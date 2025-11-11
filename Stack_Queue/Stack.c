#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int StackElement;

typedef struct {
    StackElement *data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (StackElement*)malloc(sizeof(StackElement) * capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

bool isEmpty(Stack* s) { return s->top == -1; }

bool isFull(Stack* s) { return s->top == s->capacity - 1; }

void push(Stack* s, StackElement val) {
    if (isFull(s)) {
        printf("Stack is Full!\n");
        return;
    }
    s->data[++s->top] = val;
}

StackElement pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is Empty!\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top--];
}

StackElement peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is Empty!\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

void freeStack(Stack* s) {
    free(s->data);
    free(s);
}

int main() {
    Stack* s = createStack(5);

    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("Top element: %d\n", peek(s));
    printf("Pop: %d\n", pop(s));
    printf("Top after pop: %d\n", peek(s));

    freeStack(s);
    return 0;
}