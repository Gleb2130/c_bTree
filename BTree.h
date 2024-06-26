#ifndef BTree_H
#define BTree_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    time_t time; 
    int value;
    struct Node* left;
    struct Node* right;

    int subtreeSum;
    int subtreeMin;
    int subtreeMax;
    int subtreeCount;
} Node;

// Create a new tree node
void createNode(Node** node, time_t time, int value);

// Insert a node into the tree
Node* insertNode(Node* root, time_t time, int value);

// Edit node
void editNode(Node* root, time_t time, int newValue);

// Removing a node from the tree
Node* deleteNode(Node* root, time_t time);

// Search for a node in the tree by value
Node* searchNode(Node* root, time_t time);
Node* searchNodeValue(Node* root, int value);

// Print all nodes of the tree in ascending order
void printInOrder(Node* root);

// Freeing memory occupied by tree nodes
void freeTree(Node* root);

typedef struct BTree {
    Node* root;
    int count;
} BTree;

// Creating a new tree
BTree* createBTree();

// Insert a node into the tree
void insertBNode(BTree* btree, time_t time, int value);

// Removing a node from the tree
void deleteBNode(BTree* btree, time_t time);

// Search for a node in the tree by value
Node* searchBNode(BTree* btree, time_t time);
Node* searchBNodeValue(BTree* btree, int value);

// Print node values in ascending order
void printBInOrder(BTree* btree);

// Freeing the memory occupied by the tree
void freeBTree(BTree* btree);


typedef struct TimeIntervalData {
    int sum;        // Sum of values in the interval
    int min;        // Minimum value in the interval
    int max;        // Maximum value in the interval
    int count;      // Number of values in the interval
} TimeIntervalData;


// Function for traversing the tree and calculating the sum, minimum and maximum values in the specified time interval
void calculateTimeIntervalData(Node* root, TimeIntervalData* intervalData, time_t t1, time_t t2);

// Function for calculating the average value in the specified time interval
double calculateTimeIntervalAverage(Node* root, time_t t1, time_t t2);

// Function for calculating the minimum value in the specified time interval
int calculateTimeIntervalMinimum(Node* root, time_t t1, time_t t2);

// Function for calculating the maximum value in the specified time interval
int calculateTimeIntervalMaximum(Node* root, time_t t1, time_t t2);

// Function for performing operations on a tree in a specified time interval and outputting the results
void performOperationsAndPrintResult(BTree* btree);

#endif /* BTree_H */
