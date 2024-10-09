#include <stddef.h>
#include "ll_cycle.h"
#include <stdio.h> // Include standard I/O for debugging purposes

int ll_has_cycle(node *head) {
    // Check if list is empty or has one node
    if (head == NULL || head->next == NULL) {
        return 0; // No cycle in an empty or single-node list
    }

    // Initialize two pointers at the head of the list
    node *slow_ptr = head;
    node *fast_ptr = head;

    // Loop continues if fast_ptr and the node after fast_ptr are not NULL
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        slow_ptr = slow_ptr->next;     
   	// Move slow_ptr by 1 node
        fast_ptr = fast_ptr->next->next;  
      	// Move fast_ptr by 2 nodes

        //  to see the progress of pointers
        // printf("Slow Pointer at: %p, Fast Pointer at: %p\n", (void*)slow_ptr, (void*)fast_ptr);

        if (slow_ptr == fast_ptr) {
            // If conditional for a cycle verification
            return 1;
        }
    }

    // If fast_ptr reaches the end then  there is no cycle
    return 0;
}

