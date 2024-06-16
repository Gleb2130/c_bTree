# BTree Implementation

This repository contains an implementation of a binary search tree (BTree) in C programming language.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)

## Description

The BTree implementation provides a simple binary search tree data structure with basic operations such as insertion, deletion, searching, and printing in order.

## Features

- Insertion of nodes with unique keys
- Deletion of nodes by key
- Searching for nodes by key or value
- Printing nodes in ascending order of keys
- Calculation of statistics within a specified time interval

## Usage

To use the BTree implementation in your project, include the `BTree.h` header file and link it with the appropriate source files.

## Examples

<details>
  <summary>Inserting Nodes</summary>

  ```c
  // Insert nodes into the tree
  for (int i = 0; i < 10; i++) {
      int key = i; // Use the index as the key
      int value = rand() % 100 - 50;
      insertBNode(btree, key, value);
  }
  ```

  **Output:**
  ```
  Nodes in ascending order:
  Key: 0, Value: -12, Time: 2024-05-11 15:40:20
  Key: 1, Value: -24, Time: 2024-05-11 15:40:20
  Key: 2, Value: 34, Time: 2024-05-11 15:40:20
  Key: 3, Value: 48, Time: 2024-05-11 15:40:20
  Key: 4, Value: 44, Time: 2024-05-11 15:40:20
  Key: 5, Value: 45, Time: 2024-05-11 15:40:20
  Key: 6, Value: 21, Time: 2024-05-11 15:40:20
  Key: 7, Value: 14, Time: 2024-05-11 15:40:20
  Key: 8, Value: 11, Time: 2024-05-11 15:40:20
  Key: 9, Value: 48, Time: 2024-05-11 15:40:20
  ```

</details>

<details>
  <summary>Searching for a Node</summary>

  ```c
  // Search for a node by key
  Node* searchedNode = searchBNode(btree, searchKeyValue);
  ```

  **Output:**  
  ```
  Node with key 5 found. Value: 45
  ```

</details>

<details>
  <summary>Deleting a Node</summary>

  ```c
  // Delete a node by key
  deleteBNode(btree, searchKeyValue);
  ```

  **Output:**
  ```
  Tree after deletion:
  Key: 0, Value: -12, Time: 2024-05-11 15:40:20
  Key: 1, Value: -24, Time: 2024-05-11 15:40:20
  Key: 2, Value: 34, Time: 2024-05-11 15:40:20
  Key: 3, Value: 48, Time: 2024-05-11 15:40:20
  Key: 4, Value: 44, Time: 2024-05-11 15:40:20
  Key: 6, Value: 21, Time: 2024-05-11 15:40:20
  Key: 7, Value: 14, Time: 2024-05-11 15:40:20
  Key: 8, Value: 11, Time: 2024-05-11 15:40:20
  Key: 9, Value: 48, Time: 2024-05-11 15:40:20
  ```

</details>

<details>
  <summary>Performing Operations within a Time Interval</summary>

  ```c
  // Perform operations within a specified time interval and print the results
  performOperationsAndPrintResult(btree);
  ```

  **Output:**  
  ```
  Statistics for the specified time interval:
  Average: 29.60
  Minimum: -24
  Maximum: 48
  ```

</details>

## Contributing

Contributions to this project are welcome! Please feel free to submit issues and pull requests.
