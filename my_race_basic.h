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
#include <time.h>

#define MAXSTRING 26

#define PARTS_FILE "files/fitxerPeces.txt"      //TODO delete all this bc it has to be arguments
#define SEASON_FILE "files/fitxerGPs.txt"
#define PILOTS_FILE "files/fitxerCorredors.bin"
#define BASE_FILE "files/fitxerBase.bin"

#define BACKGROUND_IMAGE "files/boxes.png"
#define TIRES_IMAGE "files/neumaticos.png"
#define AEROFRONT_IMAGE "files/aero_front.png"
#define AEROMID_IMAGE "files/aero_mid.png"
#define AEROREAR_IMAGE "files/aero_rear.png"
#define FUEL_IMAGE "files/gasolina.png"
#define ENGINE_IMAGE "files/motor.png"
#define CAR_IMAGE "files/cotxe.png"

#define WIN_WIDTH 1100
#define WIN_HEIGHT 600

#define PS_NOTASKED 0
#define PS_ASKED 1
#define PS_ACCEPTED 2
#define PS_NOTACCEPTED 3

#define RACE_INPROGRESS 0
#define RACE_FINISHED 1


typedef struct {
    char name[MAXSTRING];
    int number;
    char teamName[MAXSTRING];
    int speed;
    int acceleration;
    int consumption;
    int reliability;
    int reflexes;
    int physicalCondition;
    int temperament;
    int tireManagement;
} Pilot;

typedef struct {
    char driverName[MAXSTRING];
    char teamName[MAXSTRING];
    int number;
    int reflexes;
    int physicalCondition;
    int temperament;
    int tireManagement;
} Driver;

typedef struct {
    int number;
    float position;
} Car_UI;   //TODO chekc if used

typedef struct {
    int speed;
    int acceleration;
    int consumption;
    int reliability;
    int pstopQty;
    int time;
} Car;

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
    int totalPoints;
    int time;
    char name[MAXSTRING];
} User;


/***********************************************
 *
 * @Purpose:    Asks the user a question, checks the
 *              answers for errors within a valid range
 *              of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return:     Returns the value typed by the user.
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

/*
/***********************************************TODO evaluate if needed
 *
 * @Purpose:    Asks the user a question, checks the
 *              answers for errors within a valid range
 *              of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return:     Returns the value typed by the user.
 *
************************************************/
//void timeWait (float threshold);

/***********************************************TODO
 *
 * @Purpose:
 * @Parameters:
 * @Return:
 *
************************************************/
void calculatePlayer (Car * car, Driver * driver, Circuit temp, int * playerTime);

/***********************************************TODO
 *
 * @Purpose:
 * @Parameters:
 * @Return:
 *
************************************************/
void calculateOthers (Car * others, Pilot * pilot, Circuit temp);

/***********************************************TODO
 *
 * @Purpose:
 * @Parameters:
 * @Return:
 *
************************************************/
void calculatePos (Car * player, Car * others, int pilotQty, int ** carPos, float timeElapsed, float playerElapsed, int playerTime, int pstopCounter, int pstopStatus, float pstopTimeElapsed, int * aux, Circuit temp);


#endif //PROGPRACTICE2_MY_RACE_BASIC_H
