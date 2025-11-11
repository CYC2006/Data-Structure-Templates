#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);
    if(key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* delete(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = delete(root->left, key);
    else if (key > root->key) root->right = delete(root->right, key);
    else {
        if (!root->left) {
            Node* r = root->right;
            free(root);
            return r;
        }
        else if (!root->right) {
            Node* r = root->right;
            free(root);
            return r;
        }
        Node* node = findMin(root->right);
        root->key = node->key;
        root->right = delete(root->right, node->key);
    }
    return root;
}

// preorder traversal
void preorder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// inorder tranversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// postorder traversal
void postorder(Node* root)
 {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
 }
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 80);
    root = insert(root, 10);
    root = insert(root, 40);
    root = insert(root, 90);
    root = insert(root, 70);
    root = insert(root, 20);

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    root = delete(root, 50);
    printf("After deleting 50: ");
    inorder(root);
    printf("\n");

    freeTree(root);

    return 0;
}