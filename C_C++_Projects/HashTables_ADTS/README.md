# Data Structures and ADTs Project

This project implements three Abstract Data Types (ADTs) in C: Set, Hash Table, and Least Recently Used (LRU) Cache. Each part builds upon the previous, demonstrating the application of fundamental data structures and their optimizations.

## Table of Contents
1. [Part A: Set ADT](#part-a-set-adt)
2. [Part B: Hash Table ADT](#part-b-hash-table-adt)
3. [Part C: Least Recently Used (LRU) Cache](#part-c-least-recently-used-lru-cache)
4. [Compilation Instructions](#compilation-instructions)
5. [Testing](#testing)
6. [File Structure](#file-structure)

## Part A: Set ADT

### Description
Implement a Set ADT that maintains an unordered collection of (key, item) pairs, where keys are unique.

### Implementation Details
- File: `set.c`
- Header: `set.h` (provided)
- Key-Item Pair Type: `(char*, void*)`
- Behavior: Starts empty, grows as items are inserted
- Operations: Insert, Retrieve, Cannot Remove or Update

### Required Functions
Implement the following functions as declared in `set.h`:
- `Set* Set_new()`
- `void Set_free(Set* set)`
- `void Set_insert(Set* set, const char* key, void* item)`
- `void* Set_find(Set* set, const char* key)`
- `void Set_print(Set* set)`
- `void Set_iterate(Set* set, void (*itemfunc)(const char* key, void* item))`

### Compilation
```
gcc -Wall -Wextra set.c test_set.c -o test_set
```

## Part B: Hash Table ADT

### Description
Implement a Hash Table ADT that functions like the Set ADT but with improved efficiency for large collections.

### Implementation Details
- File: `hashtable.c`
- Header: `hashtable.h` (provided)
- Key-Item Pair Type: `(char*, void*)`
- Structure: Array of Sets
- Hashing: Choose any algorithm (e.g., treating key as integer and using modulus)

### Required Functions
Implement the following functions as declared in `hashtable.h`:
- `Hashtable* Hashtable_new(int num_bins)`
- `void Hashtable_free(Hashtable* ht)`
- `void Hashtable_insert(Hashtable* ht, const char* key, void* item)`
- `void* Hashtable_find(Hashtable* ht, const char* key)`
- `void Hashtable_print(Hashtable* ht)`
- `void Hashtable_iterate(Hashtable* ht, void (*itemfunc)(const char* key, void* item))`

### Compilation
```
gcc -Wall -Wextra set.c hashtable.c test_hashtable.c -o test_hashtable
```

## Part C: Least Recently Used (LRU) Cache

### Description
Implement an LRU Cache ADT with limited capacity that discards the least recently used item when full.

### Implementation Details
- File: `lru.c`
- Header: `lru.h` (provided)
- Functionality: Similar to Set ADT
- Capacity: Limited, specified at creation
- Behavior: Removes least recently used item when full

### Required Functions
Implement the following functions as declared in `lru.h`:
- `LRU* LRU_new(int capacity)`
- `void LRU_free(LRU* lru)`
- `void LRU_insert(LRU* lru, const char* key, void* item)`
- `void* LRU_find(LRU* lru, const char* key)`
- `void LRU_print(LRU* lru)`
- `void LRU_iterate(LRU* lru, void (*itemfunc)(const char* key, void* item))`
- `void LRU_delete(LRU* lru)`

### Implementation Notes
- You may use Set and/or Hash Table ADTs in your LRU implementation
- Keep track of the number of elements and the maximum capacity
- Update "used" status on insert and find operations

### Compilation
See the [Compilation Instructions](#compilation-instructions) section below.

## Compilation Instructions

For Part A and Part B, use the compilation commands provided in their respective sections.

For Part C (LRU Cache), the compilation command depends on your implementation choices. Please use the following command, adjusting it based on which ADTs you've used in your LRU implementation:

```
gcc -Wall -Wextra set.c hashtable.c lru.c test_lru.c -o test_lru
```

If you've only used one of the ADTs or neither, adjust the command accordingly by removing the unnecessary .c files.

## Testing

Each part comes with a provided test file:
- Part A: `test_set.c`
- Part B: `test_hashtable.c`
- Part C: `test_lru.c`

Run the compiled executables to test your implementations:
```
./test_set
./test_hashtable
./test_lru
```

## File Structure

Your project should have the following file structure:

```
.
├── set.c
├── set.h
├── test_set.c
├── hashtable.c
├── hashtable.h
├── test_hashtable.c
├── lru.c
├── lru.h
├── test_lru.c
└── README.md
```

Ensure all files are in the same directory for easy compilation and testing.
