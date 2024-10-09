# Data Structures Project

This repository contains solutions for two programming problems related to data structures in C.

## Problem A: Check if a Singly Linked List Has a Cycle

### Description
Implement a function to detect if a singly linked list contains a cycle.

### Files
- `ll_cycle.c`
- `ll_cycle.h`
- `test_ll_cycle.c`

### Task
Complete the `ll_has_cycle()` function in `ll_cycle.c`. The function should return 1 if a cycle exists and 0 if no cycle exists.

### Compilation
Create a Makefile that compiles the code with the following flags: `-Wall -Wextra -Wpedantic`

### Execution
Run the executable with `./check_cycle`

## Problem B: Growing Arrays

### Description
Implement four functions to manage a growable array of student records.

### Files
- `growing_arrays.c`
- `growing_arrays.h`
- `test_growing_arrays.c` 

### Functions to Implement
1. `int add_record(Record new_record)`
2. `int del_record(const char *name)`
3. `int get_id(const char *name)`
4. `Record get_record(int index)`

### Compilation
Create a Makefile that compiles the code with the following flags: `-Wall -Wextra -Wpedantic`

### Execution
The target name should be `growing_arrays`

## Repository Structure
```
.
├── Problem A
│   ├── ll_cycle.c
│   ├── ll_cycle.h
│   ├── test_ll_cycle.c
│   └── Makefile
└── Problem B
    ├── growing_arrays.c
    ├── growing_arrays.h
    ├── test_growing_arrays.c (optional)
    └── Makefile
```
