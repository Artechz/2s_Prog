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

int main (int argc, char * argv[]) {

    int  exit = 0, allegroExit = 0, optionDone = 0, optionSelected = 0, darkMode = WHITE, i;
    int partCategory = 0, partModel = 0, traffLightStatus, isTLOn[5], pstopStatus, pilotQty, pstopCounter, raceStatus, playerTime;
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

    //printf("\n%s || %s || %s || %s ", argv[1], argv[2], argv[3], argv[4]);

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
                    SortedLD standings[season->size];
                    for (i = 0; i < season->size; i++) {
                        standings[i] = SortedL_create();
                    }
                    //Reading the Base file and putting all info into baseStats while managing a possible error.
                    if(!fileErrorManage(readBase(baseStats, argv[4]))) {
                        //Adding Base stats to all pilots (player is done below when settin up car in option 1).
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

                            optionSelected = menuAsk("Which option do you want to execute? ", 1, 5);
                            switch (optionSelected) {

                                //OPTION 1
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
                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_D)) {
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

                                //OPTION 2
                                case 2:
                                    printf("\nWIP\n");
                                    //TODO option 2

                                    if (!optionDone) {
                                        printf("\nERROR: Car needs to be configured before racing.");
                                    }
                                    else {
                                        raceStatus = RACE_INPROGRESS;
                                        traffLightStatus = TL_NOT_SHOWN;
                                        pstopStatus = PS_NOTASKED;
                                        pstopCounter = 0;
                                        pstopDeltaTime = 0;
                                        playerElapsed = 0;

                                        SORTEDLIST_goToHead(season);
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
                                                if (LS_allegro_key_pressed(ALLEGRO_KEY_D)) {
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

                                                    if (0 == isTLOn[0]) {
                                                        if (timeDelta >= 1.0) {
                                                            isTLOn[0] = 1;
                                                            isTLOn[1] = 1;
                                                            timeInitial = (float)clock();
                                                        }
                                                    }
                                                    else {
                                                        if (0 == isTLOn[2]) {
                                                            if (timeDelta >= 1.0) {
                                                                isTLOn[2] = 1;
                                                                timeInitial = (float)clock();
                                                            }
                                                        }
                                                        else {
                                                            if (0 == isTLOn[3]) {
                                                                if (timeDelta >= 1.0) {
                                                                    isTLOn[3] = 1;
                                                                    timeInitial = (float)clock();
                                                                }
                                                            }
                                                            else {
                                                                if (0 == isTLOn[4]) {
                                                                    if (timeDelta >= 1.0) {
                                                                        isTLOn[4] = 1;
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
                                                            printf("\nRadioed in. ");                            //DEBUG //TODO remove
                                                            pstopStatus = PS_ASKED;
                                                            printf("Code: %d", *aux);
                                                        }
                                                        else {
                                                            if (LS_allegro_key_pressed(ALLEGRO_KEY_P)) {
                                                                if (pstopCounter < tempGP.pitstopQty) {
                                                                    printf("\nPitStop requested.");                 //DEBUG //TODO remove
                                                                    if (PS_ASKED == pstopStatus) {
                                                                        pstopStatus = PS_ACCEPTED;
                                                                        printf("\nPitStop accepted.");              //DEBUG //TODO remove
                                                                        pstopCounter++;
                                                                    }
                                                                    else {
                                                                        if (PS_NOTASKED == pstopStatus) {
                                                                            printf("\nPitStop NOT accepted.");          //DEBUG //TODO remove
                                                                            pstopStatus = PS_NOTACCEPTED;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }

                                                        if (pstopDeltaTime > tempGP.pitstopTime) {
                                                            pstopStatus = PS_NOTASKED;
                                                            printf("\nPitStop ended.");
                                                            pstopDeltaTime = 0;
                                                        }
                                                        //Adding to the elapsed time every 0.05 sec to improve precision.
                                                        if (timeDelta >= 0.05) {
                                                            timeElapsed += 0.05;
                                                            if (PS_ACCEPTED == pstopStatus || PS_NOTACCEPTED == pstopStatus) {
                                                                pstopDeltaTime += 0.05; //If in a time penalty, counting the time it's on stop.
                                                            }
                                                            else {
                                                                playerElapsed += 0.05;
                                                            }
                                                            timeInitial = (float)clock();
                                                        }

                                                        if (RACE_INPROGRESS == raceStatus) {
                                                            if (playerElapsed >= playerCar->time || (*aux) > 3710) {
                                                                printf("\n%d", playerCar->time);
                                                                raceStatus = RACE_FINISHED;
                                                                printf("\n0 ");
                                                                if (pstopCounter < playerCar->pstopQty) {
                                                                    //Adding the penalty if one or more pitsotps were missed.
                                                                    playerCar->time += (playerCar->pstopQty - pstopCounter) * tempGP.pitstopTime;
                                                                }
                                                                printf("1 ");
                                                                SortedLD temporary = SortedL_create();
                                                                for (i = 0; i < pilotQty; i++) {
                                                                    users[i].time = otherCars[i].time;
                                                                    strcpy(users[i].name, pilots[i].name);
                                                                    SortedL_sortedAdd( &temporary, users[i]);
                                                                }
                                                                printf("2 ");
                                                                users[pilotQty].time = playerCar->time;
                                                                strcpy(users[pilotQty].name, driver->driverName);
                                                                SortedL_sortedAdd(&temporary, users[pilotQty]);
                                                                printf("3 ");
                                                                SortedL_goToHead(&temporary);
                                                                for (i = 0; i <= pilotQty && !SortedL_isAtEnd(temporary); i++) {
                                                                    int score;
                                                                    printf("3.01 ");
                                                                    User tempuser = SortedL_get(&temporary);
                                                                    printf("3.1 ");
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
                                                                    printf("3.2 ");
                                                                    tempuser.totalPoints = score;
                                                                    printf("3.3 ");
                                                                    SortedL_sortedAddScore(&(standings[tempGP.place-1]), tempuser);
                                                                    printf("3.4.%d ", i);
                                                                }
                                                                printf("4 ");
                                                                SortedL_destroy(&temporary);
                                                                printf("5 ");
                                                            }
                                                            else {
                                                                calculatePos(playerCar, otherCars, pilotQty, &carPos, timeElapsed, playerElapsed, playerTime, pstopCounter, pstopStatus, pstopDeltaTime, aux, tempGP);

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
                                        if (RACE_FINISHED == raceStatus) SORTEDLIST_next(season);
                                        //SORTEDLIST_get(season).completed = 1;
                                        //SORTEDLIST_next(season);
                                        LS_allegro_exit();
                                    }

                                    break;

                                    //OPTION 3
                                case 3:
                                    printf("\nNot done yet\n");
                                    //TODO option 3
                                    break;

                                    //OPTION 4
                                case 4:
                                    printf("\nNot done yet\n");
                                    //TODO option 4
                                    break;

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