#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#pragma warning(disable:4996)

#include "BTree.h"


int main() {
    srand(time(NULL));

    BTree* btree = createBTree();

    printf("Inserting nodes...\n");
    for (int i = 0; i < 10; i++) {
        time_t timestamp = time(NULL) + i;
        int value = rand() % 100 - 50;
        insertBNode(btree, timestamp, value);
    }

    printf("\nNodes in ascending order:\n");
    printBInOrder(btree);
    printf("\n");

    time_t searchTime;
    printf("Enter time for searching (timestamp): ");
    scanf("%ld", &searchTime);

    int choice = 0;
    do {
        printf("Enter:\n1 <- value\n2 <- time\n");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 2);

    Node* searchedNode = NULL;
    switch (choice) {
    case 1:
        searchedNode = searchBNodeValue(btree, (int)searchTime);
        break;
    case 2:
        searchedNode = searchBNode(btree, searchTime);
        break;
    }

    if (searchedNode != NULL) {
        printf("Node with time %ld found. Value: %d\n", searchedNode->time, searchedNode->value);
    }
    else {
        switch (choice) {
        case 1:
            printf("Node with value %ld not found.\n", searchTime);
            break;
        case 2:
            printf("Node with time %ld not found.\n", searchTime);
            break;
        }
    }

    printf("Enter time to delete (timestamp): ");
    scanf("%ld", &searchTime);
    printf("\nDeleting node with time %ld...\n", searchTime);
    deleteBNode(btree, searchTime);
    printf("Tree after deletion:\n");
    printBInOrder(btree);
    printf("\n");

    printf("Statistics for the specified time interval:\n");
    performOperationsAndPrintResult(btree);
    printf("\n");

    freeBTree(btree);

    return 0;
}
