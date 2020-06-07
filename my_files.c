/***********************************************
 *
 * @Purpose: This module is responsible of the reading and checking of the different files provided.
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_files.h"

int readParts (GroupPart * partGroup, char * fileName) {

    FILE * partFile;
    char aux;
    int i, j, error = FILE_NO_ERROR;

    if (FILE_ERROR == (error = checkFile(&partFile, fileName, "r"))) {
        printf("Failed to open parts file.\n");     //TODO remove
    }
    else {

        fscanf(partFile, "%d%c", &(partGroup->numParts), &aux);

        partGroup->parts = (Part *) malloc(sizeof(Part) * partGroup->numParts);

        for ( i = 0; i < partGroup->numParts; i++) {
            fgets(partGroup->parts[i].name, MAXSTRING, partFile);
            partGroup->parts[i].name[strlen(partGroup->parts[i].name)-1] = '\0';

            fscanf(partFile, "%d%c", &(partGroup->parts[i].numParts), &aux);
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
    }
    fclose(partFile);
    return error;
}

int readSeason (SortedListC * season, char * fileName) {

    FILE * seasonFile;
    char aux;
    int error = FILE_NO_ERROR, i, numCircuits;

    if (FILE_ERROR == (error = checkFile(&seasonFile, fileName, "r"))) {
        printf("Failed to open season file.\n");    //TODO remove
    }
    else {

        //printf("\\%d/", SORTEDLIST_getErrorCode(*season));    //TODO remove
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
            temp.completed = 0;
            temp.baseTime = temp.baseTime*60; //going from minutes to seconds
            SORTEDLIST_sortedAdd(season, temp);
            //printf("\niteraFIN_%d - %d - %s", i, temp.place, temp.name);      //TODO remove
        }
    }
    fclose(seasonFile);
    return error;
}

int readPilots (Pilot ** pilots, char * fileName, int * pilotQty) {

    FILE * pilotsFile;
    int error = FILE_NO_ERROR;

    if (FILE_ERROR == (error = checkFile(&pilotsFile, fileName, "rb"))) {
        printf("Failed to open pilots file.\n"); //TODO remove
    }
    else {
        //Reading (Pilot)s until end of file.

        //Pilot * temp;
        //temp = (Pilot *) malloc(sizeof(Pilot));

        for (*pilotQty = 0; *pilotQty < 7; (*pilotQty)++) {
            //Reallocating memory for the newly found pilot to 'fit' in the dynamic array before putting it in.
            (*pilots) = (Pilot *) realloc((*pilots), sizeof(Pilot) * (*pilotQty +1)); //pilotQty is index for pilots so we use (*pilotQty +1) when using it for Pilot qty.
            fread(&(*pilots)[*pilotQty], sizeof(Pilot), 1, pilotsFile);
        }
        //*pilotQty -= 1;     //We've seen feof() works in a way we'll do the loop one more time than needed so we hardcoded the 8 following advice from one of the interns.
    }
    fclose(pilotsFile);
    return error;
}

int readBase (int stats[4], char * fileName) {

    FILE * baseFile;
    int error = FILE_NO_ERROR;

    if (FILE_ERROR == (error = checkFile(&baseFile, fileName, "rb"))) {
        printf("Failed to open base file.\n"); //TODO remove
    }
    else {
        fread(stats, sizeof(int), 4, baseFile);
        //printf("\n%d ^ %d ^ %d ^ %d", stats[0], stats[1], stats[2], stats[3]);    //TODO remove
    }
    fclose(baseFile);
    return error;
}

int fileErrorManage (int fileError) {
    switch (fileError) {
        case FILE_ERROR:
            printf("\nError. An error ocurred while processing the files.");
            return 1;
        case FILE_EMPTY:
            printf("\nError. One or more files are empty.");
            return 1;
        case FILE_NO_ERROR:
            return 0;
        default:
            printf("\nSOMETHING IS FUCKED");    //TODO remove
            return 1;
    }
}

int checkFile (FILE ** file, char * path, char * mode) {
    int error = FILE_NO_ERROR;
    if (NULL == (*file = fopen(path, mode))) {
        error = FILE_ERROR;
    }
    else {
        if (feof(*file)) {
            error = FILE_EMPTY;
        }
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