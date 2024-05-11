#include "BTree.h"
#pragma warning(disable:4996)

void printFormattedTime(time_t timestamp) {
    struct tm* tm_info;
    char buffer[26];

    tm_info = localtime(&timestamp);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("%s\n", buffer);
}
time_t convertTimeStringToSeconds() {
    int year, month, day, hour, minute, second;

    printf("Enter year: ");
    scanf("%d", &year);

    printf("Enter month: ");
    scanf("%d", &month);

    printf("Enter day: ");
    scanf("%d", &day);

    printf("Enter hour: ");
    scanf("%d", &hour);

    printf("Enter minute: ");
    scanf("%d", &minute);

    printf("Enter second: ");
    scanf("%d", &second);

    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    time_t t = mktime(&tm);
    if (t == -1) {
        fprintf(stderr, "Failed to convert time.\n");
        exit(EXIT_FAILURE);
    }

    return t;
}




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

void editNode(Node* root, int key, int newValue) {
    Node* nodeToUpdate = searchNode(root, key);
    if (nodeToUpdate != NULL) {
        nodeToUpdate->value = newValue;
    }
    else {
        fprintf(stderr, "Node with key %d not found.\n", key);
    }
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
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

Node* searchNodeValue(Node* root, int value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    if (value < root->value) {
        return searchNode(root->left, value);
    }
    return searchNode(root->right, value);
}

void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Key: %d, Value: %d, Time: ", root->key, root->value);
        printFormattedTime(root->time);
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

void insertBNode(BTree* btree, int key, int value) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    btree->root = insertNode(btree->root, key, value);
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

Node* searchBNodeValue(BTree* btree, int value) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    return searchNode(btree->root, value);
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

    printf("Enter start date: ");
    t1 = convertTimeStringToSeconds();

    printf("Enter end date: ");
    t2 = convertTimeStringToSeconds();

    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(btree->root, &intervalData, t1, t2);

    printf("Average: %.2f\n", (double)intervalData.sum / intervalData.count);
    printf("Minimum: %d\n", intervalData.min);
    printf("Maximum: %d\n", intervalData.max);
}
