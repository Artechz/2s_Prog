/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 18/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 22/03/2020
 *
***********************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LS_allegro.h"
#define MAXSTRING 26
#define WIN_TITLE "LS Racing by Arnau Sanz & Josep Segarra"
#define WIN_WIDTH 1000
#define WIN_HEIGHT 600
#define BACKGROUND_IMAGE "files/boxes.png"
#define TIRES_IMAGE "files/neumaticos.png"

typedef struct {
    char driverName[MAXSTRING];
    char teamName[MAXSTRING];
    int driverNumber;
    int reflexes;
    int physicalCondition;
    int temperament;
    int tireManagement;
} Driver;

/***********************************************
 *
 * @Purpose: Asks the user a question, checks the answers for errors within a valid
 *           range of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return: Returns the atoi of the input.
 *
************************************************/
int menuAsk (char question[MAXSTRING], int min, int max) {

    char input[MAXSTRING];
    int check, i;

    do {
        check = 1;                                                                                                      //DEBUG
        printf("%s", question);
        fgets(input, MAXSTRING, stdin);
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

int main (void) {
    Driver driver;
    int optionSelected;
    //char input[MAXSTRING];
    int i, optionDone = 0, exit = 0, allegroExit = 0;
    //char aux;
    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_BITMAP * tires = NULL;

    int background_color = BLACK;    //TODO
    int text_color = WHITE;

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

                LS_allegro_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

                printf("\nPath: %s", al_get_current_directory());                                                       //DEBUG

                //Loading the image as a bitmap, checking it loaded properly and saving its size for future scaling.
                background = al_load_bitmap(BACKGROUND_IMAGE);
                if (!background) {
                    printf("Failed to load background bitmap!\n");
                }

                const int background_width = al_get_bitmap_width(background);
                const int background_height = al_get_bitmap_height(background);

                tires = al_load_bitmap(TIRES_IMAGE);
                if (!tires) {
                    printf("Failed to load tires bitmap!\n");
                }

                const int tires_width = al_get_bitmap_width(tires);
                const int tires_height = al_get_bitmap_height(tires);
                const int tires_width_scaled =  al_get_bitmap_width(tires)/(WIN_WIDTH/200);
                const int tires_height_scaled =  al_get_bitmap_height(tires)/(WIN_WIDTH/200);
                const int tires_margin = tires_height_scaled/5;

                //Infinite loop until ESC is pressed.
                while (!allegroExit) {

                    //Checking if ESC is pressed.
                    if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                        allegroExit = 1;
                    }

                    //Scales the boxes image to a size that fits the actual window.
                    al_draw_scaled_bitmap (background, 0, 0, background_width, background_height, 0, 0, (WIN_WIDTH/5)*3, WIN_HEIGHT, 0);
                    //Scaled the tires image so it's not too big for the arrows to have space.
                    al_draw_scaled_bitmap (tires, 0, 0, tires_width, tires_height, WIN_WIDTH/5*3.4, WIN_HEIGHT/5, tires_width_scaled, tires_height_scaled, 0);


                    //Printing arrows
                    //LEFT ARROW
                    al_draw_line ( WIN_WIDTH/5*3.4 - tires_margin, WIN_HEIGHT/5 + tires_height_scaled/2, WIN_WIDTH/5*3.4 - 20 - tires_margin,
                            WIN_HEIGHT/5 + tires_height_scaled/2, LS_allegro_get_color(text_color), WIN_HEIGHT/50);
                    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 - 40 - tires_margin, WIN_HEIGHT/5 + tires_height_scaled/2, WIN_WIDTH/5*3.4 - 20 - tires_margin,
                            WIN_HEIGHT/5 + 15 + tires_height_scaled/2, WIN_WIDTH/5*3.4 - 20 - tires_margin, WIN_HEIGHT/5-15 + tires_height_scaled/2, LS_allegro_get_color(text_color));
                    //RIGHT ARROW
                    al_draw_line ( WIN_WIDTH/5*3.4 + tires_margin + tires_width_scaled, WIN_HEIGHT/5 + tires_height_scaled/2, WIN_WIDTH/5*3.4 + 20 + tires_width_scaled + tires_margin,
                                   WIN_HEIGHT/5 + tires_height_scaled/2, LS_allegro_get_color(text_color), WIN_HEIGHT/50);
                    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + 40 + tires_width_scaled + tires_margin, WIN_HEIGHT/5 + tires_height_scaled/2, WIN_WIDTH/5*3.4 + 20 + tires_width_scaled + tires_margin,
                                              WIN_HEIGHT/5 + 15 + tires_height_scaled/2, WIN_WIDTH/5*3.4 + 20 + tires_width_scaled + tires_margin, WIN_HEIGHT/5 - 15 + tires_height_scaled/2, LS_allegro_get_color(text_color));
                    //UP ARROW
                    al_draw_line ( WIN_WIDTH/5*3.4 + tires_width_scaled/2, WIN_HEIGHT/5 - tires_margin, WIN_WIDTH/5*3.4 + tires_width_scaled/2,
                                   WIN_HEIGHT/5 - 20 - tires_margin, LS_allegro_get_color(text_color), WIN_HEIGHT/50);
                    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + tires_width_scaled/2, WIN_HEIGHT/5 - 40 - tires_margin, WIN_WIDTH/5*3.4 - 15 + tires_width_scaled/2,
                                              WIN_HEIGHT/5 - 20 - tires_margin, WIN_WIDTH/5*3.4 + 15 + tires_width_scaled/2, WIN_HEIGHT/5 - 20 - tires_margin, LS_allegro_get_color(text_color));
                    //DOWN ARROW
                    al_draw_line ( WIN_WIDTH/5*3.4 + tires_width_scaled/2, WIN_HEIGHT/5 + tires_margin + tires_height_scaled, WIN_WIDTH/5*3.4 + tires_width_scaled/2,
                                   WIN_HEIGHT/5 + 20 + tires_margin + tires_height_scaled, LS_allegro_get_color(text_color), WIN_HEIGHT/50);
                    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + tires_width_scaled/2, WIN_HEIGHT/5 + 40 + tires_margin + tires_height_scaled, WIN_WIDTH/5*3.4 - 15 + tires_width_scaled/2,
                                              WIN_HEIGHT/5 + 20 + tires_margin + tires_height_scaled, WIN_WIDTH/5*3.4 + 15 + tires_width_scaled/2, WIN_HEIGHT/5 + 20 + tires_margin + tires_height_scaled, LS_allegro_get_color(text_color));

                    //Printing text
                    al_draw_textf (LS_allegro_get_font(LARGE), LS_allegro_get_color(text_color), (WIN_WIDTH/4)*3,WIN_HEIGHT/5 - 80,0,"%s","TIRES");
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), (WIN_WIDTH/6)*5,WIN_HEIGHT/5 - 20,0,"%s","C5");
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), (WIN_WIDTH/6)*5,WIN_HEIGHT/5,0,"%s%d","SPEED: ", 5);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), (WIN_WIDTH/6)*5,WIN_HEIGHT/5 + 20,0,"%s%d","ACCELERATION: ", 5);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), (WIN_WIDTH/6)*5,WIN_HEIGHT/5 + 40,0,"%s%d","CONSUMPTION: ", -2);
                    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), (WIN_WIDTH/6)*5,WIN_HEIGHT/5 + 60,0,"%s%d","RELIABILITY: ", 2);

                    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3, 0, "%s", "CURRENT CONFIGURATION");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 40, 0, "%s%s", "TIRES: ", "C5");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 60, 0, "%s%s", "AERO FRONT: ", "LOW LOAD");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 80, 0, "%s%s", "AERO MID: ", "MID LOAD");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 100, 0, "%s%s", "AERO REAR: ", "HIGH LOAD");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 120, 0, "%s%s", "FUEL: ", "REGULAR");
                    al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(text_color), WIN_WIDTH/5*3.2, WIN_HEIGHT/5*3 + 140, 0, "%s%s", "ENGINE: ", "SPEC C");



                    //'Painting' the graphic screen.
                    LS_allegro_clear_and_paint(background_color);
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

    /*int nSortir = 0;

    //Inicialitzem Allegro
    LS_allegro_init(800,600,"Projecte 2");


    //Bucle infinit del joc
    while(!nSortir){

        //Escoltem el teclat esperant la tecla ESC
        if(LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)){
            nSortir = 1;
        }

        //Donem l'ordre d'escriure el text de benvinguda
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),140,100,0,"%s","Heyy! Prem ESC per sortir...");

        //Pintem la pantalla de la finestra gràfica
        LS_allegro_clear_and_paint(BLACK);
    }


    //Tanquem la finestra gràfica
    LS_allegro_exit();*/



    return 0;
}