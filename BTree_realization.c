#include "BTree.h"


void createNode(Node** node, int key, int value) {
    *node = (Node*)malloc(sizeof(Node));
    if (*node != NULL) {
        (*node)->key = key;
        (*node)->value = value;
        (*node)->time = time(NULL);
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
    else {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
}


Node* insertNode(Node* root, int key, int value, int time) {
    if (root == NULL) {
        createNode(&root, key, value);
        return root;
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key, value, time);
    }
    else if (key > root->key) {
        root->right = insertNode(root->right, key, value, time);
    }
    return root;
}



Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->value = temp->value;
        root->time = temp->time;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

Node* searchNode(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Key: %d, Value: %d, Time: %lld\n", root->key, root->value, (long long)root->time);
        printInOrder(root->right);
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}



////BTree


BTree* createBTree() {
    BTree* btree = (BTree*)malloc(sizeof(BTree));
    if (btree != NULL) {
        btree->root = NULL;
        btree->count = 0;
        return btree;
    }
    else {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
}