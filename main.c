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

#define NOT_SHOWN 0
#define SHOWING 1
#define ALREADY_SHOWN 2

int main (void) {

    int  exit = 0, allegroExit = 0, optionDone = 0, optionSelected = 0, traffLightStatus, isTLOn[5], i;
    int partCategory = 0, partModel = 0, darkMode = 0;
    float timeInitial, timeMeasured, timeDelta = 0;

    Driver * driver;
    GroupPart * partGroup;
    SortedList * season;

    //printf("\nPath: %s\n", al_get_current_directory());
    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * partImages[6];

    driver = (Driver *) malloc(sizeof(Driver));

    season = (SortedList *) malloc(sizeof(SortedList));

    *season = SORTEDLIST_create();

    //Reading the parts file and putting all parts info into partGroup.
    partGroup = readParts(partGroup);

    readSeason(season);

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

                if (0 == optionDone) {
                    infoAsk(driver);
                    optionDone = 1;
                }

                printf("\nLoading Configurator ...");

                //Starting Allegro, its modules and the graphic window.
                LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_CONFIGURATOR);

                //Loading the images as a bitmap, checking they loaded properly.
                background = al_load_bitmap(BACKGROUND_IMAGE);

                if (!background) {
                    printf("Failed to load background bitmap.\n");
                }
                else {
                    partImages[0] = al_load_bitmap(TIRES_IMAGE);
                    if (!partImages[0]) {
                        printf("Failed to load tires bitmap.\n");
                    }
                    else {
                        partImages[1] = al_load_bitmap(AEROFRONT_IMAGE);
                        if (!partImages[1]) {
                            printf("Failed to load aero front bitmap.\n");
                        }
                        else {
                            partImages[2] = al_load_bitmap(AEROMID_IMAGE);
                            if (!partImages[2]) {
                                printf("Failed to load aero mid bitmap.\n");
                            }
                            else {
                                partImages[3] = al_load_bitmap(AEROREAR_IMAGE);
                                if (!partImages[3]) {
                                    printf("Failed to load aero rear bitmap.\n");
                                }
                                else {
                                    partImages[4] = al_load_bitmap(FUEL_IMAGE);
                                    if (!partImages[4]) {
                                        printf("Failed to load fuel bitmap.\n");
                                    }
                                    else {
                                        partImages[5] = al_load_bitmap(ENGINE_IMAGE);
                                        if (!partImages[5]) {
                                            printf("Failed to load engine bitmap.\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

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
                        else {  //TODO put arrow thingy into my_race_basic
                            if (LS_allegro_key_pressed(ALLEGRO_KEY_LEFT)) {
                                //going left
                                if (partModel != 0) {
                                    partModel--;
                                }
                                else {
                                    partModel = partGroup->parts[partCategory].numParts-1;
                                }

                                partGroup->parts[partCategory].selected = partModel;
                            }
                            else {
                                if (LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)) {
                                    //going right
                                    if (partModel != partGroup->parts[partCategory].numParts-1) {
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
                                        if (partCategory != partGroup->numParts-1) {
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
                                                partCategory = partGroup->numParts-1;
                                            }
                                        }
                                    }
                                    partModel =  partGroup->parts[partCategory].selected;
                                }
                            }
                        }
                    }

                    //Printing all the configuration screen elements.
                    printConfig (background, darkMode, partImages, partCategory, partModel, partGroup);

                    //'Painting' the graphic screen.
                    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
                }

                //Closing the graphic window
                LS_allegro_exit();
                break;

            //OPTION 2
            case 2:
                printf("\nWIP\n");
                //TODO option 2

                if (!optionDone) {
                    printf("\nERROR: Car needs to be configured before racing.");
                }
                else {
                    traffLightStatus = NOT_SHOWN;

                    SORTEDLIST_goToHead(season);
                    printf("%s", SORTEDLIST_get(season).name);

                    printf("\nLoading Race ...");

                    LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_RACE);


                    allegroExit = 0;
                    for (i = 0; i < 5; i++) { isTLOn[i] = 0;}
                    timeInitial = (float)clock();
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
                            }

                            if (NOT_SHOWN  == traffLightStatus) {
                                if (LS_allegro_key_pressed(ALLEGRO_KEY_R)) {
                                    printf("\nR key pressed.");
                                    traffLightStatus = SHOWING;
                                }
                                //Printing race - circuit info.
                                printGP(darkMode, SORTEDLIST_get(season));
                                timeInitial = (float)clock();
                            }
                            else {
                                if (SHOWING == traffLightStatus) {
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
                                                        timeDelta = (float)clock();
                                                    }
                                                }
                                                else {
                                                    if (timeDelta >= 0.5) {
                                                        traffLightStatus = ALREADY_SHOWN;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                else {
                                    if (ALREADY_SHOWN == traffLightStatus) {
                                        //Printing race screen.
                                        //printRace(darkMode);
                                        printf("\nrace mode pls");
                                    }
                                }
                            }
                        }


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

    //TODO all frees
    SORTEDLIST_destroy(season);
    free(partGroup);

    return 0;
}