/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 09/05/2020
 *
***********************************************/

#ifndef PROGPRACTICE2_MY_ALLEGRO_UI_H
#define PROGPRACTICE2_MY_ALLEGRO_UI_H

#include "LS_allegro.h"
#include "my_race_basic.h"

#define WIN_TITLE_CONFIGURATOR "LS Racing - Configurator"
#define WIN_TITLE_RACE "LS Racing - Race"
#define WIN_WIDTH 1000
#define WIN_HEIGHT 600
#define FONT_TITLE LARGE

/***********************************************
 *
 * @Purpose         Substitute for al_draw_textf with less inputs and same practical
 *                  functionality for the scope of this project.
 * @Parameters      in: size = size of the text to display.
 *                  in: color = color of the text to display.
 *                  in: xpos = position of the text in the x axis.
 *                  in: ypos = position of the text in the y axis.
 *                  in: input = dynamic 'String', format of the text to display.
 *                  in: content = dynamic 'String', the text to display.
 * @Return          ---
 *
************************************************/
void printText (int size, int color, int xpos, int ypos, char * input, char * content);

/***********************************************
 *
 * @Purpose:        Prints the first option screen (car parts configuration).
 * @Parameters:     in: background = bitmap for the background image.
 *                  in: darkMode = true (!0) to show dark mode, false (0) otherwise.
 *                  in: parts[6] = bitmap array for the parts images.
 *                  in: partCategory = part the user has selected.
 *                  in: partModel = model of part the user has selected.
 *                  in: partGroup = struct with all the part data (needed to show).
 * @Return:         ---
 *
************************************************/
void printConfig (ALLEGRO_BITMAP * background, int darkMode, ALLEGRO_BITMAP * parts[6], int partCategory, int partModel, GroupPart * partGroup);

/***********************************************
 *
 * @Purpose:        Prints the second option screen (gp info).
 * @Parameters:     in: darkMode = true (!0) to show dark mode, false (0) otherwise.
 *                  in: gp = struct with all the circuit data.
 * @Return:         ---
 *
************************************************/
void printGP (int darkMode, Circuit gp);

/***********************************************TODO
 *
 * @Purpose:        Prints the traffic lights screen (second option screen).
 * @Parameters:     in: darkMode = true (!0) to show dark mode, false (0) otherwise.
 * @Return:         ---
 *
************************************************/
void printTrafficLights (int darkMode, int on[5]);

/***********************************************TODO
 *
 * @Purpose: Asks the user a question, checks the answers for errors within a valid
 *           range of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return: Returns the atoi of the input if answer is valid.
 *
************************************************/
int switchDarkMode (int * mode);

/***********************************************TODO
 *
 * @Purpose: Asks the user a question, checks the answers for errors within a valid
 *           range of numbers and converts it to an int.
 * @Parameters:     in: question = text to print as a question.
 *                  in: min = minimum value for valid input range.
 *                  in: max = maximum value for valid input range.
 * @Return: Returns the atoi of the input if answer is valid.
 *
************************************************/
int getBackgroundColor (int * mode);

#endif //PROGPRACTICE2_MY_ALLEGRO_UI_H
