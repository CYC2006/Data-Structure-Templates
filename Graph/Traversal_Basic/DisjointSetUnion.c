#include <stdio.h>
#include <stdlib.h>

// Disjoint Set Union (DSU)

#define MAXN 200005

int parent[MAXN]; // store parent of each element
int sz[MAXN];
int components; // current Union count

// initialize DSU
void initDSU(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    components = n;
}

// find the first ancestor (parent's parent's parent ...)
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

// unite two unions
int dsu_union(int a, int b) {
    a = find(a);
    b = find(b);

    // Cycle found
    if (a == b) return 0;

    // Union by size
    if (sz[a] < sz[b]) {
        int t = a; a = b; b = t;
    }
    parent[b] = a;
    sz[a] += sz[b];
    components--;
    return 1;
}

int main() {
    int n = 6;
    int edges[][2] = {
        {1, 2},
        {2, 3},
        {3, 1}, // cycle here
        {4, 5}
    };
    int m = 4;
    
    initDSU(n);

    // cycle detect
    int hasCycle = 0;
    for (int i = 0; i < m; i++) {
        if (!dsu_union(edges[i][0], edges[i][1])) {
            hasCycle = 1;
        }
    }

    if (hasCycle)
        printf("Cycle detected\n");
    else
        printf("No cycle\n");


    // components count
    printf("Components Count: %d\n", components);

    return 0;
}