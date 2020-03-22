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
#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define BACKGROUND_FILE "/files/boxes.png"

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

                background = al_load_bitmap(BACKGROUND_FILE);
                if (!background) {
                    printf("Failed to load background bitmap!\n");
                }

                //Bucle infinit del joc
                while (!allegroExit) {

                    //Escoltem el teclat esperant la tecla ESC
                    if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                        allegroExit = 1;
                    }

                    al_draw_bitmap(background,0,0,0);

                    //Donem l'ordre d'escriure el text de benvinguda
                    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE),140,100,0,"%s","Heyy! Prem ESC per sortir...");

                    //Pintem la pantalla de la finestra gràfica
                    LS_allegro_clear_and_paint(BLACK);
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