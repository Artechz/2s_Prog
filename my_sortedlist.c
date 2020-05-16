/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 12/05/2020 (DD/MM/YYYY)
 * @Date of last modification: 12/05/2020
 *
***********************************************/

#include "my_sortedlist.h"

SortedList SORTEDLIST_create () {
    SortedList list;
    // The list's head now is the phantom node.
    list.head = (Node*) malloc(sizeof(Node));
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


void LINKEDLIST_add (SortedList * list, Element element) {
    Node * new_node = (Node*) malloc(sizeof(Node));

    if (new_node != NULL) {
        //Set the element field in the new node.
        new_node->element = element;
        //Set the next field in the new node.
        new_node->next = list->previous->next;
        //Link the new node to the list.
        list->previous->next = new_node;
        //Move the previous pointer.
        list->previous = new_node;
        list->size++;
    }
}


void 	SORTEDLIST_sortedAdd (SortedList * list, Element element) {
    int found = 0;
    Element e;

    //POV to head to make sure we check all the positions starting from the beginning.
    SORTEDLIST_goToHead(list);

    //Loop will stop when it finds the proper position for the new Element.
    while (!SORTEDLIST_isAtEnd(*list) && !found) {
        e = SORTEDLIST_get(list);

        //Skipping the position if number is greater than actual. If not then we've found it.
        if (element.place > e.place) {
            SORTEDLIST_next(list);
        }
        else {
            found = 1;
        }
    }

    //Adding the element to the list.
    LINKEDLIST_add(list, element);
    //printf(" !! Circuit %s added at position %d. New size: %d", element.name, element.place-1, list->size);
}


void 	SORTEDLIST_remove (SortedList * list)  {
    Node * aux = NULL;

    //Checking the previous pointer doesn't point to the last node.
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        //Setting an auxiliary pointer to the element we want to remove.
        aux = list->previous->next;

        //Removing POV
        list->previous->next = list->previous->next->next;

        //Removing the element.
        free(aux);

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
        list->size--;
    }
}


Element SORTEDLIST_get (SortedList * list) {
    Element element;

    // Checking the previous pointer doesn't point to the last node in the list
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        //Returning the element stored in the POV.
        element = list->previous->next->element;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }

    return element;
}


int 	SORTEDLIST_isEmpty (SortedList list)  {
    //Checking if list is empty by seeing if there's someone after the phantom node.
    return NULL == list.head->next;
}


void 	SORTEDLIST_goToHead (SortedList * list) {
    //Moving POV to first element.
    list->previous = list->head;
}


void 	SORTEDLIST_next (SortedList * list) {
    // Checking the previous pointer doesn't point to the last node in the list
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // Move the POV to the next element.
        list->previous = list->previous->next;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}


int 	SORTEDLIST_isAtEnd (SortedList list) {
    //Checking if at the end by seeing if there's any node after POV.
    return NULL == list.previous->next;
}


void 	SORTEDLIST_destroy (SortedList * list) {
    Node * aux;
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


int		SORTEDLIST_getErrorCode (SortedList list) {
    return list.error;
}