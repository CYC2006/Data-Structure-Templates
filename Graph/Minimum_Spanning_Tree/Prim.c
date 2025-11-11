#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 7
#define MAXM 20

typedef long long ll;

typedef struct {
    int v;
    ll w;
} Edge;

Edge graph[N][N];
int deg[N] = {0};

ll INF = 1e18;

typedef struct Node {
    int v;
    ll w;
} Node;

Node heap[1000];
int hsz = 0; // heap size
void swap(Node *a, Node *b) {
    Node t = *a; *a = *b; *b = t;
}

void push(Node x) {
    heap[++hsz] = x;
    int curr = hsz;
    while (curr > 1 && heap[curr].w < heap[curr/2].w) {
        swap(&heap[curr], &heap[curr/2]);
        curr /= 2;
    }
}

Node pop() {
    Node top = heap[1];
    heap[1] = heap[hsz--];

    int curr = 1;
    while (1) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int best = curr;
        if (left <= hsz && heap[left].w < heap[best].w) best = left;
        if (right <= hsz && heap[right].w < heap[best].w) best = right;
        if (best == curr) break;
        swap(&heap[curr], &heap[best]);
        curr = best;
    }
    return top;
}

void add_edge(int u, int v, ll w) {
    graph[u][deg[u]].v = v;
    graph[u][deg[u]].w = w;
    deg[u]++;

    graph[v][deg[v]].v = v;
    graph[v][deg[v]].w = w;
    deg[v]++;
}

ll prim(int start) {
    int visited[N] = {0};
    ll total = 0;
    int count = 0;

    push((Node){start, 0});

    while (hsz && count < N) {
        Node top = pop();
        int v = top.v;
        ll w = top.w;
        if (visited[v]) continue;
        visited[v] = 1;
        total += w;
        count++;
        
        for (int i = 0; i < deg[v]; i++) {
            Edge e = graph[v][i];
            if (!visited[e.v]) {
                push((Node){e.v, e.w});
            }
        }
    }
    return total;
}

int main() {
    add_edge(0,1,7);
    add_edge(0,3,5);
    add_edge(1,2,8);
    add_edge(1,3,9);
    add_edge(1,4,7);
    add_edge(2,4,5);
    add_edge(3,4,15);
    add_edge(3,5,6);
    add_edge(4,5,8);
    add_edge(4,6,9);
    add_edge(5,6,11);

    printf("MST total weight (Prim) = %lld\n", prim(0));
    return 0;
}