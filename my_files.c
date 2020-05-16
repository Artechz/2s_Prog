/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_files.h"

int readParts (GroupPart * partGroup, char * fileName) {

    FILE * partFile = fopen(fileName, "r");
    char aux;
    int i, j, error = FILE_NO_ERROR;

    if (NULL == partFile) {
        printf("Failed to open parts file.\n");     //TODO remove
        error = FILE_ERROR;          //TODO fer que serveixi fent return de error idk - convert func to int.
    }
    else {
        partGroup = (GroupPart *) malloc(sizeof(GroupPart));

        fscanf(partFile, "%d%c", &(partGroup->numParts), &aux);
        if (aux != '\n') {printf("Failed to read aux.\n");}      //DEBUG

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
        fclose(partFile);
    }
    return error;
}

int readSeason (SortedList * season, char * fileName) {
    printf("x");
    FILE * seasonFile = fopen(fileName, "r");

    char aux;
    int error = FILE_NO_ERROR, i, numCircuits;
    printf("r");
    if (NULL == seasonFile) {
        printf("Failed to open season file.\n");    //TODO remove
        error = FILE_ERROR;
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
            temp.completed = 0;

            SORTEDLIST_sortedAdd(season, temp);
            printf("\niteraFIN_%d - %d - %s", i, temp.place, temp.name);
        }
        error = 0;
        fclose(seasonFile);
    }

    return error;
}

int readPilots (Pilot * pilots, char * fileName, int * pilotQty) {

    FILE * pilotsFile;
    char aux;
    char * buffer;
    int i, j, error = FILE_NO_ERROR;

    if (FILE_ERROR == (error = checkFile(&pilotsFile, fileName, "rb"))) {
        printf("Failed to open pilots file.\n"); //TODO remove
    }
    else {
        fseek(pilotsFile, 0, SEEK_SET);
        for (*pilotQty = 0; !(feof(pilotsFile)); (*pilotQty)++) {
            //fseek(pilotsFile, -sizeof(Pilot), SEEK_CUR);
            //Reallocating memory for the newfound pilot to 'fit' in the dynamic array before putting it in.
            pilots = (Pilot *) realloc(pilots, sizeof(Pilot) * (*pilotQty+1));
            fread(&pilots[*pilotQty], sizeof(Pilot), 1, pilotsFile);  //pilotQty is amount of Pilots so we use (*pilotQty -1) when using it for array index.
            fseek(pilotsFile, sizeof(Pilot), SEEK_CUR);
            printf("%ld - ", ftell(pilotsFile));
        }

        if (pilots[*pilotQty].teamName == "\0") printf("it is");
        printf("\nReached end of %s, read %d pilots.", fileName, *pilotQty);

        for (i = 0; i < *pilotQty; i++) {
            printf("\n!%s! - ", pilots[i].name);
            printf("%d - ", pilots[i].number);
            printf("%s - ", pilots[i].teamName);
            printf("%d - ", pilots[i].speed);
            printf("%d - ", pilots[i].acceleration);
            printf("%d - ", pilots[i].consumption);
            printf("%d - ", pilots[i].reliability);
            printf("%d - ", pilots[i].reflexes);
            printf("%d - ", pilots[i].physicalCondition);
            printf("%d - ", pilots[i].temperament);
            printf("%d - ", pilots[i].tireManagement);
        }
    }
    fclose(pilotsFile);
    return error;
}

int readBase (int stats[4], char * fileName) {

    FILE * baseFile;
    char aux;
    char * buffer;
    int i, j, error = FILE_NO_ERROR;

    if (FILE_ERROR == (error = checkFile(&baseFile, fileName, "rb"))) {
        printf("Failed to open pilots file.\n"); //TODO remove
    }
    else {
        fread(stats, sizeof(int), 4, baseFile);
        printf("\n%d ^ %d ^ %d ^ %d", stats[0], stats[1], stats[2], stats[3]);
    }
    fclose(baseFile);
    return error;
}

int fileErrorManage (int fileError) {
    switch (fileError) {
        case FILE_ERROR:
            printf("\nError. An error ocurred while processing the files.");
            return 1;
            break;
        case FILE_EMPTY:
            printf("\nError. One or more files are empty.");
            return 1;
            break;
        case FILE_NO_ERROR:
            return 0;
            break;
        default:
            printf("\nSOMETHING IS FUCKED");    //TODO remove
            return 1;
            break;
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