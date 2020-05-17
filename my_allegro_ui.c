/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 09/05/2020
 *
***********************************************/

#include "my_allegro_ui.h"

void printText (int size, int color, int xpos, int ypos, char * input, char * content) {

    al_draw_textf (LS_allegro_get_font(size), LS_allegro_get_color(color), xpos, ypos,0, input, content);
}

void printConfig (ALLEGRO_BITMAP * background, int darkMode, ALLEGRO_BITMAP * parts[6], int partCategory, int partModel, GroupPart * partGroup) {

    const int background_width = al_get_bitmap_width(background);
    const int background_height = al_get_bitmap_height(background);

    const int part_width = al_get_bitmap_width(parts[0]);
    const int part_height = al_get_bitmap_height(parts[0]);
    const int part_width_scaled = al_get_bitmap_width(parts[0]) / (WIN_WIDTH / 200);
    const int part_height_scaled = al_get_bitmap_height(parts[0]) / (WIN_WIDTH / 200);

    int i , margin = 0;

    //Scales the boxes image to a size that fits the actual window.
    al_draw_scaled_bitmap (background, 0, 0, background_width, background_height, 0, 0, (WIN_WIDTH/5)*3, WIN_HEIGHT, 0);
    //Scaled the tires image so it's not too big for the arrows to have space.
    al_draw_scaled_bitmap (parts[partCategory], 0, 0, part_width, part_height, WIN_WIDTH / 5 * 3.4, WIN_HEIGHT / 5, part_width_scaled, part_height_scaled, 0);


    //Drawing arrows
    //LEFT ARROW
    al_draw_line ( WIN_WIDTH/5*3.4 - part_height_scaled / 5, WIN_HEIGHT/5 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 - 20 - part_height_scaled / 5,
                   WIN_HEIGHT/5 + part_height_scaled / 2, LS_allegro_get_color(darkMode), WIN_HEIGHT / 50);
    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 - 40 - part_height_scaled / 5, WIN_HEIGHT/5 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 - 20 - part_height_scaled / 5,
                              WIN_HEIGHT/5 + 15 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 - 20 - part_height_scaled / 5, WIN_HEIGHT / 5 - 15 + part_height_scaled / 2, LS_allegro_get_color(darkMode));
    //RIGHT ARROW
    al_draw_line ( WIN_WIDTH/5*3.4 + part_height_scaled / 5 + part_width_scaled, WIN_HEIGHT / 5 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 + 20 + part_width_scaled + part_height_scaled / 5,
                   WIN_HEIGHT/5 + part_height_scaled / 2, LS_allegro_get_color(darkMode), WIN_HEIGHT / 50);
    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + 40 + part_width_scaled + part_height_scaled / 5, WIN_HEIGHT / 5 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 + 20 + part_width_scaled + part_height_scaled / 5,
                              WIN_HEIGHT/5 + 15 + part_height_scaled / 2, WIN_WIDTH / 5 * 3.4 + 20 + part_width_scaled + part_height_scaled / 5, WIN_HEIGHT / 5 - 15 + part_height_scaled / 2, LS_allegro_get_color(darkMode));
    //UP ARROW
    al_draw_line ( WIN_WIDTH/5*3.4 + part_width_scaled / 2, WIN_HEIGHT / 5 - part_height_scaled / 5, WIN_WIDTH / 5 * 3.4 + part_width_scaled / 2,
                   WIN_HEIGHT/5 - 20 - part_height_scaled / 5, LS_allegro_get_color(darkMode), WIN_HEIGHT / 50);
    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + part_width_scaled / 2, WIN_HEIGHT / 5 - 40 - part_height_scaled / 5, WIN_WIDTH / 5 * 3.4 - 15 + part_width_scaled / 2,
                              WIN_HEIGHT/5 - 20 - part_height_scaled / 5, WIN_WIDTH/5*3.4 + 15 + part_width_scaled / 2, WIN_HEIGHT / 5 - 20 - part_height_scaled / 5, LS_allegro_get_color(darkMode));
    //DOWN ARROW
    al_draw_line ( WIN_WIDTH/5*3.4 + part_width_scaled / 2, WIN_HEIGHT / 5 + part_height_scaled / 5 + part_height_scaled, WIN_WIDTH / 5 * 3.4 + part_width_scaled / 2,
                   WIN_HEIGHT/5 + 20 + part_height_scaled / 5 + part_height_scaled, LS_allegro_get_color(darkMode), WIN_HEIGHT / 50);
    al_draw_filled_triangle ( WIN_WIDTH/5*3.4 + part_width_scaled / 2, WIN_HEIGHT / 5 + 40 + part_height_scaled / 5 + part_height_scaled, WIN_WIDTH / 5 * 3.4 - 15 + part_width_scaled / 2,
                              WIN_HEIGHT/5 + 20 + part_height_scaled / 5 + part_height_scaled, WIN_WIDTH / 5 * 3.4 + 15 + part_width_scaled / 2, WIN_HEIGHT / 5 + 20 + part_height_scaled / 5 + part_height_scaled, LS_allegro_get_color(darkMode));

    //Printing text
    printText (FONT_TITLE, darkMode, (WIN_WIDTH / 4) * 3, WIN_HEIGHT / 5 - 80, "%s", partGroup->parts[partCategory].name);
    printText (SMALL, darkMode, (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 - 20, "%s", partGroup->parts[partCategory].type[partModel].name);

    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5, 0, "%s%d", "SPEED: ", partGroup->parts[partCategory].type[partModel].speed);
    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 20, 0, "%s%d", "ACCELERATION: ", partGroup->parts[partCategory].type[partModel].acceleration);
    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 40, 0, "%s%d", "CONSUMPTION: ", partGroup->parts[partCategory].type[partModel].consumption);
    al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 + 60, 0, "%s%d", "RELIABILITY: ", partGroup->parts[partCategory].type[partModel].reliability);

    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3, 0, "%s", "CURRENT CONFIGURATION");

    for (i = 0; i < partGroup->numParts; i++) {
        al_draw_textf(LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), WIN_WIDTH / 5 * 3.2, WIN_HEIGHT / 5 * 3 + 40 + margin, 0, "%s%s%s", partGroup->parts[i].name, ": ", partGroup->parts[i].type[partGroup->parts[i].selected].name);
        margin += 20;
    }
}

