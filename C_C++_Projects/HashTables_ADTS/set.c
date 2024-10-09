#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct setitem {
    char *key;
    void *item;
    bool is_occupied;
} setitem_t;

typedef struct set {
    setitem_t *items;
    int capacity;
    int size;
} set_t;

// Helper function to calculate the hash
static int hash(const char *key, int capacity) {
    unsigned long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % capacity;
}

// Helper function to resize and rehash the set
static bool resize_set(set_t *set, int new_capacity) {
    setitem_t *new_items = calloc(new_capacity, sizeof(setitem_t));
    if (!new_items) return false;

    for (int i = 0; i < set->capacity; i++) {
        if (set->items[i].is_occupied) {
            int index = hash(set->items[i].key, new_capacity);
            new_items[index] = set->items[i]; // Shallow copy
        }
    }

    free(set->items);
    set->items = new_items;
    set->capacity = new_capacity;
    return true;
}

// Create a new set
set_t* set_new(void) {
    set_t *set = malloc(sizeof(set_t));
    if (!set) return NULL;

    set->items = calloc(INITIAL_SIZE, sizeof(setitem_t));
    if (!set->items) {
        free(set);
        return NULL;
    }

    set->capacity = INITIAL_SIZE;
    set->size = 0;
    return set;
}

// Insert an item into the set
bool set_insert(set_t *set, const char *key, void *item) {
    if (!set || !key || !item) return false;

    if ((float)set->size / set->capacity >= LOAD_FACTOR) {
        if (!resize_set(set, set->capacity * 2)) return false;
    }

    int index = hash(key, set->capacity);
    while (set->items[index].is_occupied) {
        if (strcmp(set->items[index].key, key) == 0) return false; // Duplicate key
        index = (index + 1) % set->capacity; // Linear probing
    }

    set->items[index].key = strdup(key);
    set->items[index].item = item;
    set->items[index].is_occupied = true;
    set->size++;
    return true;
}

// Find an item by its key in the set
void *set_find(set_t *set, const char *key) {
    if (!set || !key) return NULL;

    int index = hash(key, set->capacity);
    while (set->items[index].is_occupied) {
        if (strcmp(set->items[index].key, key) == 0) {
            return set->items[index].item; // Key found
        }
        index = (index + 1) % set->capacity; // Linear probing
    }
    return NULL; // Key not found
}

// Print the whole set
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (!set || !fp) return;

    for (int i = 0; i < set->capacity; i++) {
        if (set->items[i].is_occupied) {
            if (itemprint) {
                itemprint(fp, set->items[i].key, set->items[i].item);
            }
        }
    }
}

// Iterate over all items in the set
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (!set || !itemfunc) return;

    for (int i = 0; i < set->capacity; i++) {
        if (set->items[i].is_occupied) {
            itemfunc(arg, set->items[i].key, set->items[i].item);
        }
    }
}

// Delete the whole set
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (!set) return;

    for (int i = 0; i < set->capacity; i++) {
        if (set->items[i].is_occupied) {
            if (itemdelete) {
                itemdelete(set->items[i].item);
            }
            free(set->items[i].key);
        }
    }
    free(set->items);
    free(set);
}


