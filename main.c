#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LS_allegro.h"
#define MAXSTRING 26

typedef struct {
    char driverName[MAXSTRING];
    char teamName[MAXSTRING];
    char driverNumber[MAXSTRING];
    char reflexes[MAXSTRING];
    char physicalCondition[MAXSTRING];
    char temperament[MAXSTRING];
    char tireManagement[MAXSTRING];
} Driver;

int main (void) {
    Driver driver;
    char OptionSelected[MAXSTRING];
    int check = 1, i;
    char aux;


    printf("Welcome to LS Racing\n\n");
    printf("\t 1. Configure Car\n");
    printf("\t 2. Race\n");
    printf("\t 3. See Standings\n");
    printf("\t 4. Save Season\n\n");
    do {
        printf("Which option do you want to execute? ");
        scanf("%s", OptionSelected);
        scanf("%c", &aux);
        if (strlen(OptionSelected) != 1){
            printf("Error, the number should be between 1 and 4, inclusive.\n");
        }
        else {
            if (OptionSelected[0] < '1' || OptionSelected[0] > '4') {
                printf("Error, the number should be between 1 and 4, inclusive.");
            }
            else {
                check = 1;
            }
        }
    } while (0 == check);

    printf("Driver Name? ");
    fgets(driver.driverName, MAXSTRING, stdin);
    driver.driverName[strlen(driver.driverName) - 1] = '\0';

    printf("Team Name? ");
    fgets(driver.teamName, MAXSTRING, stdin);
    driver.teamName[strlen(driver.teamName) - 1] = '\0';

     do {
        printf("Drivers Number? ");
        fgets(driver.driverNumber, MAXSTRING, stdin);
        driver.driverNumber[strlen(driver.driverNumber) - 1] = '\0';
        if (strlen(driver.driverNumber) > 2){
            check = 0;
            printf("strlenDNum > 2");                                                                                   //DEBUG
        }
        else {
            for (i = 0; i < strlen(driver.driverNumber); i++) {
                if (driver.driverNumber[i] < '0' || driver.driverNumber[i] > '9') {
                    check = 0;
                }
            }
            if (check) {
                if (atoi(driver.driverNumber) > 99) {
                    check = 0;
                }
            }
        }
        if (0 == check) {
            printf("Error, the number should be between 0 and 99, inclusive.\n");
        }
    } while (0 == check);

    do {
        //check = 1;                                                                                                    //DEBUG
        printf("Reflexes? ");
        fgets(driver.reflexes, MAXSTRING, stdin);
        driver.reflexes[strlen(driver.reflexes) - 1] = '\0';
        if (strlen(driver.reflexes) > 2) {
            check = 0;
        }
        else {
            if(!(atoi(driver.reflexes) <= 10)) {
                    check = 0;
            }
        }
        if (0 == check) {
            printf("Error, the number should be between 0 and 10, inclusive.\n");
        }
    } while (0 == check);

    check = 0;


    printf("\nDriver Name? ");

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