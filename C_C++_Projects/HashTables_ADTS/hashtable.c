#include "hashtable.h"
#include "set.h"
#include <stdlib.h>
#include <string.h>
typedef struct hashnode {
    char *key;
    void *item;
    struct hashnode *next;
} hashnode_t;

typedef struct hashtable {
    hashnode_t **buckets; // Array of pointers to hash nodes
    int num_buckets;      // Number of buckets in the hashtable
} hashtable_t;

// hash function for string keys
static int hash(const char *key, int num_buckets) {
    unsigned int hash = 0;
    while (*key) {
        hash = hash * 37 + *key++;
    }
    return hash % num_buckets;
}

// Create a new hashtable
hashtable_t *hashtable_new(const int num_buckets) {
    if (num_buckets <= 0) return NULL;

    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (!ht) return NULL;

    ht->buckets = calloc(num_buckets, sizeof(hashnode_t*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    ht->num_buckets = num_buckets;
    return ht;
}



bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (!ht || !key || !item) return false;

    int index = hash(key, ht->num_buckets);
    for (hashnode_t *node = ht->buckets[index]; node; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            printf("Duplicate key found: %s\n", key);
            return false; // Key already exists
        }
    }

    hashnode_t *new_node = malloc(sizeof(hashnode_t));
    if (!new_node) return false;

    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return false;
    }
    new_node->item = item;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;

    printf("Inserting new key: %s\n", key);
    return true;
}



// Find an item by its key in the hashtable
void *hashtable_find(hashtable_t *ht, const char *key) {
    if (!ht || !key) return NULL;

    int index = hash(key, ht->num_buckets);
    for (hashnode_t *node = ht->buckets[index]; node; node = node->next) {
        if (strcmp(node->key, key) == 0) return node->item;
    }

    return NULL;
}






// Print the whole hashtable
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *, const char *, void *)) {
    if (!ht || !fp) return;

    for (int i = 0; i < ht->num_buckets; i++) {
        for (hashnode_t *node = ht->buckets[i]; node; node = node->next) {
            if (itemprint) itemprint(fp, node->key, node->item);
        }
    }
}

// Iterate over all items in the hashtable
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *, const char *, void *)) {
    if (!ht || !itemfunc) return;

    for (int i = 0; i < ht->num_buckets; i++) {
        for (hashnode_t *node = ht->buckets[i]; node; node = node->next) {
            itemfunc(arg, node->key, node->item);
        }
    }
}
// Delete the whole hashtable
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *)) {
    if (!ht) return;

    for (int i = 0; i < ht->num_buckets; i++) {
        hashnode_t *node = ht->buckets[i];
        while (node) {
            hashnode_t *next = node->next;
            if (itemdelete) itemdelete(node->item);
            free(node->key);
            free(node);
            node = next;
        }
    }

    free(ht->buckets);
    free(ht);
}



bool hashtable_remove(hashtable_t *ht, const char *key) {
    if (!ht || !key) return false;

    int index = hash(key, ht->num_buckets);
    hashnode_t *node = ht->buckets[index], *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) prev->next = node->next;
            else ht->buckets[index] = node->next;

            free(node->key);
            free(node);
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false; // Key not found
}

