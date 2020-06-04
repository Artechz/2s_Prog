/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_race_basic.h"

int menuAsk (char question[MAXSTRING], int min, int max) {

    char input[MAXSTRING];
    int check, i;

    do {
        check = 1;
        printf("%s", question);
        fgets(input, MAXSTRING, stdin);
        if(input[0] == '\n')
            check = 0;
        input[strlen(input) - 1] = '\0';
        if (strlen(input) > 2) {
            check = 0;
        }
        else {
            for (i = 0; i < strlen(input); i++) {
                if (input[i] < '0' || input[i] > '9') {
                    check = 0;
                }
            }
            if (check) {
                if (atoi(input) > max || atoi(input) < min) {
                    check = 0;
                }
            }
        }
        if (0 == check) {
            printf("Error, the number should be between %d and %d, inclusive.\n", min, max);
        }
    } while (0 == check);

    return atoi(input);
}

void infoAsk (Driver * driver) {

    printf("Driver Name? ");
    fgets(driver->driverName, MAXSTRING, stdin);
    driver->driverName[strlen(driver->driverName) - 1] = '\0';

    printf("Team Name? ");
    fgets(driver->teamName, MAXSTRING, stdin);
    driver->teamName[strlen(driver->teamName) - 1] = '\0';

    driver->number = menuAsk("Drivers Number? ", 0, 99);

    driver->reflexes = menuAsk("Reflexes? ", 0, 10);

    driver->physicalCondition = menuAsk("Physical Condition? ", 0, 10);

    driver->temperament = menuAsk("Temperament? ", 0, 10);

    driver->tireManagement = menuAsk("Tire management? ", 0, 10);
}

/*
void timeWait (float threshold) {
    float timeInitial, timeMeasured, timeDelta = 0;

    timeInitial = (float)clock();
    while (timeDelta < threshold) {
        timeMeasured = (float)clock();
        timeDelta = ((timeMeasured - timeInitial) / (float)CLOCKS_PER_SEC);
    }
    printf("%.2f - %.2f s have passed.", threshold, timeDelta);
}
*/

void calculatePlayer (Car * car, Driver * driver, Circuit temp, int * playerTime) {

    int diff[4];
    float calcTime = temp.baseTime;
    int i;
    //printf("-%.2f-", temp.baseTime);      //TODO remove
    diff[0] = car->speed - temp.speed;
    diff[1] = car->acceleration - temp.acceleration;
    diff[2] = car->consumption - temp.consumption;
    diff[3] = car->reliability - temp.reliability;
    for (i = 0; i < 4; i++) {
        calcTime += abs(diff[i]);
    }

    if (diff[3] < 0) {  //pitStop substracting or adding if - or +
        car->pstopQty = temp.pitstopQty + 1;
    }
    else {
        if (diff[3] > 0) {  //if greater than 0 means car has more than appropiate = not less.
            car->pstopQty = temp.pitstopQty - 1;
        }
        else {
            car->pstopQty = temp.pitstopQty;
        }
    }

    calcTime += (car->pstopQty * temp.pitstopTime);
    calcTime -= ((driver->reflexes + driver->physicalCondition + driver->temperament + driver->tireManagement)/4)/2;

    *playerTime = (int)(calcTime - (car->pstopQty * temp.pitstopTime));
    car->time = (int)calcTime;
    printf("\nmytime: %d - %.2f", car->time, calcTime);       //TODO REMOVE
    //printf("\nOthers: ");                                     //TODO REMOVe
}

void calculateOthers (Car * car, Pilot * pilot, Circuit temp) {

    int diff[4];
    float calcTime = temp.baseTime;
    int i;

    diff[0] = car->speed - temp.speed;
    diff[1] = car->acceleration - temp.acceleration;
    diff[2] = car->consumption - temp.consumption;
    diff[3] = car->reliability - temp.reliability;
    for (i = 0; i < 4; i++) {
        calcTime += abs(diff[i]);
    }
    if (diff[3] < 0) {  //pitStop substracting or adding if - or +
        car->pstopQty = temp.pitstopQty + 1;
    }
    else {
        if (diff[3] > 0) {  //if greater than 0 means car has more than appropiate = not less.
            car->pstopQty = temp.pitstopQty - 1;
        }
        else {
            car->pstopQty = temp.pitstopQty;
        }
    }
    calcTime += (car->pstopQty * temp.pitstopTime);
    calcTime -= ((pilot->reflexes + pilot->physicalCondition + pilot->temperament + pilot->tireManagement) / 4) / 2;

    car->time = (int)calcTime;
    //printf("%d - %d ! ", car->time, calcTime);        //TODO remove
}

void calculatePos (Car * player, Car * others, int pilotQty, int ** carPos, float timeElapsed, float playerElapsed, int playerTime, int pstopStatus, int * aux) {

    const int distance = abs(WIN_WIDTH*3/30 - (WIN_WIDTH*14)/20);
    int i;
    for (i = 0; i < pilotQty; i++) {
        if (others[i].time > timeElapsed) {
            (*carPos)[i] = (int)(((float)distance / (float)others[i].time ) * timeElapsed);
        }
    }

    if (!(PS_NOTACCEPTED == pstopStatus || PS_ACCEPTED == pstopStatus) && 0 == (*aux)) {
        (*carPos)[pilotQty] = (int)((distance / playerTime) * playerElapsed);
        printf("\n %d", (*carPos)[pilotQty]);
        if ((*carPos)[pilotQty] >= distance) {
            (*aux) = 1;
        }
        //printf("\n%d ", distance/(distance/playerTime));
    }
}
