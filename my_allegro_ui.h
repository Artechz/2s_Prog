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
void printText (int size, int color, int xpos, int ypos, char * input, char * content);

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
void printConfig (ALLEGRO_BITMAP * background, int darkMode, ALLEGRO_BITMAP * parts[6], int partCategory, int partModel, GroupPart * partGroup);

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
void printGP (int darkMode, Circuit gp);

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
