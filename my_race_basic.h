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

#define PARTS_FILE "files/fitxerPeces.txt"
#define SEASON_FILE "files/fitxerGPs.txt"

#define BACKGROUND_IMAGE "files/boxes.png"
#define TIRES_IMAGE "files/neumaticos.png"
#define AEROFRONT_IMAGE "files/aero_front.png"
#define AEROMID_IMAGE "files/aero_mid.png"
#define AEROREAR_IMAGE "files/aero_rear.png"
#define FUEL_IMAGE "files/gasolina.png"
#define ENGINE_IMAGE "files/motor.png"


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
    int selected;
    MiniPart * type;
} Part;

typedef struct {
    int numParts;
    Part * parts;
} GroupPart;

typedef struct {
    int place;
    char name[MAXSTRING];
    int speed;
    int acceleration;
    int consumption;
    int reliability;
    float baseTime;
    int pitstopTime;
    int pitstopQty;
    int completed;  //TODO probs sobra
} Circuit;

typedef struct {
    int numGPs;
    Circuit * circuits;
} Season;


/***********************************************TODO
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

/***********************************************TODO
 *
 * @Purpose:
 * @Parameters:
 * @Return:
 *
************************************************/
void infoAsk (Driver * driver);


#endif //PROGPRACTICE2_MY_RACE_BASIC_H
