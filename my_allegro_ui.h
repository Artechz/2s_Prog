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
#include "my_driver_sortedlist.h"

#define WIN_TITLE_CONFIGURATOR "LS Racing - Configurator"
#define WIN_TITLE_RACE "LS Racing - Race"

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

/***********************************************
 *
 * @Purpose:        Prints the traffic lights screen (second option screen).
 * @Parameters:     in: darkMode = true (!0) to show dark mode, false (0) otherwise.
 *                  in: on[5] = indicates which traffic lights are on.
 * @Return:        ---
 *
************************************************/
void printTrafficLights (int darkMode, int on[5]);

/***********************************************TODO
 *
 * @Purpose:    Show the user the race.
 * @Parameters: (in/out): player = information about the players car.
 *              (in/out): others = information about the car of the other drivers.
 *              in: pilotQty = number of pilots
 *              in: timeElapsed =
 *              in: pstopRemainingTime =
 *              in: pstopCounter =
 *              in: pstopNeeded =
 *              in: pstopStatus =
 *              (in/out): carPos = Position of the car.
 *              (in/out): carImage = Image of the car.
 * @Return:        ---
 *
************************************************/
void printRace (int darkMode, Driver * driver, Car * car, Pilot * pilots, int pilotQty, float timeElapsed, float pstopRemainingTime, int pstopCounter, int pstopNeeded, int pstopStatus, int * carPos, ALLEGRO_BITMAP * carImage);

/***********************************************
 *
 * @Purpose:    Show the user the post-race menu.
 * @Parameters: in: darkMode = Color of the background
 *              (in/out): driver = Information about the driver
 *              in: pilotQty = number of pilots.
 *              (in/out): list = Sortedlist of the season.
 * @Return:        ---
 *
************************************************/
void printFinish (int darkMode, Driver * driver, int pilotQty, SortedLD * list);


/***********************************************
 *
 * @Purpose:     	Switches the menu to dark mode if is in bright mode or viceversa.
 * @Parameters:     (in/out): mode = integer asociated with the background color.
 * @Return:          Returns the integer asociated with the new background color.
 *
************************************************/
int switchDarkMode (int * mode);

/***********************************************
 *
 * @Purpose:        Gets the background color.
 * @Parameters:     (in/out): mode = integer asociated with the background color.
 * @Return:         Returns the integer asociated with the background color.
 *
************************************************/
int getBackgroundColor (int * mode);

#endif //PROGPRACTICE2_MY_ALLEGRO_UI_H
