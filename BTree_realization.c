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

void createNode(Node** node, time_t time, int value) {
    *node = (Node*)malloc(sizeof(Node));
    if (*node != NULL) {
        (*node)->time = time;
        (*node)->value = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
        (*node)->subtreeSum = value;
        (*node)->subtreeMin = value;
        (*node)->subtreeMax = value;
        (*node)->subtreeCount = 1;
    } else {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
}


void updateSubtreeInfo(Node* node) {
    if (node == NULL) return;
    node->subtreeSum = node->value;
    node->subtreeMin = node->value;
    node->subtreeMax = node->value;
    node->subtreeCount = 1;
    if (node->left != NULL) {
        node->subtreeSum += node->left->subtreeSum;
        node->subtreeMin = (node->subtreeMin > node->left->subtreeMin) ? node->left->subtreeMin : node->subtreeMin;
        node->subtreeMax = (node->subtreeMax < node->left->subtreeMax) ? node->left->subtreeMax : node->subtreeMax;
        node->subtreeCount += node->left->subtreeCount;
    }
    if (node->right != NULL) {
        node->subtreeSum += node->right->subtreeSum;
        node->subtreeMin = (node->subtreeMin > node->right->subtreeMin) ? node->right->subtreeMin : node->subtreeMin;
        node->subtreeMax = (node->subtreeMax < node->right->subtreeMax) ? node->right->subtreeMax : node->subtreeMax;
        node->subtreeCount += node->right->subtreeCount;
    }
}

Node* insertNode(Node* root, time_t time, int value) {
    if (root == NULL) {
        createNode(&root, time, value);
        return root;
    }
    if (time < root->time) {
        root->left = insertNode(root->left, time, value);
    }
    else if (time > root->time) {
        root->right = insertNode(root->right, time, value);
    }
    root->subtreeSum = root->value +
        (root->left ? root->left->subtreeSum : 0) +
        (root->right ? root->right->subtreeSum : 0);
    root->subtreeMin = root->value;
    if (root->left) root->subtreeMin = (root->subtreeMin < root->left->subtreeMin) ? root->subtreeMin : root->left->subtreeMin;
    if (root->right) root->subtreeMin = (root->subtreeMin < root->right->subtreeMin) ? root->subtreeMin : root->right->subtreeMin;
    root->subtreeMax = root->value;
    if (root->left) root->subtreeMax = (root->subtreeMax > root->left->subtreeMax) ? root->subtreeMax : root->left->subtreeMax;
    if (root->right) root->subtreeMax = (root->subtreeMax > root->right->subtreeMax) ? root->subtreeMax : root->right->subtreeMax;
    root->subtreeCount = 1 +
        (root->left ? root->left->subtreeCount : 0) +
        (root->right ? root->right->subtreeCount : 0);
    return root;
}

void editNode(Node* root, time_t time, int newValue) {
    Node* nodeToUpdate = searchNode(root, time);
    if (nodeToUpdate != NULL) {
        nodeToUpdate->value = newValue;
        updateSubtreeInfo(nodeToUpdate);
    }
    else {
        fprintf(stderr, "Node with time %ld not found.\n", time);
    }
}

Node* minValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, time_t time) {
    if (root == NULL) {
        return root;
    }
    if (time < root->time) {
        root->left = deleteNode(root->left, time);
    }
    else if (time > root->time) {
        root->right = deleteNode(root->right, time);
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
        root->time = temp->time;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->time);
    }
    root->subtreeSum = root->value +
        (root->left ? root->left->subtreeSum : 0) +
        (root->right ? root->right->subtreeSum : 0);
    root->subtreeMin = root->value;
    if (root->left) root->subtreeMin = (root->subtreeMin < root->left->subtreeMin) ? root->subtreeMin : root->left->subtreeMin;
    if (root->right) root->subtreeMin = (root->subtreeMin < root->right->subtreeMin) ? root->subtreeMin : root->right->subtreeMin;
    root->subtreeMax = root->value;
    if (root->left) root->subtreeMax = (root->subtreeMax > root->left->subtreeMax) ? root->subtreeMax : root->left->subtreeMax;
    if (root->right) root->subtreeMax = (root->subtreeMax > root->right->subtreeMax) ? root->subtreeMax : root->right->subtreeMax;
    root->subtreeCount = 1 +
        (root->left ? root->left->subtreeCount : 0) +
        (root->right ? root->right->subtreeCount : 0);
    return root;
}


