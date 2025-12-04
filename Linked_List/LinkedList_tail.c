#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        perror("Failed to allocate list structure");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void append(LinkedList* list, int data) {
    Node* newNode = createNode(data);

    // Null LinkedList
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    // Not Null
    list->tail->next = newNode;
    list->tail = newNode;
}

void insert(LinkedList* list, int data, int pos) {
    Node* newNode = createNode(data);

    if (pos == 0) {
        newNode->next = list->head;
        list->head = newNode;
        
        if (list->tail == NULL) {
            list->tail = newNode;
        }
        return;
    }

    Node* temp = list->head;
    for (int i = 0; temp != NULL && i < pos - 1; ++i) {
        temp = temp->next;
    }

    if (temp == NULL) { // pos out of range
        printf("Error: Position out of bounds.\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    
    if (newNode->next == NULL) {
        list->tail = newNode;
    }
}

void deleteNode(LinkedList* list, int pos) {
    if (list->head == NULL) return;

    Node* temp = list->head;
    Node* prev = NULL;

    if (pos == 0) {
        list->head = temp->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < pos; ++i) {
        prev = temp;
        temp = temp->next;
    }
    
    // pos out of range
    if (temp == NULL) return;
    
    prev->next = temp->next;
    
    if (temp == list->tail) {
        list->tail = prev;
    }

    free(temp);
}


void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int main() {

    LinkedList* list = createList(); 

    append(list, 10); // list->head = 10, list->tail = 10
    append(list, 20); // list->tail->next = 20, list->tail = 20
    append(list, 40); // list->tail->next = 40, list->tail = 40

    insert(list, 30, 2); // 10 -> 20 -> 30 -> 40

    deleteNode(list, 1); // 10 -> 30 -> 40

    printf("Final List: ");
    printList(list->head);
    
    printf("Tail data: %d\n", list->tail->data);

    freeList(list->head);
    free(list);
    
    return 0;
}