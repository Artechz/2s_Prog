#include <stdio.h>
#include "LS_allegro.h"
#define MAX 100
int main(void){
    char OptionSelected[MAX];
    int check = 0;


    printf("Welcome to LS Racing\n\n");
    printf("\t 1. Configure Car\n");
    printf("\t 2. Race\n");
    printf("\t 3. See Standings\n");
    printf("\t 4. Save Season\n\n");
    while(check == 0){
        printf("Which option do you want to execute? ");
        scanf("%s", OptionSelected);
        if (strlen(OptionSelected) != 1){
            printf("Error, the number should be between 1 and 4, inclusive.");
        }
        else {
            if (OptionSelected[0] < '1' || OptionSelected[0] > '4') {
                printf("Error, the number should be between 1 and 4, inclusive.");
            }
            else {
                check = 1;
            }
        }
    }

    printf("\nDriver Name? ");

    //this is a comment comeme los cojones
    //segundo comment para test




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