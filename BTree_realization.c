#include "BTree.h"


void createNode(Node* node,int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node != NULL) {
		node->value = value;
		node->time = time(NULL);
		node->left = NULL;
		node->right = NULL;
	}
}

Node* insertNode(Node* root, int value, int time) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode != NULL) {
            newNode->value = value;
            newNode->time = time;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        else {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (value < root->value) {
        root->left = insertNode(root->left, value, time);
    }
    else if (value > root->value) {
        root->right = insertNode(root->right, value, time);
    }
    return root;
}