void printGP (int darkMode, Circuit gp) {

    printText (FONT_TITLE, darkMode, WIN_WIDTH / 5, WIN_HEIGHT / 5, "WELCOME TO THE %s", gp.name);

    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH / 4), WIN_HEIGHT / 9 * 3, 0, "%s%d", "SPEED: ", gp.speed);
    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH / 4), WIN_HEIGHT / 9 * 3 + 40, 0, "%s%d", "ACCELERATION: ", gp.acceleration);
    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH / 4), WIN_HEIGHT / 9 * 3 + 80, 0, "%s%d", "CONSUMPTION: ", gp.consumption);
    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH / 4), WIN_HEIGHT / 9 * 3 + 120, 0, "%s%d", "RELIABILITY: ", gp.reliability);

    printText (FONT_TITLE, darkMode, WIN_WIDTH / 5, (WIN_HEIGHT / 4) * 3, "%s", "PRESS R TO START THE RACE");

    //'Painting' the graphic screen.
    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
}

void printTrafficLights(int darkMode, int on[5]) {

    int i, j, x;

    for (j = 0; j < 5; j++) {
        x = WIN_WIDTH * (7 + 4 * j) /30;

        al_draw_filled_rectangle((x - WIN_WIDTH/18), WIN_HEIGHT / 5, (x + WIN_WIDTH/18),
                                 (WIN_HEIGHT / 5) * 4, LS_allegro_get_color(darkMode));
        //drawing balls
        for (i = 2; i < 4; i++) {
            al_draw_filled_circle(x, ((WIN_HEIGHT / 9)*i + (WIN_HEIGHT / 40)*i) + WIN_HEIGHT/34, WIN_HEIGHT / 18,
                                  LS_allegro_get_color(LIGHT_GRAY));
        }
        if (on[j]) {
            for (i = 4; i < 6; i++) {
                al_draw_filled_circle(x, ((WIN_HEIGHT / 9)*i + (WIN_HEIGHT / 40)*i) + WIN_HEIGHT/34, WIN_HEIGHT / 18,
                                      LS_allegro_get_color(RED));
            }
        }
        else {
            for (i = 4; i < 6; i++) {
                al_draw_filled_circle(x, ((WIN_HEIGHT / 9) * i + (WIN_HEIGHT / 40) * i) + WIN_HEIGHT / 34,
                                      WIN_HEIGHT / 18,
                                      LS_allegro_get_color(LIGHT_GRAY));
            }
        }
    }

    //'Painting' the graphic screen.
    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));

}

