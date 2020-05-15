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

    //al_draw_textf (LS_allegro_get_font(SMALL), LS_allegro_get_color(darkMode), (WIN_WIDTH / 6) * 5, WIN_HEIGHT / 5 - 20, 0, "%s", partGroup->parts[partCategory].type[partModel].name);
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