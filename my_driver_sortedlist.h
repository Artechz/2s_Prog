/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 12/05/2020 (DD/MM/YYYY)
 * @Date of last modification: 12/05/2020
 *
***********************************************/

#ifndef PROGPRACTICE2_MY_CIRCUIT_SortedL_H
#define PROGPRACTICE2_MY_CIRCUIT_SortedL_H

// Libraries
#include <stdlib.h>				// To use dynamic memory.
#include "my_race_basic.h"			// Student module to let the ElD be a Student

// Constants to manage the list's error codes.
#define LIST_NO_ERROR 0
#define LIST_ERROR_FULL 1		// Error, the list is full.
#define LIST_ERROR_EMPTY 2		// Error, the list is empty.
#define LIST_ERROR_MALLOC 3		// Error, a malloc failed.
#define LIST_ERROR_END 4		// Error, the POV is at the end.

// Data types

typedef User ElD;

typedef struct _NodeD {
    ElD element;
    struct _NodeD * next;
} NodeD;

typedef struct {
    int error;			// Error code to keep track of failing operations;
    NodeD * head;	 	// Head/First ElD or Phantom node;
    NodeD * previous; 	// Previous node before the point of view;
    int size;
} SortedLD;

// Procedures & Functions
/****************************************************************************
 *
 * @Objective:  Creates an empty sorted list.
 *			    If the list fails to create the phantom node, it will set
 *			    the error code to LIST_ERROR_MALLOC.
 * @Parameters:     ---
 * @Return:     An empty sorted list
 *
 ****************************************************************************/
SortedLD SortedL_create ();

/****************************************************************************
 *
 * @Objective:  Inserts the specified ElD in this list to the position
 *			    defined by the sorting algorithm. Shifts the point of view
 *				ElD (if any) and any subsequent ElDs to the right.
 *			    If the list fails to create the new node to store the ElD,
 *				it will set	the error code to LIST_ERROR_MALLOC.
 *
 * @Parameters:     (in/out) list    = the sorted list where to add the new ElD
 *				    (in)     ElD = the ElD to add to the list
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_sortedAddTime (SortedLD * list, ElD element);

/****************************************************************************
 *
 * @Objective:  Inserts the specified ElD in this list to the position
 *			    defined by the sorting algorithm. Shifts the point of view
 *				ElD (if any) and any subsequent ElDs to the right.
 *			    If the list fails to create the new node to store the ElD,
 *				it will set	the error code to LIST_ERROR_MALLOC.
 *
 * @Parameters:     (in/out) list    = the sorted list where to add the new ElD
 *				    (in)     ElD = the ElD to add to the list
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_sortedAddScore (SortedLD * list, ElD element);

/****************************************************************************
 *
 * @Objective: Removes the ElD currently at the point of view in this
 *				list. Shifts any subsequent ElDs to the left.
 *			   This operation will fail if the POV is after the last valid
 *				ElD of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *			    LIST_ERROR_END.
 * @Parameters:     (in/out) list = the sorted list where to remove the ElD
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_remove (SortedLD * list);

/****************************************************************************
 *
 * @Objective:  Returns the ElD currently at the point of view in this list.
 *			    This operation will fail if the POV is after the last valid
 *				ElD of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
 * @Parameters:     (in/out) list = the sorted list where to get the ElD.
 *								in/out because we need to set the error code.
 * @Return:     ---
 *
 ****************************************************************************/
ElD SortedL_get (SortedLD * list);


/****************************************************************************
 *
 * @Objective:  Returns true (!0) if this list contains no ElDs.
 * @Parameters:     (in)     list = the sorted list to check.
 * @Return:     true (!0) if this list contains no ElDs, false (0) otherwise.
 *
 ****************************************************************************/
int 	SortedL_isEmpty (SortedLD list);


/****************************************************************************
 *
 * @Objective:  Moves the point of view to the first ElD in the list.
 * @Parameters:     (in/out) list = the sorted list to move the POV.
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_goToHead (SortedLD * list);


/****************************************************************************
 *
 * @Objective:  Moves the point of view to the next ElD in the list.
 *				If the POV is after the last ElD in the list (or when
 *				the list is empty), this function will set the list's error
 *				to LIST_ERROR_END.
 * @Parameters:     (in/out) list = the sorted list to move the POV.
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_next (SortedLD * list);


/****************************************************************************
 *
 * @Objective:  Returns true (!0) if the POV is after the last ElD in the
 *				list.
 * @Parameters:     (in)     list = the sorted to check.
 * @Return:     true (!0) if the POV is after the last ElD in the list
 *
 ****************************************************************************/
int 	SortedL_isAtEnd (SortedLD list);


/****************************************************************************
 *
 * @Objective: Removes all the ElDs from the list and frees any dynamic
 *				memory block the list was using. The list must be created
 *				again before usage.
 * @Parameters:     (in/out) list = the sorted list to destroy.
 * @Return:     ---
 *
 ****************************************************************************/
void 	SortedL_destroy (SortedLD * list);


/****************************************************************************
 *
 * @Objective:  This function returns the error code provided by the last
 *				operation run. The operations that update the error code are:
 *				Create, Add, Remove and Get.
 * @Parameters:     (in)     list = the sorted list to check.
 * @Return:     An error code from the list of constants defined.
 *
 ****************************************************************************/
int		SortedL_getErrorCode (SortedLD list);

#endif //PROGPRACTICE2_MY_CIRCUIT_SortedL_H
