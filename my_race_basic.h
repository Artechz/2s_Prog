/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#ifndef PROGPRACTICE2_MY_RACE_BASIC_H
#define PROGPRACTICE2_MY_RACE_BASIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRING 26

typedef struct {
    char driverName[MAXSTRING];
    char teamName[MAXSTRING];
    int driverNumber;
    int reflexes;
    int physicalCondition;
    int temperament;
    int tireManagement;
} Driver;

typedef struct {
    char name[MAXSTRING];
    int speed;
    int acceleration;
    int consumption;
    int reliability;
} MiniPart;

typedef struct {
    char name[MAXSTRING];
    int numParts;
    MiniPart * type;
} Part;

typedef struct {
    int numParts;
    Part * parts;
} GroupPart;

/***********************************************
 *
 * @Purpose: Asks the user a question, checks the answers for errors within a valid
 *           range of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return: Returns the atoi of the input if answer is valid.
 *
************************************************/
int menuAsk (char question[MAXSTRING], int min, int max);

#endif //PROGPRACTICE2_MY_RACE_BASIC_H
