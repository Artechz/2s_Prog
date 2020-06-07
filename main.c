/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 18/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/


#include <stdio.h>
#include <stdlib.h>
#include "LS_allegro.h"
#include "my_race_basic.h"
#include "my_allegro_ui.h"
#include "my_files.h"

#define TL_NOT_SHOWN 0
#define TL_SHOWING 1
#define TL_ALREADY_SHOWN 2

#define NEEDED_ARGS 5

//#undef LSRACER_LOG

int main (int argc, char * argv[]) {

    int  exit = 0, allegroExit = 0, optionDone = 0, optionSelected = 0, darkMode = WHITE, i, completed;
    int partCategory = 0, partModel = 0, traffLightStatus, isTLOn[5], pstopStatus, pilotQty, pstopCounter, raceStatus, playerTime, pstopPenaltyCounter;
    float timeInitial, timeMeasured, timeDelta, timeElapsed, pstopDeltaTime, playerElapsed;

    //PilotContainer * pilots;
    Pilot * pilots;
    Driver * driver;
    Car * playerCar;
    Car * otherCars;
    GroupPart * partGroup;
    SortedListC * season;
    SortedLD classification = SortedL_create();
    int * carPos;
    int * aux;
    int  baseStats[4]; //From Base.bin file: Speed, Acceleration, Consumption, and Reliability. Respectively

    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * partImages[6];
    ALLEGRO_BITMAP * carImage = NULL;

    pilots = (Pilot * ) malloc(sizeof(Pilot));  //will realloc when reading file
    driver = (Driver *) malloc(sizeof(Driver));
    playerCar = (Car *) malloc(sizeof(Car));
    partGroup = (GroupPart *) malloc(sizeof(GroupPart));
    season = (SortedListC *) malloc(sizeof(SortedListC));
    //Creating the List so we're able to put thing inside it.
    *season = SORTEDLIST_create();
    aux = (int *) malloc(sizeof(int));
    *aux = 0;

    if (NEEDED_ARGS == argc) {
        //Reading the Racers file and putting all info into pilots while managing a possible error.
        if (!fileErrorManage(readPilots(&pilots, argv[3], &pilotQty))) {
            otherCars = (Car *) malloc(sizeof(Car) * pilotQty); //TODO check if using
            carPos = (int *) malloc(sizeof(int) * (pilotQty+1));
            User users[pilotQty+1];
            //Reading the Parts file and putting all parts info into partGroup while managing a possible error.
            if (!fileErrorManage(readParts(partGroup, argv[1]))) {
                //Reading the GPs file and putting all GPs info into season while managing a possible error.
                if(!fileErrorManage(readSeason(season, argv[2]))) {
                    SORTEDLIST_goToHead(season);
                    SortedLD standings[season->size];
                    for (i = 0; i < season->size; i++) {
                        standings[i] = SortedL_create();
                    }
                    //Reading the Base file and putting all info into baseStats while managing a possible error.
                    if(!fileErrorManage(readBase(baseStats, argv[4]))) {
                        //Adding Base stats to all pilots (player is done below when setting up car in option 1).
                        for (i = 0; i < pilotQty; i++) {
                            otherCars[i].speed = baseStats[0];
                            otherCars[i].acceleration = baseStats[1];
                            otherCars[i].consumption = baseStats[2];
                            otherCars[i].reliability = baseStats[3];
                        }
                        //All good, we continue to the menu - major loop.
                        do {

                            printf("\n\nWelcome to LS Racing\n\n");
                            printf("\t 1. Configure Car\n");
                            printf("\t 2. Race\n");
                            printf("\t 3. See Standings\n");
                            printf("\t 4. Save Season\n");
                            printf("\t 5. Exit\n\n");

                            optionSelected = menuAsk("Which option do you want to execute? ", 1, 5);  //TODO change max from 5 to 4
                            switch (optionSelected) {

                                //region OPTION 1
                                case 1:

                                    if (!optionDone) {
                                        infoAsk(driver);
                                        optionDone = 1;
                                    }

                                    printf("\nLoading Configurator ...");
                                    //Starting Allegro, its modules and the graphic window.
                                    LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_CONFIGURATOR);

                                    //Loading the images as a bitmap, checking they loaded properly.
                                    if (!(background= al_load_bitmap(BACKGROUND_IMAGE))) printf("Failed to load background bitmap.\n");
                                    if (!(partImages[0] = al_load_bitmap(TIRES_IMAGE))) printf("Failed to load tires bitmap.\n");
                                    if (!(partImages[1] = al_load_bitmap(AEROFRONT_IMAGE))) printf("Failed to load aero front bitmap.\n");
                                    if (!(partImages[2] = al_load_bitmap(AEROMID_IMAGE))) printf("Failed to load aero mid bitmap.\n");
                                    if (!(partImages[3] = al_load_bitmap(AEROREAR_IMAGE))) printf("Failed to load aero rear bitmap.\n");
                                    if (!(partImages[4] = al_load_bitmap(FUEL_IMAGE))) printf("Failed to load fuel bitmap.\n");
                                    if (!(partImages[5] = al_load_bitmap(ENGINE_IMAGE))) printf("Failed to load engine bitmap.\n");

                                    //Infinite loop until ESC is pressed.
                                    allegroExit = 0;
                                    while (!allegroExit) {
                                        //Checking if ESC or any arrow is being pressed.
                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                                            allegroExit = 1;
                                        }
                                        else {
                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_H)) {
                                                switchDarkMode(&darkMode);
                                            }
                                            else {
                                                if (LS_allegro_key_pressed(ALLEGRO_KEY_LEFT)) {
                                                    //going left
                                                    if (partModel != 0) {
                                                        partModel--;
                                                    }
                                                    else {
                                                        partModel = partGroup->parts[partCategory].numParts - 1;
                                                    }

                                                    partGroup->parts[partCategory].selected = partModel;
                                                }
                                                else {
                                                    if (LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)) {
                                                        //going right
                                                        if (partModel != partGroup->parts[partCategory].numParts - 1) {
                                                            partModel++;
                                                        }
                                                        else {
                                                            partModel = 0;
                                                        }

                                                        partGroup->parts[partCategory].selected = partModel;
                                                    }
                                                    else {
                                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_DOWN)) {
                                                            //going down
                                                            if (partCategory != partGroup->numParts - 1) {
                                                                partCategory++;
                                                            }
                                                            else {
                                                                partCategory = 0;
                                                            }
                                                        }
                                                        else {
                                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_UP)) {
                                                                //going up
                                                                if (partCategory != 0) {
                                                                    partCategory--;
                                                                }
                                                                else {
                                                                    partCategory = partGroup->numParts - 1;
                                                                }
                                                            }
                                                        }
                                                        partModel = partGroup->parts[partCategory].selected;
                                                    }
                                                }
                                            }
                                        }

                                        //Printing all the configuration screen elements.
                                        printConfig(background, darkMode, partImages, partCategory, partModel, partGroup);
                                        //'Painting' the graphic screen.
                                        LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
                                    }

                                    //Closing the graphic window
                                    LS_allegro_exit();

                                    playerCar->speed = baseStats[0];
                                    playerCar->reliability = baseStats[3];
                                    playerCar->consumption = baseStats[2];
                                    playerCar->acceleration = baseStats[1];
                                    for (i = 0; i < partGroup->numParts; i++) { //Adding all the selected parts stats to the player's playerCar stats.
                                        playerCar->speed += partGroup->parts[i].type[partGroup->parts[i].selected].speed;
                                        playerCar->reliability += partGroup->parts[i].type[partGroup->parts[i].selected].reliability;
                                        playerCar->consumption += partGroup->parts[i].type[partGroup->parts[i].selected].consumption;
                                        playerCar->acceleration += partGroup->parts[i].type[partGroup->parts[i].selected].acceleration;
                                    }
                                    //printf("\n%d - %d - %d - %d", playerCar->speed, playerCar->acceleration, playerCar->consumption, playerCar->reliability);     //TODO remove
                                    break;
                                //endregion

                                //region OPTION 2
                                case 2:

                                    if (!optionDone) {
                                        printf("\nERROR: Car needs to be configured before racing.");
                                    }
                                    else {
                                        raceStatus = RACE_INPROGRESS;
                                        traffLightStatus = TL_NOT_SHOWN;
                                        pstopStatus = PS_NOTASKED;
                                        pstopCounter = 0;
                                        pstopPenaltyCounter = 0;
                                        pstopDeltaTime = 0;
                                        playerElapsed = 0;
                                        *aux = 0;

                                        for (i = 0; i < season->size; i++) {
                                            if (!(SORTEDLIST_get(season).completed))
                                                break;
                                            SORTEDLIST_next(season);
                                        }

                                        printf("\nList pos Op 2: %d", SORTEDLIST_get(season).place);

                                        Circuit tempGP = SORTEDLIST_get(season);
                                        carImage = al_load_bitmap(CAR_IMAGE);
                                        if (!carImage) printf("Failed to load playerCar bitmap.\n");

                                        calculatePlayer(playerCar, driver, tempGP, &playerTime);
                                        carPos[pilotQty] = 0;
                                        for (i = 0; i < pilotQty; i++) {
                                            calculateOthers(&otherCars[i], &(pilots[i]), tempGP);
                                            carPos[i] = 0;
                                        }

                                        printf("\nLoading Race ...");
                                        //Starting Allegro, its modules and the graphic window.
                                        LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_RACE);

                                        allegroExit = 0;
                                        for (i = 0; i < 5; i++) {isTLOn[i] = 0;}
                                        timeInitial = (float)clock();
                                        timeElapsed = 0;
                                        //Infinite loop until ESC is pressed.
                                        while (!allegroExit) {
                                            timeMeasured = (float)clock();
                                            timeDelta = ((timeMeasured - timeInitial) / (float)CLOCKS_PER_SEC);

                                            //Checking if ESC or any arrow is being pressed.
                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                                                allegroExit = 1;
                                            }
                                            else {
                                                if (LS_allegro_key_pressed(ALLEGRO_KEY_H)) {
                                                    switchDarkMode(&darkMode);
                                                }
                                                else {
                                                    if (RACE_FINISHED == raceStatus) {
                                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_ENTER)) {
                                                            allegroExit = 1;
                                                        }
                                                    }
                                                }
                                            }

                                            if (TL_NOT_SHOWN == traffLightStatus) { //gp info screen
                                                if (LS_allegro_key_pressed(ALLEGRO_KEY_R)) {
                                                    printf("\nR key pressed.");
                                                    traffLightStatus = TL_SHOWING;
                                                }
                                                //Printing race - circuit info.
                                                printGP(darkMode, SORTEDLIST_get(season));
                                                timeInitial = (float)clock();
                                            }
                                            else {
                                                if (TL_SHOWING == traffLightStatus) {   //traffic lights screen
                                                    //Printing traffic lights screen.
                                                    printTrafficLights(darkMode, isTLOn);

                                                    if (FALSE == isTLOn[0]) {
                                                        if (timeDelta >= 1.0) {
                                                            isTLOn[0] = TRUE;
                                                            isTLOn[1] = TRUE;
                                                            timeInitial = (float)clock();
                                                        }
                                                    }
                                                    else {
                                                        if (FALSE == isTLOn[2]) {
                                                            if (timeDelta >= 1.0) {
                                                                isTLOn[2] = TRUE;
                                                                timeInitial = (float)clock();
                                                            }
                                                        }
                                                        else {
                                                            if (FALSE == isTLOn[3]) {
                                                                if (timeDelta >= 1.0) {
                                                                    isTLOn[3] = TRUE;
                                                                    timeInitial = (float)clock();
                                                                }
                                                            }
                                                            else {
                                                                if (FALSE == isTLOn[4]) {
                                                                    if (timeDelta >= 1.0) {
                                                                        isTLOn[4] = TRUE;
                                                                        timeInitial = (float)clock();
                                                                    }
                                                                }
                                                                else {
                                                                    if (timeDelta >= 0.5) {
                                                                        traffLightStatus = TL_ALREADY_SHOWN;
                                                                        timeElapsed = 0;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                else {
                                                    if (TL_ALREADY_SHOWN == traffLightStatus) { //race screen
                                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_R) && PS_NOTASKED == pstopStatus) {
                                                            pstopStatus = PS_ASKED;
#ifdef LSRACER_LOG
                                                            printf("\nRadioed in. ");                                   //LOG
                                                            printf("Code: %d", *aux);                                   //LOG
#endif
                                                        }
                                                        else {
                                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_P)) {
                                                                if (pstopCounter < tempGP.pitstopQty) {
#ifdef LSRACER_LOG
                                                                    printf("\nPitStop requested.");                     //LOG
#endif
                                                                    if (PS_ASKED == pstopStatus) {
                                                                        pstopStatus = PS_ACCEPTED;
#ifdef LSRACER_LOG
                                                                        printf("\nPitStop accepted.");                  //LOG
#endif
                                                                    }
                                                                    else {
                                                                        if (PS_NOTASKED == pstopStatus) {
                                                                            pstopStatus = PS_NOTACCEPTED;
                                                                            pstopPenaltyCounter++;
#ifdef LSRACER_LOG
                                                                            printf("\nPitStop NOT accepted.");          //LOG
#endif
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        if (pstopDeltaTime > tempGP.pitstopTime) {
                                                            pstopStatus = PS_NOTASKED;
                                                            pstopCounter++;
                                                            pstopDeltaTime = 0;
#ifdef LSRACER_LOG
                                                            printf("\nPitStop ended.");
#endif
                                                        }
                                                        //Adding to the elapsed time every 0.05 sec to improve precision.
                                                        if (timeDelta >= 0.05f) {
                                                            timeElapsed += 0.05f;
                                                            if (PS_ACCEPTED == pstopStatus || PS_NOTACCEPTED == pstopStatus) {
                                                                pstopDeltaTime += 0.05f; //If in a time penalty, counting the time it's on stop.
                                                            }
                                                            else {
                                                                playerElapsed += 0.05f;
                                                            }
                                                            timeInitial = (float)clock();
                                                        }

                                                        if (RACE_INPROGRESS == raceStatus) {
                                                            if (playerElapsed >= playerCar->time || 1 == (*aux)) {

                                                                raceStatus = RACE_FINISHED;
#ifdef LSRACER_LOG
                                                                printf("\n%d", playerCar->time);                        //LOG
#endif
                                                                if (pstopCounter < playerCar->pstopQty) {
                                                                    //Adding the penalty if one or more pit-stops were missed.
                                                                    playerCar->time += (playerCar->pstopQty - pstopCounter) * tempGP.pitstopTime + (pstopPenaltyCounter * 5 * tempGP.pitstopTime);
                                                                }

                                                                SortedLD temporary = SortedL_create();
                                                                SortedL_goToHead(&temporary);

                                                                for (i = 0; i < pilotQty; i++) {
                                                                    users[i].time = otherCars[i].time;
                                                                    strcpy(users[i].name, pilots[i].name);
                                                                    users[i].totalPoints =
                                                                    printf(" %s - %s - ", users[i].name, pilots[i].name);
                                                                    SortedL_sortedAdd(&temporary, users[i]);
                                                                }

                                                                users[pilotQty].time = playerCar->time;
                                                                strcpy(users[pilotQty].name, driver->driverName);
                                                                SortedL_sortedAdd(&temporary, users[pilotQty]);
                                                                SortedL_goToHead(&temporary);

                                                                for (i = 0; i <= pilotQty && !SortedL_isAtEnd(temporary); i++) {
                                                                    int score;
                                                                    User tempuser = SortedL_get(&temporary);

                                                                    switch (i) {
                                                                        case 0:
                                                                            score = 25;
                                                                            break;
                                                                        case 1:
                                                                            score = 18;
                                                                            break;
                                                                        case 2:
                                                                            score = 15;
                                                                            break;
                                                                        case 3:
                                                                            score = 10;
                                                                            break;
                                                                        case 4:
                                                                            score = 8;
                                                                            break;
                                                                        case 5:
                                                                            score = 6;
                                                                            break;
                                                                        case 6:
                                                                            score = 5;
                                                                            break;
                                                                        case 7:
                                                                            score = 3;
                                                                            break;
                                                                    }

                                                                    tempuser.totalPoints += score;
                                                                    SortedL_sortedAddScore(&(standings[tempGP.place-1]), tempuser);
                                                                    SortedL_next(&temporary);
                                                                }

                                                                SortedL_goToHead(&(standings[tempGP.place-1]));
                                                                SortedL_destroy(&temporary);
                                                            }
                                                            else {
                                                                calculatePos(playerCar, otherCars, pilotQty, &carPos, timeElapsed, playerElapsed, playerTime, pstopStatus, aux);

                                                                //Printing race screen.
                                                                printRace(darkMode, driver, playerCar, pilots, pilotQty, timeElapsed, tempGP.pitstopTime - pstopDeltaTime,
                                                                          pstopCounter, tempGP.pitstopQty, pstopStatus, carPos, carImage);
                                                            }
                                                        }
                                                        else {
                                                            printFinish(darkMode, driver, pilotQty, &(standings[tempGP.place-1]));
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (RACE_FINISHED == raceStatus) {
                                            SORTEDLIST_getPointer(season)->completed = TRUE;
                                            //SORTEDLIST_next(season);
                                        }

                                        LS_allegro_exit();
                                    }

                                    break;
                                //endregion

                                //region OPTION 3
                                case 3:
                                    //TODO option 3
#ifdef LSRACER_LOG
                                    printf("\nInside option 3.");
#endif
                                    completed = FALSE;

                                    for (i = 0; i < season->size; i++) {
                                        if (SORTEDLIST_get(season).completed) {
                                            completed = TRUE;
                                            break;
                                        }
                                        //printf("!%s!", SortedL_get(&standings[SORTEDLIST_get(season).place]).name);
                                        if (SORTEDLIST_isAtEnd(*season)) {
                                            SORTEDLIST_goToHead(season);
                                        }
                                        else {
                                            SORTEDLIST_next(season);
                                        }
                                        printf("-%d", i);
                                    }
                                    if (SORTEDLIST_isAtEnd(*season)) {
                                        SORTEDLIST_goToHead(season);
                                    }

                                    printf("\n/////////////////\n%s: %d\n/////////////////\n", SORTEDLIST_get(season).name, SORTEDLIST_get(season).place);

                                    if (FALSE == completed) {
                                        //no gp has been completed
                                        printf("\nThe season hasn't started yet.\n");
                                    }
                                    else {
                                        //one or more gps have been completed
                                        LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_RACE);

                                        allegroExit = 0;

                                        //Infinite loop until ESC is pressed.
                                        while (!allegroExit) {
                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                                                allegroExit = 1;
                                            } else {
                                                if (LS_allegro_key_pressed(ALLEGRO_KEY_H)) {
                                                    switchDarkMode(&darkMode);
                                                } else {
                                                    if (LS_allegro_key_pressed(ALLEGRO_KEY_A)) {
                                                        //go left - one less (going through all list except one so it ends at the one before the pov)
                                                        if (season->previous->element.completed) {
                                                            for (i = 0; i < season->size; i++) {
                                                                if (SORTEDLIST_isAtEnd(*season)) {
                                                                    SORTEDLIST_goToHead(season);
                                                                } else {
                                                                    SORTEDLIST_next(season);
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_D)) {
                                                            //go right - one more
                                                            if (season->previous->next->next->element.completed) {
                                                                SORTEDLIST_next(season);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            printf("\n------------------\n%s: %d\n------------------\n", SORTEDLIST_get(season).name, SORTEDLIST_get(season).place);
                                            printStandings(darkMode, &(standings[SORTEDLIST_get(season).place - 1]),
                                                           SORTEDLIST_get(season).name);
                                        }
                                        LS_allegro_exit();
                                    }
                                    break;
                                //endregion

                                //region OPTION 4
                                case 4:
                                    printf("\nNot done yet\n");
                                    //TODO option 4
                                    break;
                                //endregion

                                default:
                                    printf("\nALGO HEM FET MALAMENT PERQUE AIXO NO HAURIA DE SORTIR MAI\n");
                                    exit = 1;
                                    break;
                            }

                        } while (!exit);
                    }
                    for (i = 0; i < season->size; i++) {
                        SortedL_destroy(&(standings[i]));
                    }
                }
            }
        }
    }
    else {
        printf("\nError. The program should have 4 arguments.");
    }

    //TODO all frees
    SORTEDLIST_destroy(season);
    free(partGroup);
    free(playerCar);
    free(driver);
    free(pilots);

    return 0;
}