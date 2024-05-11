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


Node* insertNode(Node* root, int key, int value) {
    if (root == NULL) {
        createNode(&root, key, value);
        return root;
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key, value);
    }
    else if (key > root->key) {
        root->right = insertNode(root->right, key, value);
    }
    root->time = time(NULL);
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

void insertBNode(BTree* btree, int key, int value, int time) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    btree->root = insertNode(btree->root, key, value, time);
    btree->count++;
}

void deleteBNode(BTree* btree, int key) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    btree->root = deleteNode(btree->root, key);
    btree->count--;
}

Node* searchBNode(BTree* btree, int key) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    return searchNode(btree->root, key);
}

void printBInOrder(BTree* btree) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    printInOrder(btree->root);
}

void freeBTree(BTree* btree) {
    if (btree != NULL) {
        freeTree(btree->root);
        free(btree);
    }
}

//// BTree interval statistics 

void calculateTimeIntervalData(Node* root, TimeIntervalData* intervalData, time_t t1, time_t t2) {
    if (root == NULL) {
        return;
    }

    calculateTimeIntervalData(root->left, intervalData, t1, t2);
    if (root->time >= t1 && root->time <= t2) {
        intervalData->sum += root->value;
        intervalData->min = (intervalData->min > root->value) ? root->value : intervalData->min;
        intervalData->max = (intervalData->max < root->value) ? root->value : intervalData->max;
        intervalData->count++;
    }
    calculateTimeIntervalData(root->right, intervalData, t1, t2);
}

double calculateTimeIntervalAverage(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 }; 
    calculateTimeIntervalData(root, &intervalData, t1, t2); 
    if (intervalData.count > 0) {
        return (double)intervalData.sum / intervalData.count;
    }
    else {
        return 0.0; 
    }
}


int calculateTimeIntervalMinimum(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(root, &intervalData, t1, t2);
    return (intervalData.count > 0) ? intervalData.min : 0;
}

int calculateTimeIntervalMaximum(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(root, &intervalData, t1, t2);
    return (intervalData.count > 0) ? intervalData.max : 0;
}

void performOperationsAndPrintResult(BTree* btree) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }

    time_t t1, t2;
    printf("Enter start time (in seconds since epoch): ");
    scanf("%lld", (long long*)&t1);
    printf("Enter end time (in seconds since epoch): ");
    scanf("%lld", (long long*)&t2);

    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(btree->root, &intervalData, t1, t2);

    printf("Average: %.2f\n", (double)intervalData.sum / intervalData.count);
    printf("Minimum: %d\n", intervalData.min);
    printf("Maximum: %d\n", intervalData.max);
}
