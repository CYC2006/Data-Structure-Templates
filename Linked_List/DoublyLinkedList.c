#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Doubly Linked List with head & tail
typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

// Create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Initialize empty list
void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Append at end
void append(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) { // empty list
        list->head = list->tail = newNode;
        return;
    }
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}

// Insert at beginning
void insertFront(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) { // empty list
        list->head = list->tail = newNode;
        return;
    }
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
}

// Delete specific node (by pointer)
void deleteNode(DoublyLinkedList* list, Node* node) {
    if (node == NULL) return;

    if (node == list->head) list->head = node->next;
    if (node == list->tail) list->tail = node->prev;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    free(node);
}

// Print forward
void printForward(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free entire list
void freeList(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = list->tail = NULL;
}

// Example usage
int main() {
    DoublyLinkedList list;
    initList(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    printForward(&list);

    insertFront(&list, 5);
    printForward(&list);

    deleteNode(&list, list.head->next); // delete 10
    printForward(&list);

    freeList(&list);
    return 0;
}