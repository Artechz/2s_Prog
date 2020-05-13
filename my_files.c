/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_files.h"

GroupPart * readParts (GroupPart * partGroup) {

    FILE * partFile = fopen(PARTS_FILE, "r");
    char aux;
    int i, j, error = 0;

    if (NULL == partFile) {
        printf("Failed to open parts file.\n");
        error = 1;          //TODO fer que serveixi fent return de error idk - convert func to int.
    }
    else {
        partGroup = (GroupPart *) malloc(sizeof(GroupPart));

        fscanf(partFile, "%d%c", &(partGroup->numParts), &aux);
        if (aux != '\n') {printf("Failed to read aux.\n");}      //DEBUG

        printf("numParts = %d\n", partGroup->numParts);
        partGroup->parts = (Part *) malloc(sizeof(Part) * partGroup->numParts);

        for ( i = 0; i < partGroup->numParts; i++) {

            fgets(partGroup->parts[i].name, MAXSTRING, partFile);
            partGroup->parts[i].name[strlen(partGroup->parts[i].name)-1] = '\0';
            //printf("%s!", partGroup->parts[i].name);

            fscanf(partFile, "%d%c", &(partGroup->parts[i].numParts), &aux);
            //printf("\n!%d%c%d", partGroup->parts[i].numParts, aux, i);
            partGroup->parts[i].type = (MiniPart *) malloc(sizeof(MiniPart) * partGroup->parts[i].numParts);

            partGroup->parts[i].selected = 0;

            for ( j = 0; j < partGroup->parts[i].numParts; j++) {

                fgets(partGroup->parts[i].type[j].name, MAXSTRING, partFile);
                partGroup->parts[i].type[j].name[strlen(partGroup->parts[i].type[j].name)-1] = '\0';

                fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].speed), &aux);

                fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].acceleration), &aux);

                fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].consumption), &aux);

                fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].reliability), &aux);
            }
        }

        fclose(partFile);
    }
    return partGroup;

}

int readSeason (SortedList * season) {
    printf("x");
    FILE * seasonFile = fopen(SEASON_FILE, "r");

    char aux;
    int error = 0, i, numCircuits;
    printf("r");
    if (NULL == seasonFile) {
        printf("Failed to open parts file.\n");
        error = 1;
    }
    else {

        printf("\\%d/", SORTEDLIST_getErrorCode(*season));

        fscanf(seasonFile, "%d%c", &numCircuits, &aux);

        for (i = 0; i < numCircuits; i++) {
            Circuit temp;

            fscanf(seasonFile, "%d%c", &temp.place, &aux);
            fgets(temp.name, MAXSTRING, seasonFile);
            temp.name[strlen(temp.name)-1] = '\0';
            fscanf(seasonFile, "%d%c", &temp.speed, &aux);
            fscanf(seasonFile, "%d%c", &temp.acceleration, &aux);
            fscanf(seasonFile, "%d%c", &temp.consumption, &aux);
            fscanf(seasonFile, "%d%c", &temp.reliability, &aux);
            fscanf(seasonFile, "%f%c", &temp.baseTime, &aux);
            fscanf(seasonFile, "%d%c", &temp.pitstopTime, &aux);
            fscanf(seasonFile, "%d%c", &(temp.pitstopQty), &aux);

            SORTEDLIST_sortedAdd(season, temp);
            printf("\niteraFIN_%d - %d - %s", i, temp.place, temp.name);
            Circuit z = SORTEDLIST_get(season);
            printf("!!%s!!", z.name);
        }
        error = 0;
        fclose(seasonFile);
    }

    return error;
}

/*
 *  quantity -> GPs INT
 *  GP block:
 *      place in season (to sort) INT
 *      name of GP  STRING
 *      appropriate speed INT
 *      appropriate acceleration INT
 *      appropriate consumption INT
 *      appropriate reliability INT
 *      base time FLOAT
 *      pit-stop time INT
 *      quantity pit-stops INT
 */