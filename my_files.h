/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#ifndef PROGPRACTICE2_MY_FILES_H
#define PROGPRACTICE2_MY_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_race_basic.h"
#include "my_sortedlist.h"

//read fitxerPeces.txt
//read / write fitxerGPs.txt
// ?? fiterBase.bin
// ?? fitxer Corredors.bin


/***********************************************
 *
 * @Purpose:    Reading the Pat¡rts file and loading the info into a GroupPart structure.
 * @Parameters: (in/out) partGroup = the struct where to load all the parts info.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
 *
************************************************/
GroupPart * readParts (GroupPart * partGroup);

/***********************************************
 *
 * @Purpose:    Reading the GPs file and loading the info into a SortedList.
 * @Parameters: (in/out) season = the sorted list where to load all the GP info.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
 *
************************************************/
int readSeason (SortedList * season);


#endif //PROGPRACTICE2_MY_FILES_H