Node* searchNode(Node* root, time_t time) {
    if (root == NULL || root->time == time) {
        return root;
    }
    if (time < root->time) {
        return searchNode(root->left, time);
    }
    return searchNode(root->right, time);
}

Node* searchNodeValue(Node* root, int value) {
    if (root == NULL || root->value == value) {
        return root;
    }
    Node* foundNode = searchNodeValue(root->left, value);
    if (foundNode == NULL) {
        foundNode = searchNodeValue(root->right, value);
    }
    return foundNode;
}

void printInOrder(Node* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("Time: ");
    printFormattedTime(root->time);
    printf("Value: %d\n", root->value);
    printf("Subtree Sum: %d\n", root->subtreeSum);
    printf("Subtree Min: %d\n", root->subtreeMin);
    printf("Subtree Max: %d\n", root->subtreeMax);
    printf("Subtree Count: %d\n", root->subtreeCount);
    printf("\n");
    printInOrder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

BTree* createBTree() {
    BTree* btree = (BTree*)malloc(sizeof(BTree));
    if (btree != NULL) {
        btree->root = NULL;
        btree->count = 0;
    }
    else {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    return btree;
}

void insertBNode(BTree* btree, time_t time, int value) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    btree->root = insertNode(btree->root, time, value);
    btree->count++;
}


void deleteBNode(BTree* btree, time_t time) {
    if (btree == NULL) {
        fprintf(stderr, "Invalid BTree.\n");
        exit(EXIT_FAILURE);
    }
    btree->root = deleteNode(btree->root, time);
    btree->count--;
}


Node* searchBNode(BTree* btree, time_t time) {
    return searchNode(btree->root, time);
}

Node* searchBNodeValue(BTree* btree, int value) {
    return searchNodeValue(btree->root, value);
}

void printBInOrder(BTree* btree) {
    printInOrder(btree->root);
}

void freeBTree(BTree* btree) {
    freeTree(btree->root);
    free(btree);
}

void calculateTimeIntervalData(Node* root, TimeIntervalData* intervalData, time_t t1, time_t t2) {
    if (root == NULL) {
        return;
    }

    if (root->time >= t1 && root->time <= t2) {
        intervalData->sum += root->value;
        intervalData->min = (intervalData->min > root->value) ? root->value : intervalData->min;
        intervalData->max = (intervalData->max < root->value) ? root->value : intervalData->max;
        intervalData->count++;
    }

    if (root->left && root->left->subtreeMax >= t1) {
        calculateTimeIntervalData(root->left, intervalData, t1, t2);
    }

    if (root->right && root->right->subtreeMin <= t2) {
        calculateTimeIntervalData(root->right, intervalData, t1, t2);
    }
}


double calculateTimeIntervalAverage(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(root, &intervalData, t1, t2);
    return (intervalData.count > 0) ? (double)intervalData.sum / intervalData.count : 0.0;
}

int calculateTimeIntervalMinimum(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(root, &intervalData, t1, t2);
    return (intervalData.count > 0) ? intervalData.min : INT_MAX;
}

int calculateTimeIntervalMaximum(Node* root, time_t t1, time_t t2) {
    TimeIntervalData intervalData = { 0, INT_MAX, INT_MIN, 0 };
    calculateTimeIntervalData(root, &intervalData, t1, t2);
    return (intervalData.count > 0) ? intervalData.max : INT_MIN;
}

void performOperationsAndPrintResult(BTree* btree) {
    if (btree == NULL || btree->root == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    time_t t1, t2;
    printf("Enter start of time interval (timestamp): ");
    scanf("%ld", &t1);
    printf("Enter end of time interval (timestamp): ");
    scanf("%ld", &t2);

    double average = calculateTimeIntervalAverage(btree->root, t1, t2);
    int min = calculateTimeIntervalMinimum(btree->root, t1, t2);
    int max = calculateTimeIntervalMaximum(btree->root, t1, t2);

    printf("For the time interval [%ld, %ld]:\n", t1, t2);
    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
}

