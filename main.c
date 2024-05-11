#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#pragma warning(disable:4996)
#include "BTree.h"

int main() {
    // Initialize the random number generator
    srand(time(NULL));

    // Create a tree
    BTree* btree = createBTree();

    // Insert nodes into the tree
    printf("Inserting nodes...\n");
    for (int i = 0; i < 10; i++) {
        int key = i; // Use the index as the key
        int value = rand() % 100 - 50;
        insertBNode(btree, key, value);
    }

    // Print nodes in ascending order of the key
    printf("\nNodes in ascending order:\n");
    printBInOrder(btree);
    printf("\n");

    // Search for a node
    int searchKeyValue = 0;

    printf("Enter value or key:");
    scanf("%d", &searchKeyValue);

    char choise = 0;
    
    do {
        printf("Enter:\n1 <- value\n2 <- key\n");
        scanf("%d", &choise);
    } while (choise < 1 || choise>2);

    Node* searchedNode = NULL;

    switch (choise) {
    case 1: searchedNode = searchBNode(btree, searchKeyValue); break;
    case 2: searchedNode = searchBNodeValue(btree, searchKeyValue); break;
    }

    if (searchedNode != NULL) {
        printf("Node with key %d found. Value: %d\n", searchedNode->key, searchedNode->value);
    }
    else {
        switch (choise) {
        case 1: printf("Node with value %d not found.\n", searchKeyValue); break;
        case 2: printf("Node with key %d not found.\n", searchKeyValue); break;
        }
    }

    // Delete a node
    printf("Enter key:");
    scanf("%d", &searchKeyValue);
    printf("\nDeleting node with key %d...\n", searchKeyValue);
    deleteBNode(btree, searchKeyValue);
    printf("Tree after deletion:\n");
    printBInOrder(btree);
    printf("\n");

    // Perform operations within a specified time interval and print the results
    printf("Statistics for the specified time interval:\n");
    performOperationsAndPrintResult(btree);
    printf("\n");

    // Free the memory occupied by the tree
    freeBTree(btree);

    return 0;
}