void printRace (int darkMode, Driver * driver, Car * car, Pilot * pilots, int pilotQty, float timeElapsed, float pstopRemainingTime, int pstopCounter, int pstopNeeded, int pstopStatus, int * carPos, ALLEGRO_BITMAP * carImage) {

    //Main part---------------------------------------------------------------------------------------------------------
    al_draw_filled_rectangle( 0, 0, (WIN_WIDTH*3)/4, (WIN_HEIGHT*9)/10, LS_allegro_get_color(darkMode));

    int i, raceMargin = ((WIN_HEIGHT*9)/10)/(pilotQty+2);
    //Drawing race lines
    al_draw_line(WIN_WIDTH*3/30, raceMargin, (WIN_WIDTH*14)/20, raceMargin, LS_allegro_get_color(getBackgroundColor(&darkMode)), WIN_HEIGHT/90);
    for (i = 0; i < pilotQty; i++) {
        al_draw_line(WIN_WIDTH*3/30, raceMargin*(i+2), (WIN_WIDTH*14)/20, raceMargin*(i+2), LS_allegro_get_color(getBackgroundColor(&darkMode)), WIN_HEIGHT/120);
    }
    //Drawing race cars
    const int carSW = al_get_bitmap_width(carImage), carSH = al_get_bitmap_height(carImage);
    al_draw_scaled_bitmap(carImage, 0, 0, carSW, carSH, WIN_WIDTH*3/30 - (carSW/(WIN_HEIGHT/320))/2  + carPos[pilotQty], raceMargin - (carSH/(WIN_HEIGHT/320))/2, carSW/(WIN_HEIGHT/320), carSH/(WIN_HEIGHT/320), 0);
    for (i = 0; i < pilotQty; i++) {
        al_draw_scaled_bitmap(carImage, 0, 0, carSW, carSH, WIN_WIDTH*3/30 - (carSW/(WIN_HEIGHT/320))/2  + carPos[i], raceMargin*(i+2) - (carSH/(WIN_HEIGHT/320))/2, carSW/(WIN_HEIGHT/320), carSH/(WIN_HEIGHT/320), 0);
    }
    //Drawing driver numbers
    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(getBackgroundColor(&darkMode)), WIN_WIDTH/30 - WIN_WIDTH/50, raceMargin - WIN_HEIGHT/50, 0, "%02d", driver->number);
    for (i = 0; i < pilotQty; i++) {
        al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(getBackgroundColor(&darkMode)), WIN_WIDTH/30 - WIN_WIDTH/50, raceMargin*(i+2) - WIN_HEIGHT/50, 0, "%02d", pilots[i].number);
    }

    //Right part--------------------------------------------------------------------------------------------------------
    printText(FONT_TITLE, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*1)/60, (WIN_HEIGHT*4)/100, "%s", "PILOT");
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*10)/100, "%s", "NAME");
    printText(NORMAL, YELLOW, (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*14)/100, "%s", driver->driverName);
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*18)/100, "%s", "TEAM");
    printText(NORMAL, YELLOW, (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*22)/100, "%s", driver->teamName);
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*26)/100, "%s", "NUMBER");
    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(YELLOW), (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*30)/100, 0, "%d", driver->number);

    printText(FONT_TITLE, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*1)/60, (WIN_HEIGHT*36)/100, "%s", "CAR");
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*42)/100, "%s", "SPEED");
    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(YELLOW), (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*46)/100, 0, "%d", car->speed);
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*50)/100, "%s", "ACCELERATION");
    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(YELLOW), (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*54)/100, 0, "%d", car->acceleration);
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*58)/100, "%s", "CONSUMPTION");
    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(YELLOW), (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*62)/100, 0, "%d", car->consumption);
    printText(NORMAL, darkMode, (WIN_WIDTH*3)/4 + (WIN_WIDTH*2)/60, (WIN_HEIGHT*66)/100, "%s", "RELIABILITY");
    al_draw_textf(LS_allegro_get_font(NORMAL), LS_allegro_get_color(YELLOW), (WIN_WIDTH*3)/4 + (WIN_WIDTH*3)/60, (WIN_HEIGHT*70)/100, 0, "%d", car->reliability);

    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH*3)/4 + (WIN_WIDTH*8)/60, (WIN_HEIGHT*78)/100, 0, "%02d", (int)timeElapsed);
    if (PS_NOTACCEPTED == pstopStatus || PS_ACCEPTED == pstopStatus) {
        printText(NORMAL, darkMode, (WIN_WIDTH * 3) / 4 + (WIN_WIDTH * 1) / 60, (WIN_HEIGHT * 84) / 100, "%s","PIT STOP: ");
        al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode),(WIN_WIDTH * 3) / 4 + (WIN_WIDTH * 8) / 60, (WIN_HEIGHT * 84) / 100, 0, "%02d",(int) (pstopRemainingTime + 0.4));
    }

    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH*3)/4 + (WIN_WIDTH*1)/60, (WIN_HEIGHT*90)/100, 0, "%s%d%s%d", "STOPS: ", pstopCounter, "/", pstopNeeded);

    //Bottom part-------------------------------------------------------------------------------------------------------
    al_draw_line((WIN_WIDTH*3)/4, 0, (WIN_WIDTH*3)/4, WIN_HEIGHT, LS_allegro_get_color(LIGHT_GRAY), WIN_WIDTH/150);
    al_draw_line(0, (WIN_HEIGHT*9)/10, (WIN_WIDTH*3)/4, (WIN_HEIGHT*9)/10, LS_allegro_get_color(LIGHT_GRAY), WIN_WIDTH/150);

    printText(NORMAL, darkMode, WIN_WIDTH/30, (WIN_HEIGHT*94)/100, "%s", "RADIO (R)");
    printText(NORMAL, darkMode, (WIN_WIDTH*12)/20, (WIN_HEIGHT*94)/100, "%s", "PIT STOP (P)");


    //'Painting' the graphic screen.
    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
}

void printFinish (int darkMode, Driver * driver, int pilotQty, SortedLD * list) {

    int i;
    SortedL_goToHead(list);
    for (i = 0; i <= pilotQty && !(0 == strcmp(SortedL_get(list).name, driver->driverName)); i++) {
        SortedL_next(list);
    }

    al_draw_textf(LS_allegro_get_font(FONT_TITLE), LS_allegro_get_color(darkMode), (WIN_WIDTH / 4), WIN_HEIGHT / 4, 0, "%s%s%d", driver->driverName, " HAS ENDED IN POSITION ", i+1);
    printText(FONT_TITLE, darkMode, WIN_WIDTH / 4, WIN_HEIGHT*3 / 4, "%s", "PRESS ENTER TO GO TO MENU");

    //'Painting' the graphic screen.
    LS_allegro_clear_and_paint(getBackgroundColor(&darkMode));
}

int switchDarkMode (int * mode) {
    if (WHITE == *mode) {
        *mode = BLACK;
    }
    else {
        *mode = WHITE;
    }

    return *mode;
}

int getBackgroundColor (int * mode) {
    int backgroundColor = *mode;
    return switchDarkMode(&backgroundColor);
}