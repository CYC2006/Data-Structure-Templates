#include <stdio.h>
#include <stdlib.h>

// NPL Leftist Tree (min tree)
// another type of Lefist Tree is Weight-Based Leftist Tree

typedef struct Node {
    int key;
    int dist;
    struct Node *left, *right;
} Node;


Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = val;
    n->dist = 1; // NPL (null path length)
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Merge two trees
Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    // ensure a is smaller
    if (a->key > b->key) {
        Node* temp = a;
        a = b;
        b = temp;
    }

    // merge b into a->right subtree
    a->right = merge(a->right, b);

    // maintain leftist property: dist(left) >= right(dist)
    int distL = a->left ? a->left->dist : 0;
    int distR = a->right ? a->right->dist : 0;

    if (distL < distR) {
        Node* temp = a->left;
        a->left = a->right;
        a->right = temp;
    }

    a->dist = (a->right ? a->right->dist : 0) + 1;
    return a;
}

// Merge tree and newNode
Node* insert(Node* root, int x) {
    Node* node = newNode(x);
    return merge(root, node);
}

Node* deleteMin(Node* root) {
    if (!root) return NULL;
    Node* newRoot = merge(root->left, root->right);
    free(root);
    return newRoot;
}

int top(Node* root) {
    return root->key;
}


int main() {
    Node* heap = NULL;

    heap = insert(heap, 5);
    heap = insert(heap, 2);
    heap = insert(heap, 7);
    heap = insert(heap, 1);

    printf("Top = %d\n", top(heap));  // 1

    heap = deleteMin(heap);
    printf("Top = %d\n", top(heap));  // 2

    return 0;
}