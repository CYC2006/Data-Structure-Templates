#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insert(Node** head, int data, int pos) {
    Node* newNode = createNode(data);
    
    // insert at the front
    if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* temp = *head;
    for (int i=0; i<pos-1; ++i) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void delete(Node** head, int pos) {
    // empty linked list
    if (*head == NULL) return;

    Node* temp = *head;
    Node* prev = NULL;

    // delete first node
    if (pos == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i=0; i<pos; ++i) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    free(temp);
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Free entire list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    append(&head, 10);
    append(&head, 20);
    append(&head, 40);

    insert(&head, 30, 2);
    delete(&head, 1);

    printList(head);
    
    return 0;
}