

#include "lru.h"
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <stdbool.h>
// function to create a new LRU node
static lru_node_t *lru_node_new(const char *key, void *item) {
    lru_node_t *node = malloc(sizeof(lru_node_t));
    if (node == NULL) {
        return NULL;
    }
    node->key = strdup(key);
    node->item = item;
    node->next = node->prev = NULL;
    return node;
}

// Function to create a new LRU cache
lru_t *lru_new(const int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    lru_t *lru = malloc(sizeof(lru_t));
    if (lru == NULL) {
        return NULL;
    }

    lru->head = lru->tail = NULL;
  
    lru->capacity = capacity;
    lru->size = 0;
    // Initialize other members if needed
// Initialize the hashtable with a suitable size
    // Assuming you have a hashtable_new function
    lru->hashtable = hashtable_new(capacity * 2); //  adjust based on requirements
    if (lru->hashtable == NULL) {
        free(lru);
        return NULL;
    }
    return lru;
}
// Move the node to the end of the list most recently used
static void lru_touch(lru_t *lru, lru_node_t *node) {
    if (node == lru->tail) {
        return; // Already the most recently used
    }

    // Remove node from its current position
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (lru->head == node) {
        lru->head = node->next;
    }

 // Add the node to the tail
    node->prev = lru->tail;
    node->next = NULL;
    if (lru->tail) {
        lru->tail->next = node;
    }
    lru->tail = node;

    // If the list was empty, set the head
    if (!lru->head) {
        lru->head = node;
    }
}
        

bool lru_insert(lru_t *lru, const char *key, void *item) {
    if (!lru || !key || !item) return false;

    if (hashtable_find(lru->hashtable, key) != NULL) {
        return false; // Key already exists
    }

    lru_node_t *new_node = lru_node_new(key, item);
    if (!new_node) return false;

    if (lru->size >= lru->capacity) {
        lru_node_t *old_head = lru->head;
        if (old_head) {
            lru->head = old_head->next;
            if (lru->head) lru->head->prev = NULL;

            hashtable_remove(lru->hashtable, old_head->key);
            free(old_head->key);
            free(old_head);
            lru->size--;
        }
    }

    new_node->next = NULL;
    new_node->prev = lru->tail;
    if (lru->tail) lru->tail->next = new_node;
    lru->tail = new_node;
    if (!lru->head) lru->head = new_node;

    hashtable_insert(lru->hashtable, key, new_node);
    lru->size++;
    return true;
}


// Find an item in the LRU cache
void *lru_find(lru_t *lru, const char *key) {
    if (!lru || !key) return NULL;

    lru_node_t *node = hashtable_find(lru->hashtable, key);
    if (node) {
        // Move the node to the tail (most recently used)
        lru_touch(lru, node);
        return node->item;
    }

    return NULL; // Item not found
}


void lru_print(lru_t *lru, FILE *fp, void (*itemprint)(FILE *, const char *, void *)) {
    if (!lru || !fp || !itemprint) return;

    for (lru_node_t *node = lru->head; node != NULL; node = node->next) {
        itemprint(fp, node->key, node->item);
    }
}

void lru_iterate(lru_t *lru, void *arg, void (*itemfunc)(void *, const char *, void *)) {
    if (!lru || !itemfunc) return;

    for (lru_node_t *node = lru->head; node != NULL; node = node->next) {
        itemfunc(arg, node->key, node->item);
    }
}



void lru_delete(lru_t *lru, void (*itemdelete)(void *)) {
    if (!lru) return;

    lru_node_t *current = lru->head;
    while (current != NULL) {
        lru_node_t *temp = current;
        current = current->next;

        // Call itemdelete for the item if provided
        if (itemdelete) {
            itemdelete(temp->item);
        }

        free(temp->key);
        free(temp);
    }

    // Delete the hashtable, passing NULL for itemdelete because items are already freed
    if (lru->hashtable) {
        hashtable_delete(lru->hashtable, NULL);
    }

    free(lru);
}


