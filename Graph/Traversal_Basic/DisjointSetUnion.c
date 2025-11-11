#include <stdio.h>
#include <stdlib.h>

// Disjoint Set Union (DSU)

#define MAXN 200005

int parent[MAXN]; // store parent of each element
int sz[MAXN];
int components; // current Union count

// initialize DSU
void initDSU(int n) {
    for (int i = 0; i <= n; i++) {
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

// check if in same union
int sameUnion(int a, int b) {
    return find(a) == find(b);
}

// unite two unions
void unite(int a, int b) {
    if (sameUnion(a, b)) return;

    if (sz[a] < sz[b]) { // swap parent: let sz[a] > sz[b]
        int temp = a;
        a = b;
        b = temp;
    }
    parent[b] = a;
    sz[a] += sz[b];
    components--;
}

int main() {
    int n = 6;
    initDSU(n);

    unite(1, 2);
    unite(2, 3);
    unite(4, 5);

    printf("Components Count: %d\n", components);

    return 0;
}