#ifndef BTree_H
#define BTree_H
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

typedef struct Node {
    int value;
    time_t  time;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new tree node
void createNode(Node* node, int value);

// Insert a node into the tree
Node* insertNode(Node* root, int value, int time);

// Removing a node from the tree
Node* deleteNode(Node* root, int value);

// Search for a node in the tree by value
Node* searchNode(Node* root, int value);

// Print all nodes of the tree in ascending order
void printInOrder(Node* root);

// Freeing memory occupied by tree nodes
void freeTree(Node* root);


typedef struct BTree {
    Node* root;
} Btree;


#endif 
