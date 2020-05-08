/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 18/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LS_allegro.h"
#include "my_race_basic.h"
#include "my_allegro_ui.h"
#include "my_files.h"


int main (void) {

    Driver driver;
    GroupPart * partGroup;

    //partGroup = (GroupPart *) malloc(sizeof(GroupPart));

    int optionSelected;
    int i, optionDone = 0, exit = 0, allegroExit = 0, partCategory = 0, partModel = 0, darkMode = 0;

    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * parts[6];

    do {

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

                    printf("Driver Name? ");
                    fgets(driver.driverName, MAXSTRING, stdin);
                    driver.driverName[strlen(driver.driverName) - 1] = '\0';

                    printf("Team Name? ");
                    fgets(driver.teamName, MAXSTRING, stdin);
                    driver.teamName[strlen(driver.teamName) - 1] = '\0';

                    driver.driverNumber = menuAsk("Drivers Number? ", 0, 99);

                    driver.reflexes = menuAsk("Reflexes? ", 0, 10);

                    driver.physicalCondition = menuAsk("Physical Condition? ", 0, 10);

                    driver.temperament = menuAsk("Temperament? ", 0, 10);

                    driver.tireManagement = menuAsk("Tire management? ", 0, 10);

                    optionDone = 1;
                }
                printf("\nLoading Configurator ...");

                partGroup = readParts(partGroup);                                                                                  //READING PARTS INFO

                LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE_CONFIGURATOR);

                printf("\nPath: %s\n", al_get_current_directory());                                                       //DEBUG

                //Loading the image as a bitmap, checking it loaded properly and saving its size for future scaling.
                background = al_load_bitmap(BACKGROUND_IMAGE);
                if (!background) {
                    printf("Failed to load background bitmap.\n");
                }

                parts[0] = al_load_bitmap(TIRES_IMAGE);
                if (!parts[0]) {
                    printf("Failed to load tires bitmap.\n");
                }
                //parts[1] = al_load_bitmap(//TODO);
                if (!parts[1]) {
                    printf("Failed to load aero front bitmap.\n");
                }
                //parts[2] = al_load_bitmap(//TODO);
                if (!parts[2]) {
                    printf("Failed to load aero mid bitmap.\n");
                }
                //parts[3] = al_load_bitmap(//TODO);
                if (!parts[3]) {
                    printf("Failed to load aero rear bitmap.\n");
                }
                parts[4] = al_load_bitmap(FUEL_IMAGE);
                if (!parts[4]) {
                    printf("Failed to load fuel bitmap.\n");
                }
                parts[5] = al_load_bitmap(ENGINE_IMAGE);
                if (!parts[5]) {
                    printf("Failed to load engine bitmap.\n");
                }//TODO put images


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
                        else {
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

                    printConfig(background, parts, partCategory, darkMode);

                    //Printing text
                    printText(TITLE, darkMode, (WIN_WIDTH / 4) * 3, WIN_HEIGHT / 5 - 80, "%s", partGroup->parts[partCategory].name);
                    printText(SMALL, darkMode, (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 - 20, "%s", partGroup->parts[partCategory].type[partModel].name);
                    //al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 - 20, 0, "%s", partGroup->parts[partCategory].type[partModel].name);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5, 0, "%s%d", "SPEED: ", partGroup->parts[partCategory].type[partModel].speed);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 20, 0, "%s%d", "ACCELERATION: ", partGroup->parts[partCategory].type[partModel].acceleration);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 40, 0, "%s%d", "CONSUMPTION: ", partGroup->parts[partCategory].type[partModel].consumption);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 60, 0, "%s%d", "RELIABILITY: ", partGroup->parts[partCategory].type[partModel].reliability);

                    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3, 0, "%s", "CURRENT CONFIGURATION");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 40, 0, "%s%s", "TIRES: ", partGroup->parts[0].type[partGroup->parts[0].selected].name);
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 60, 0, "%s%s", "AERO FRONT: ", partGroup->parts[1].type[partGroup->parts[1].selected].name);
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 80, 0, "%s%s", "AERO MID: ", partGroup->parts[2].type[partGroup->parts[2].selected].name);
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 100, 0, "%s%s", "AERO REAR: ", partGroup->parts[3].type[partGroup->parts[3].selected].name);
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 120, 0, "%s%s", "FUEL: ", partGroup->parts[4].type[partGroup->parts[4].selected].name);
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 140, 0, "%s%s", "ENGINE: ", partGroup->parts[5].type[partGroup->parts[5].selected].name);



                    //'Painting' the graphic screen.
                    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
                }

                //Tanquem la finestra gràfica
                LS_allegro_exit();

                break;

                //OPTION 2
            case 2:
                printf("\nNot done yet\n");
                //TODO
                break;

                //OPTION 3
            case 3:
                printf("\nNot done yet\n");
                //TODO
                break;

                //OPTION 4
            case 4:
                printf("\nNot done yet\n");
                //TODO
                break;

            default:
                printf("\nALGO HEM FET MALAMENT PERQUE AIXO NO HAURIA DE SORTIR MAI\n");
                exit = 1;
                break;
        }

    } while (!exit);

    free(partGroup);

    return 0;
}