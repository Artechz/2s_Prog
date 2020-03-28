/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_race_basic.h"

int menuAsk (char question[MAXSTRING], int min, int max) {

    char input[MAXSTRING];
    int check, i;

    do {
        check = 1;
        printf("%s", question);
        fgets(input, MAXSTRING, stdin);
        if(input[0] == '\n')
            check = 0;
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