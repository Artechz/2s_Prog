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

//read fitxerPeces.txt
//read / write fitxerGPs.txt
// ?? fiterBase.bin
// ?? fitxer Corredors.bin


/*********************************************** TODO
 *
 * @Purpose: Asks the user a question, checks the answers for errors within a valid
 *           range of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return: Returns the atoi of the input if answer is valid.
 *
************************************************/
GroupPart * readParts (GroupPart * partGroup);


#endif //PROGPRACTICE2_MY_FILES_H
