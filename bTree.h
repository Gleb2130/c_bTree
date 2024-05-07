#ifndef BTree_H
#define BTree_H


typedef struct Node {
    int value;
    int time;
    struct Node* left;
    struct Node* right;
} Node;



#endif 
