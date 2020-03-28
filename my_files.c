/***********************************************
 *
 * @Purpose: //TODO
 * @Author: Arnau Sanz and Josep Segarra.
 * @Creation date: 27/03/2020 (DD/MM/YYYY)
 * @Date of last modification: 28/03/2020
 *
***********************************************/

#include "my_files.h"

int readParts (GroupPart * partGroup) {

    FILE * partFile = fopen(PARTS_FILE, "r");
    char aux;
    int i, j, error = 0;

    if (NULL == partFile) {
        printf("Failed to open parts file.\n");
        error = 1;
    }

    partGroup = (GroupPart *) malloc(sizeof(GroupPart));

    fscanf(partFile, "%d%c", &(partGroup->numParts), &aux);
    if (aux != '\n')
        printf("Failed to read aux.\n");                                                                   //DEBUG

    partGroup->parts = (Part *) malloc(sizeof(Part) * partGroup->numParts);

    for ( i = 0; i < partGroup->numParts; i++) {

        fgets(partGroup->parts[i].name, MAXSTRING, partFile);
        partGroup->parts[i].name[strlen(partGroup->parts[i].name)-1] = '\0';

        fscanf(partFile, "%d%c", &(partGroup->parts[i].numParts), &aux);

        partGroup->parts[i].type = (MiniPart *) malloc(sizeof(MiniPart) * partGroup->parts[i].numParts);

        for ( j = 0; j < partGroup->parts[i].numParts; j++) {

            fgets(partGroup->parts[i].type[j].name, MAXSTRING, partFile);
            partGroup->parts[i].type[j].name[strlen(partGroup->parts[i].type[j].name)-1] = '\0';

            fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].speed), &aux);

            fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].acceleration), &aux);

            fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].consumption), &aux);

            fscanf(partFile, "%d%c", &(partGroup->parts[i].type[j].reliability), &aux);
        }
    }

    return error;

}
