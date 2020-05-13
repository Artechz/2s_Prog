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


int main (void) {

    Driver * driver;
    GroupPart * partGroup;
    SortedList * season;

    //partGroup = (GroupPart *) malloc(sizeof(GroupPart));

    int optionSelected;
    int i, optionDone = 0, exit = 0, allegroExit = 0, partCategory = 0, partModel = 0, darkMode = 0;

    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * partImages[6];

    do {
        //readSeason(season);
        printf("\nWelcome to LS Racing\n\n");
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

                //Reading the parts file and putting all parts info into partGroup.
                partGroup = readParts(partGroup);

                LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_CONFIGURATOR);

                //printf("\nPath: %s\n", al_get_current_directory());

                //Loading the images as a bitmap, checking they loaded properly.
                background = al_load_bitmap(BACKGROUND_IMAGE);
                if (!background) {
                    printf("Failed to load background bitmap.\n");
                }

                partImages[0] = al_load_bitmap(TIRES_IMAGE);
                if (!partImages[0]) {
                    printf("Failed to load tires bitmap.\n");
                }
                partImages[1] = al_load_bitmap(AEROFRONT_IMAGE);
                if (!partImages[1]) {
                    printf("Failed to load aero front bitmap.\n");
                }
                partImages[2] = al_load_bitmap(AEROMID_IMAGE);
                if (!partImages[2]) {
                    printf("Failed to load aero mid bitmap.\n");
                }
                partImages[3] = al_load_bitmap(AEROREAR_IMAGE);
                if (!partImages[3]) {
                    printf("Failed to load aero rear bitmap.\n");
                }
                partImages[4] = al_load_bitmap(FUEL_IMAGE);
                if (!partImages[4]) {
                    printf("Failed to load fuel bitmap.\n");
                }
                partImages[5] = al_load_bitmap(ENGINE_IMAGE);
                if (!partImages[5]) {
                    printf("Failed to load engine bitmap.\n");
                }


                //Infinite loop until ESC is pressed.
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
                                printf("<- ");
                                //going left
                                printf("sub%d ", partModel);

                                if (partModel != 0) {
                                    partModel--;
                                } else {
                                    partModel = partGroup->parts[partCategory].numParts-1;
                                }

                                printf("sub%d ", partModel);
                                partGroup->parts[partCategory].selected = partModel;

                            } else {
                                if (LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)) {
                                    printf("-> ");
                                    //going right
                                    printf("sub%d ", partModel);

                                    if (partModel != partGroup->parts[partCategory].numParts-1) {
                                        partModel++;
                                        printf("add%d ", partModel);
                                    } else {
                                        partModel = 0;
                                        printf("0%d ", partModel);
                                    }

                                    partGroup->parts[partCategory].selected = partModel;
                                } else {
                                    if (LS_allegro_key_pressed(ALLEGRO_KEY_UP)) {
                                        printf("^ ");
                                        //going up
                                        if (partCategory != partGroup->numParts-1) {
                                            printf("sub%d ", partCategory);
                                            partCategory++;
                                            printf("add%d ", partCategory);
                                        } else {
                                            printf("sub%d ", partCategory);
                                            partCategory = 0;
                                            printf("add%d ", partCategory);
                                        }
                                    } else {
                                        if (LS_allegro_key_pressed(ALLEGRO_KEY_DOWN)) {
                                            printf("v ");
                                            //going down
                                            if (partCategory != 0) {
                                                printf("sub%d ", partCategory);
                                                partCategory--;
                                                printf("sub%d ", partCategory);
                                            } else {
                                                printf("sub%d ", partCategory);
                                                partCategory = partGroup->numParts-1;
                                                printf("sub%d ", partCategory);
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
                /*
                if (!optionDone) {
                    printf("\nERROR: Car needs to be configured before racing.");
                }
                else {
                */
                    SortedList damn;
                    damn = SORTEDLIST_create();
                    season = &damn;
                    if (readSeason(season)) {
                        printf("\nThere was an error getting the season info");
                    }
                    else {
                        SORTEDLIST_goToHead(season);
                        printf("%s", SORTEDLIST_get(season).name);

                        printf("\nLoading Race ...");

                        LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_RACE);

                        //Infinite loop until ESC is pressed.
                        while (!allegroExit) {

                            //Checking if ESC or any arrow is being pressed.
                            if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                                allegroExit = 1;
                            }

                            //Printing race info.
                            printGP(darkMode, SORTEDLIST_get(season));

                            //'Painting' the graphic screen.
                            LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));

                        }

                        //SORTEDLIST_get(season).completed = 1;
                        //SORTEDLIST_next(season);
                        LS_allegro_exit();
                    }

                //}

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