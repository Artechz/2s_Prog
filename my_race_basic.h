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

#define TRUE 1
#define FALSE 0

#define LSRACER_LOG 1

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
    int completed;
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

/***********************************************
 *
 * @Purpose:    Asks the user for the information about the pilot.
 * @Parameters:     in: driver = place where the information introduced
 *                  by the user is stored.
 * @Return:     ---
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

/***********************************************
 *
 * @Purpose:    Calculate the statistics of the player
 * @Parameters: (in/out): car = information about the car.
 *              (in/out): driver = information about the driver
 *              in: temp = information about the gp.
 *              out: playerTime = time the player spends to end the race.
 * @Return:     ---
 *
************************************************/
void calculatePlayer (Car * car, Driver * driver, Circuit temp, int * playerTime);

/***********************************************
 *
 * @Purpose:    Calculate the statistics of the other drivers.
 * @Parameters: (in/out): others = information about the car of the other drivers
 *              (in/out): pilot = information about the other drivers
 *              in: temp = information about the gp.
 * @Return:     ---
 *
************************************************/
void calculateOthers (Car * others, Pilot * pilot, Circuit temp);

/***********************************************
 *
 * @Purpose:    Calculate the position of the cars.
 * @Parameters: (in/out): player = information about the players car.
 *              (in/out): others = information about the car of the other drivers.
 *              in: pilotQty = number of pilots
 *              (in/out): carPos = position of the car.
 *              in: timeElapsed = number of seconds that have passed since the race has started.
 *              in: playerElapsed = time the player has been moving (excludes pit stops time).
 *              in: playerTime = time the player needs to finish.
 *              in: pstopCounter = number of pit stops done by player.
 *              in: pstopNeeded = number of pit stops required by the circuit.
 *              in: pstopStatus = indicates if player is doing a pit stop or not.
 *              (in/out): aux = auxiliary value related to player relative position to the screen margins.
 *              in: temp = information about the gp.
 * @Return:     ---
 *
************************************************/
void calculatePos (Car * player, Car * others, int pilotQty, int ** carPos, float timeElapsed, float playerElapsed, int playerTime, int pstopStatus, int * aux);


#endif //PROGPRACTICE2_MY_RACE_BASIC_H
