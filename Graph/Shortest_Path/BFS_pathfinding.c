#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int R, C;
int grid[MAXN][MAXN];
int dist[MAXN][MAXN];

typedef struct Node {
    int r;
    int c;
} Node;

Node parent[MAXN][MAXN];

Node q[MAXN * MAXN];
int head = 0;
int tail = 0;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void bfs(int sr, int sc) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            dist[i][j] = -1;
        }
    }

    dist[sr][sc] = 0;
    parent[sr][sc] = (Node){ -1, -1 }; // start has no parent
    q[tail++] = (Node){ sr, sc };

    while (head < tail) {
        Node curr = q[head++];

        for (int k = 0; k < 4; k++) {
            int nr = curr.r + dr[k];
            int nc = curr.c + dc[k];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == 1) continue; // 0 is free, 1 is wall
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[curr.r][curr.c] + 1;
            parent[nr][nc] = curr; // record parent
            q[tail++] = (Node){ nr, nc };
        }
    }
}


void printPath(int tr, int tc) {
    Node path[10000];
    int len = 0;

    Node curr = (Node) {tr, tc};

    while (curr.r != -1 && curr.c != -1) {
        path[len++] = curr;
        curr = parent[curr.r][curr.c];
    }

    printf("Path: ");
    for (int i = len - 1; i >= 0; i--) {
        printf("(%d, %d) ", path[i].r, path[i].c);
    }
    printf("\n");
}


int main() {
    R = 5; C = 6;
    int temp[5][6] = {
        {0,0,1,0,0,0},
        {0,1,0,0,1,0},
        {0,0,0,1,0,0},
        {1,0,0,0,0,1},
        {0,0,1,0,0,0}
    };

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = temp[i][j];
        }
    }

    int sr = 0, sc = 0; // start point
    int tr = 4, tc = 5; // target

    bfs(sr, sc);

    if (dist[tr][tc] == -1) { printf("No Path Found\n"); }
    else {
        printf("Shortest Path Distance: %d\n", dist[tr][tc]);
        printPath(tr, tc);
    }
    
    return 0;
}