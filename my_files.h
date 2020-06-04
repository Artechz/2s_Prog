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
#include "my_circuit_sortedlist.h"
#include "my_driver_sortedlist.h"

#define FILE_NO_ERROR 0
#define FILE_ERROR 1    //TODO implement
#define FILE_EMPTY 2

//read fitxerPeces.txt
//read / write fitxerGPs.txt
// ?? fiterBase.bin
// ?? fitxer Corredors.bin


/***********************************************
 *
 * @Purpose:    Reading the Parts file and loading the info into a GroupPart structure.
 * @Parameters: (in/out): partGroup = the struct where to load all the parts info.
 *              in: fileName = string indicating the location of the file to read.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
************************************************/
int readParts (GroupPart * partGroup, char * fileName);

/***********************************************
 *
 * @Purpose:    Reading the GPs file and loading the info into a SortedListC.
 * @Parameters: (in/out): season = the sorted list where to load all the GP info.
 *              in: fileName = string indicating the location of the file to read.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
 *
************************************************/
int readSeason (SortedListC * season, char * fileName);

/***********************************************
 *
 * @Purpose:    Reading the Pilots file and loading the info into a dynamic array.
 * @Parameters: (in/out): pilots = the dynamic array where to store all the info.
 *              in: fileName = string indicating the location of the file to read.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
 *
************************************************/
int readPilots (Pilot ** pilots, char * fileName, int * pilotQty);

/***********************************************
 *
 * @Purpose:    Reading the Base file and loading the info into an array.
 * @Parameters: (in/out): stats = the array where to store the base info.
 *              in: fileName = string indicating the location of the file to read.
 * @Return:     false (0) if there's no error, true (!0) otherwise.
 *
************************************************/
int readBase (int stats[4], char * fileName);

/***********************************************
 *
 * @Purpose:    Check if we have an error, and which is it.
 * @Parameters: in: filError = Int indicating which error we have
 * @Return:     false (0) if there's no error, true(!0) otherwise.
 *
************************************************/
int fileErrorManage (int fileError);

/***********************************************
 *
 * @Purpose:    Check if there was an error when opening the file or if this one is empty.
 * @Parameters: (in/out): file = file we want to check
 *              in: path = path of the file to open.
 *              in: mode = how to open that file.
 * @Return:     false (0) if no error, true(!0) otherwise.
 *
************************************************/
int checkFile (FILE ** file, char * path, char * mode);

#endif //PROGPRACTICE2_MY_FILES_H
