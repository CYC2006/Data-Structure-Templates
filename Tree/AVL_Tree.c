#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// Utility Functions

int height(Node *n) {
    return (n == NULL) ? 0 : n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

// Rotations
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}
/*
        y                  x
       / \                / \
      x   T3    --->    T1   y
     / \                    / \
    T1  T2                 T2  T3
*/

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right));
    y->height = max(height(y->left), height(y->right));

    return y;
}

// Balance Factor
int getBalance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

// Get min Node (successor for deletion)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

// Insert
Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node; // duplicates not allowed

    node->height = 1 + max(height(node->left), height(node->right));

    // 4 cases: LL RR LR RL
    // two ways of if-statement: key < node->left->key == getBalance(node->left) >= 0
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);

    if (balance < -1 && key > node->right->key) return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Delete
Node* delete(Node* root, int key) {
    // (A) Standard BST Deletion
    if (root == NULL) return root;

    if (key < root->key) root->left = delete(root->left, key);

    else if (key > root->key) root->right = delete(root->right, key);

    else { // found the deletion key
        // Not child or One child
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) { // No child
                temp = root;
                root = NULL;
            }
            else *root = *temp; // One child

            free(temp);
        }
        // Two childs
        else {
            Node* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = delete(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    // (B) Update Height
    root->height = 1 + max(height(root->left), height(root->right));

    // (C) AVL Rebalance (4 cases)
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = leftRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Traversal
void inorderTraversal(Node *root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->key);
    inorderTraversal(root->right);
}

// test
int main() {
    Node *root = NULL;

    int values[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(values) / sizeof(values[0]);

    // Test Insertion
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Inorder Traversal (after insert): ");
    inorderTraversal(root);
    printf("\n");

    // Test deletion
    root = delete(root, 40);
    root = delete(root, 25);
    root = delete(root, 10);

    printf("Inorder Traversal (after delete): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}