#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXM 400005
typedef long long ll;

typedef struct Edge {
    int u, v;
    ll w;
} Edge;


Edge edges[MAXM];
int M = 0;

// Disjoint Set Union
int parent_[MAXN];
int sz_[MAXN];

void dsu_init(int n) {
    for (int i = 1; i <= n; i++) {
        parent_[i] = i;
        sz_[i] = 1;
    }
}

int dsu_find(int x) {
    if (parent_[x] != x) parent_[x] = dsu_find(parent_[x]);
    return parent_[x];
}

int dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (a == b) return 0;
    if (sz_[a] < sz_[b]) { int t = a; a = b; b = t; } // swap
    parent_[b] = a;
    sz_[a] += sz_[b];
    return 1;
}

// sort comparator
int cmp_edge(const void *A, const void *B) {
    const Edge *x = (const Edge*)A;
    const Edge *y = (const Edge*)B;
    if (x->w < y->w) return -1;
    if (x->w > y->w) return 1;
    return 0 ;
}

ll kruskal_mst(int n, int m) {
    qsort(edges, m, sizeof(Edge), cmp_edge);
    dsu_init(n);

    ll total = 0;
    int picked = 0;

    for (int i = 0; i < m && picked < n - 1; i++) {
        if (dsu_unite(edges[i].u, edges[i].v)) {
            total += edges[i].w;
            picked++;
        }
    }

    if (picked != n - 1) return -1;
    return total;
}

void add_edge(int u, int v, ll w) {
    edges[M].u = u;
    edges[M].v = v;
    edges[M].w = w;
    M++;
}

int main() {
    int N = 7; // node count
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

    ll ans = kruskal_mst(N, M);
    if (ans == -1) { printf("-1\n"); }
    else printf("MST total weight: %lld\n", ans);

    return 0;
}