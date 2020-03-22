#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LS_allegro.h"
#define MAXSTRING 26

typedef struct {
    char driverName[MAXSTRING];
    char teamName[MAXSTRING];
    int driverNumber;
    int reflexes;
    int physicalCondition;
    int temperament;
    int tireManagement;
} Driver;

int menuAsk (char question[MAXSTRING], int min, int max) {

    char input[MAXSTRING];
    int check, i;

    do {
        check = 1;                                                                                              //DEBUG
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
    char input[MAXSTRING];
    int check = 1, i, optionRunned = 0;
    char aux;

    printf("Welcome to LS Racing\n\n");
    printf("\t 1. Configure Car\n");
    printf("\t 2. Race\n");
    printf("\t 3. See Standings\n");
    printf("\t 4. Save Season\n\n");

    optionSelected = menuAsk("Which option do you want to execute? ", 1, 4);

    switch (optionSelected) {

        //OPTION 1
        case 1:

            if(optionRunned == 0){

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

                optionRunned = 1;
            }

            break;

        //OPTION 2
        case 2:
            printf("Not done yet");
            break;

        //OPTION 3
        case 3:
            printf("Not done yet");
            break;

        //OPTION 4
        case 4:
            printf("Not done yet");
            break;

        default:
            printf("\nALGO HEM FET MALAMENT PERQUE AIXO NO HAURA DE SORTIR MAI\n");
            break;
    }


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