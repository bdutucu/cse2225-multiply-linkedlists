# cse2225-multiply-linkedlists

This repository contains an implementation in C for performing arithmetic operations (such as addition) on large numbers represented by doubly linked lists. The project is suitable for coursework or assignments related to data structures, especially focusing on linked lists and their applications in handling large numbers beyond standard data type limits.

## Features

- **Doubly Linked List Data Structure:**  
  Numbers are stored as linked lists where each node represents a digit (or character).
- **Dynamic Memory Management:**  
  Nodes are dynamically allocated and freed to handle numbers of arbitrary size.
- **Addition Functionality:**  
  Includes an `addition` function for adding two numbers represented by linked lists.
- **List Manipulation Utilities:**  
  - `append`: Add new digits to the end of the list.
  - `reverseLinkedList`: Reverse the linked list in place.
  - `displayList` and `displayReverseList`: Print the list forward and backward.
  - `freeList`: Free all allocated memory.

## File Overview

- `150124830_prj1.c`  
  Main source file containing definitions for all core linked list operations and the addition logic.
- `tempCodeRunnerFile.c`  
  Temporary or test file (contains sample includes, may not be central to the project).

## How It Works

1. **Creating Numbers:**  
   Numbers are constructed by appending digits to a linked list.
2. **Arithmetic Operations:**  
   The addition function traverses both lists from tail to head (least to most significant digit), handling carries as needed.
3. **Reversing and Displaying:**  
   Utility functions allow you to reverse the linked list and display numbers in both directions.

## Example Usage

```c
Node *num1 = NULL, *tail1 = NULL;
Node *num2 = NULL, *tail2 = NULL;
Node *result = NULL, *tailResult = NULL;

// Building the numbers
append(&num1, &tail1, '1');
append(&num1, &tail1, '2');
append(&num2, &tail2, '3');
append(&num2, &tail2, '4');

// Adding the numbers
addition(tail1, tail2, &result, &tailResult);

// Displaying the result
displayList(result, stdout);

// Freeing memory
freeList(num1);
freeList(num2);
freeList(result);
