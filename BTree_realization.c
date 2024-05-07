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

