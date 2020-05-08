/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_allegro_ui.h"


void printConfig (ALLEGRO_BITMAP * background, ALLEGRO_BITMAP * parts[6], int partType, int darkMode) {

    const int background_width = al_get_bitmap_width(background);
    const int background_height = al_get_bitmap_height(background);

    const int part_width = al_get_bitmap_width(parts[0]);
    const int part_height = al_get_bitmap_height(parts[0]);
    const int part_width_scaled = al_get_bitmap_width(parts[0]) / (WIN_WIDTH / 200);
    const int part_height_scaled = al_get_bitmap_height(parts[0]) / (WIN_WIDTH / 200);

    //Scales the boxes image to a size that fits the actual window.
    al_draw_scaled_bitmap (background, 0, 0, background_width, background_height, 0, 0, (WIN_WIDTH/5)*3, WIN_HEIGHT, 0);
    //Scaled the tires image so it's not too big for the arrows to have space.
    al_draw_scaled_bitmap (parts[0], 0, 0, part_width, part_height, WIN_WIDTH / 5 * 3.4, WIN_HEIGHT / 5, part_width_scaled, part_height_scaled, 0);


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

}

void printText (int size, int color, int xpos, int ypos, char * input, char * content) {

    al_draw_textf (LS_allegro_get_font(size), LS_allegro_get_color(color), xpos, ypos,0, input, content);
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