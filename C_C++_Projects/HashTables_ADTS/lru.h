#include <stdbool.h>
#include <stdio.h>
#include "hashtable.h" // Include the hashtable header
#ifndef LRU_H_
#define LRU_H_

// Define the structure of an LRU cache node
typedef struct lru_node {
    char *key;
    void *item;
    struct lru_node *next; // Pointer to the next node (for a linked list)
    struct lru_node *prev; // Previous node pointer for doubly linked list
} lru_node_t;

// Define the structure of the LRU cache
typedef struct lru {
    lru_node_t *head; // Pointer to the head of the linked list
    lru_node_t *tail; // Pointer to the tail of the linked list
    int capacity;     // Maximum capacity of the LRU cache
    int size;         // Current size of the LRU cache
    hashtable_t *hashtable; // Pointer to the hashtable for quick lookups
} lru_t;



/* Create a new (empty) lru; return NULL if error. */
lru_t *lru_new(const int capacity);
/* Insert item, identified by key (string), into the given lru.
* The key string is copied for use by the lru.
* Return false if key exists in ht, any parameter is NULL, or error;
* return true iff new item was inserted.
*/
bool lru_insert(lru_t *ht, const char *key, void *item);
/* Return the item associated with the given key;
* return NULL if lru is NULL, key is NULL, key is not found.
*/
void *lru_find(lru_t *ht, const char *key);
/* Print the whole table; provide the output file and func to print each item.
* Ignore if NULL fp. Print (null) if NULL ht.
* Print a table with no items if NULL itemprint.
*/
void lru_print(lru_t *ht, FILE *fp,
void (*itemprint)(FILE *fp, const char *key, void *item));
/* Iterate over all items in the table; in undefined order.
* Call the given function on each item, with (arg, key, item).
* If ht==NULL or itemfunc==NULL, do nothing.
*/
void lru_iterate(lru_t *ht, void *arg,
void (*itemfunc)(void *arg, const char *key, void *item) );
/* Delete the whole lru; ignore NULL ht.
* Provide a function that will delete each item (may be NULL).
*/
void lru_delete(lru_t *ht, void (*itemdelete)(void *item) );
#endif //LRU_H_

