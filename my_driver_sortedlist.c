/***********************************************
 *
 * @Purpose: Module with all the functions and structures needed to be able to implement a sortedlist for the drivers,
 *           and be capable of storing the information of the drivers in an ordered list.
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 12/05/2020 (DD/MM/YYYY)
 * @Date of last modification: 12/05/2020
 *
***********************************************/

#include "my_driver_sortedlist.h"

SortedLD SortedL_create () {
    SortedLD list;
    // The list's head now is the phantom node.
    list.head = (NodeD*) malloc(sizeof(NodeD));
    if (NULL != list.head) {
        // There is no one after the phantom node, so next is NULL.
        list.head->next = NULL;
        // We set the previous pointer to the phantom node.
        list.previous = list.head;
        // Everything was fine, so we indicate it.
        list.error = LIST_NO_ERROR;
        list.size = 0;
    }
    else {
        // Could not get dynamic memory for the phantom node, so we indicate it.
        list.error = LIST_ERROR_MALLOC;
    }

    return list;
}


void LinkedLISTD_add (SortedLD * list, ElD ElD) {
    NodeD * new_node = (NodeD*) malloc(sizeof(NodeD));

    if (new_node != NULL) {
        //Set the ElD field in the new node.
        new_node->element = ElD;
        //Set the next field in the new node.
        new_node->next = list->previous->next;
        //Link the new node to the list.
        list->previous->next = new_node;
        //Move the previous pointer.
        list->previous = new_node;
        list->size++;
    }
}


void 	SortedL_sortedAddTime (SortedLD * list, ElD element) {
    int found = 0;
    ElD e;

    //POV to head to make sure we check all the positions starting from the beginning.
    SortedL_goToHead(list);

    //Loop will stop when it finds the proper position for the new ElD.
    while (!SortedL_isAtEnd(*list) && !found) {
        e = SortedL_get(list);

        //Skipping the position if number is greater than actual. If not then we've found it.
        if (element.time > e.time) {
            SortedL_next(list);
        }
        else {
            found = 1;
        }
    }

    //Adding the ElD to the list.
    LinkedLISTD_add(list, element);
    //printf(" !! Circuit %s added at position %d. New size: %d", ElD.name, ElD.place-1, list->size);
}

void 	SortedL_sortedAddScore (SortedLD * list, ElD element) {
    int found = 0;
    ElD e;

    //POV to head to make sure we check all the positions starting from the beginning.
    SortedL_goToHead(list);

    //Loop will stop when it finds the proper position for the new ElD.
    while (!SortedL_isAtEnd(*list) && !found) {
        e = SortedL_get(list);

        //Skipping the position if number is greater than actual. If not then we've found it.
        if (element.totalPoints < e.totalPoints) {
            SortedL_next(list);
        }
        else {
            found = 1;
        }
    }

    //Adding the ElD to the list.
    LinkedLISTD_add(list, element);
    //printf(" !! Circuit %s added at position %d. New size: %d", ElD.name, ElD.place-1, list->size);
}

void 	SortedL_remove (SortedLD * list)  {
    NodeD * aux = NULL;

    //Checking the previous pointer doesn't point to the last node.
    if (SortedL_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        //Setting an auxiliary pointer to the ElD we want to remove.
        aux = list->previous->next;

        //Removing POV
        list->previous->next = list->previous->next->next;

        //Removing the ElD.
        free(aux);

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
        list->size--;
    }
}


ElD SortedL_get (SortedLD * list) {
    ElD element;

    // Checking the previous pointer doesn't point to the last node in the list
    if (SortedL_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        //Returning the ElD stored in the POV.
        element = list->previous->next->element;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }

    return element;
}


int 	SortedL_isEmpty (SortedLD list)  {
    //Checking if list is empty by seeing if there's someone after the phantom node.
    return NULL == list.head->next;
}


void 	SortedL_goToHead (SortedLD * list) {
    //Moving POV to first ElD.
    list->previous = list->head;
}


void 	SortedL_next (SortedLD * list) {
    // Checking the previous pointer doesn't point to the last node in the list
    if (SortedL_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // Move the POV to the next ElD.
        list->previous = list->previous->next;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}


int 	SortedL_isAtEnd (SortedLD list) {
    //Checking if at the end by seeing if there's any node after POV.
    return NULL == list.previous->next;
}


void 	SortedL_destroy (SortedLD * list) {
    NodeD * aux;
    // While there are still NODEs in the list.
    while (NULL != list->head) {
        // Take the first node.
        aux = list->head;
        // Now the first node is the next node.
        list->head = list->head->next;
        // Free who was the first node;
        free(aux);
    }
    // Set the pointers to NULL (best practice).
    list->head = NULL;
    list->previous = NULL;
    list->size = 0;
}


int		SortedL_getErrorCode (SortedLD list) {
    return list.error;
}