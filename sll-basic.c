#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node {
    int data;
    struct sll_node *next;
} sll_node;

typedef sll_node* ptr_sll_node;

ptr_sll_node
insertNodeAtHead (ptr_sll_node* ptr_head, 
                  int val_to_be_stored) 
{

    ptr_sll_node new_node = (ptr_sll_node)malloc(sizeof(sll_node));
    if (!new_node)
        return NULL;

    // Store val in node
    new_node->data = val_to_be_stored;

    // Re-asssign head
    new_node->next = *ptr_head;
    *ptr_head = new_node;

    return new_node;

}

ptr_sll_node
insertNodeAtEnd (ptr_sll_node* ptr_head,
                 int val_to_be_stored)
{

    ptr_sll_node new_node = (ptr_sll_node)malloc(sizeof(ptr_sll_node));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    ptr_sll_node temp = *ptr_head;
    
    new_node->next = NULL;
    new_node->data = val_to_be_stored;

    // Null check for head
    if (temp == NULL) {
        *ptr_head = new_node;
        return new_node;
    }

    // Head is NOT NULL
    while(temp->next != NULL) {
        temp = temp->next;
    }
    // temp points to last node
    temp->next = new_node;

    return new_node;
}

int
deleteElementInSLL (ptr_sll_node* ptr_head,
                    int search_val)
{

    ptr_sll_node temp = *ptr_head, curr_node, prev_node, next_node;
   
    if (!temp)
        return -1;
    if (temp->data == search_val) {
        *ptr_head = temp->next;
        free(temp);
        return 0;
    }
    curr_node = temp->next;
    prev_node = temp;
    next_node = temp->next->next;
    while (next_node != NULL) {
        if (curr_node->data == search_val) {
            prev_node->next = next_node;
            free(curr_node); 
            return 0;
        }
        prev_node = curr_node;
        curr_node = next_node;
        next_node = next_node->next;
    }
    return -1;

}

int
deleteAllElementInSLL (ptr_sll_node* ptr_head,
                       int search_val)
{

    ptr_sll_node temp = *ptr_head, curr_node, prev_node, next_node;

    if (!temp)
        return -1;
    if (temp->data == search_val) {
        *ptr_head = temp->next;
        free(temp);
        temp = temp->next;
    }
    curr_node = temp->next;
    prev_node = temp;
    next_node = temp->next->next;
    while (next_node != NULL) {
        if (curr_node->data == search_val) {
            prev_node->next = next_node;
            free(curr_node);
            curr_node = NULL;
        } 
        prev_node = curr_node;
        curr_node = next_node;
        next_node = next_node->next;
    }
    return -1;

}

int
detectLoop (const ptr_sll_node head)
{
    /* Floyd’s Cycle detection algorithm */
    ptr_sll_node slow_ptr = head;
    ptr_sll_node fast_ptr = head;

    while (slow_ptr && fast_ptr && fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        if (slow_ptr == fast_ptr)
            return 0;
    }

    return 1;
}

void
printList (ptr_sll_node head) 
{

    ptr_sll_node slow_ptr = head, temp, last_node_with_val_printed;
    ptr_sll_node fast_ptr = head;
    int count = 0, iterations = 0;

    // If loop is detected, then print need to be terminated accordingly
    // Hence, print is done with loop detection algo

    /* Floyd’s Cycle detection algorithm */
    while (slow_ptr && fast_ptr && fast_ptr->next) {
        iterations++;
        printf("Element at node (%d) : %d\n",
               count++,slow_ptr->data);
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
        if (slow_ptr == fast_ptr) {
            printf("Loop detected\n");
            last_node_with_val_printed = slow_ptr;
            // Proceed to identify intersection point
            slow_ptr = head;
            while(slow_ptr != fast_ptr) {
                iterations++;
                slow_ptr = slow_ptr->next;
                fast_ptr = fast_ptr->next;
            }

            // Reached intersection point
            // Now print the data from last node printed till intersection point
            printf("Val at intersection point : %d\n", slow_ptr->data);

            // This is corner case when intersection point coincides with 
            // loop detection point
            if(last_node_with_val_printed == slow_ptr) {
                iterations++;
                printf("Element at node (%d) : %d\n",
                       count++,last_node_with_val_printed->data);
                last_node_with_val_printed = last_node_with_val_printed->next;
            }

            while(last_node_with_val_printed != slow_ptr) {
                iterations++;
                printf("Element at node (%d) : %d\n",
                       count++,last_node_with_val_printed->data);
                last_node_with_val_printed = last_node_with_val_printed->next;
            }
            printf ("Completed print of sll in (%d) iterations\n",iterations);
            return;
        }
    }

    // No loopfound, hence proceed from the point where
    // earlier loop left and print remaining elements
    while(slow_ptr) {
        iterations++;
        printf("Element at node (%d) : %d\n",
               count++,slow_ptr->data);
        slow_ptr = slow_ptr->next;
    }

    printf ("Completed print of sll in (%d) iterations\n",iterations);
    return;
}

#define EOK 0

int
main() {

   ptr_sll_node head = NULL;
   int loop_count;
   int rc = EOK;

   #define SIZE_OF_ARRAY 15
   int arr[SIZE_OF_ARRAY] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   ptr_sll_node temp_node[SIZE_OF_ARRAY];
   for (loop_count=0;loop_count < SIZE_OF_ARRAY;loop_count++) {
       temp_node[loop_count] = insertNodeAtEnd(&head,arr[loop_count]);
       if (!temp_node[loop_count]) {
           printf("Insertion of node failed for loop_count : %d\n",loop_count);
           // since this is main, so need to worry for freeing up the malloced mem
           return 1;
       }
   }

   // Print SLL
   printf("Original List\n");
   printList(head);

   // Create a loop
   temp_node[14]->next = temp_node[6];

   // Print SLL
   printf("List after loop is inserted\n");
   printList(head);

   // Delete node
   //deleteAllElementInSLL(&head,2);
   //printList(head);

   return 0;

}
