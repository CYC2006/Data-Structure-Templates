#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 200005
#define MAX_EDGES 200005

// Basic Adjacency List Setup
typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *adj[MAX_NODES];
int visited[MAX_NODES];

void addEdge(int u, int v) {
    // the later-added node will be placed at the frontaa
    Node *a = malloc(sizeof(Node));
    a->val = u;
    a->next = adj[v];
    adj[v] = a;

    Node *b = malloc(sizeof(Node));
    b->val = v;
    b->next = adj[u];
    adj[u] = b;
}

void deleteEdge(int u, int v) {
    Node *curr = adj[u];
    Node *prev = NULL;
    while (curr != NULL) {
        if (curr->val == v) {
            if (prev == NULL) { adj[u] = curr->next; } // v is the first neighbor
            else { prev->next = curr->next; }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    curr = adj[v];
    prev = NULL;
    while (curr != NULL) {
        if (curr->val == u) {
            if (prev == NULL) { adj[v] = curr->next; } // v is the first neighbor
            else { prev->next = curr->next; }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}


// BFS
typedef struct {
    int data[MAX_NODES];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = 0; }
int isEmpty(Queue *q) { return q->front == q->rear; }
void enqueue(Queue *q, int v) { q->data[q->rear++] = v; }
int dequeue(Queue *q) { return q->data[q->front++]; }

void BFS(int start, int n) {
    for (int i = 0; i < n; i++) visited[i] = 0;
    Queue q;
    initQueue(&q);

    visited[start] = 1;
    enqueue(&q, start);

    printf("BFS: ");
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        for (Node *p = adj[u]; p != NULL; p = p->next) {
            if (!visited[p->val]) {
                visited[p->val] = 1;
                enqueue(&q, p->val);
            }
        }
    }
    printf("\n");
}


// DFS
void DFSUtil(int u) {
    visited[u] = 1;
    printf("%d ", u);
    for (Node *p = adj[u]; p != NULL; p = p->next) {
        if (!visited[p->val]) DFSUtil(p->val);
    }
}

void DFS(int start, int n) {
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("DFS: ");
    DFSUtil(start); // Recursive uses Stack
    printf("\n");
}

int main() {
    int n = 6;
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 5);
    addEdge(4, 5);

    BFS(0, n);
    DFS(0, n);

    return 0;
}