#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXM 200005

// array adjacency
// head and next is like prev and curr
int head[MAXN];   // edge // node i's first edge
int to[MAXM];     // node // node which edge i points to
int next[MAXM];   // edge // edge i's next edge
int ec;           // ec edge count
int indeg[MAXN];  // node i's in-degree

int q[MAXN];

void addEdge(int u, int v) {
    to[ec] = v;
    next[ec] = head[u];
    head[u] = ec;
    ec++;
}

int main() {
    int N, M;
    scanf(" %d %d", &N, &M);

    // initialize
    for (int i = 0; i < N; i++) {
        head[i] = -1;
        indeg[i] = 0;
    }

    // add edges
    int u, v;
    for (int i = 0; i < M; i++) {
        scanf(" %d %d", &u, &v);
        addEdge(u, v);
        indeg[v]++;
    }

    // enqueue nodes with indegree 0
    int front = 0;
    int rear = 0;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) q[rear++] = i;
    }

    int count = 0;
    while (front < rear) {
        int curr = q[front++];
        printf("%d ", curr);
        count++;

        for (int e = head[curr]; e != -1; e = next[e]) {
            int nextNode = to[e];
            if (--indeg[nextNode] == 0) q[rear++] = nextNode;
        }
    }

    if (count != N) printf("Cycle detected\n");
    else printf("\n");

    return 0;
}