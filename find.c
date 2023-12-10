#include "find.h"

Status find(Index *index, FILE *db, int const key){
    IndexBook *aux = NULL, *ib = NULL;
    int i, d=0;
    char c=0;

    if (!index || !db || key < 0) return ERROR;

    aux = indexbook_init();

    indexbook_setKey(aux, key);

    if (index_contains(index, aux) == FALSE){
        indexbook_free(aux);
        return ERROR;
    }

    ib = index_find(index, aux);

    for (i=0; i<indexbook_getOffset(ib); i++)
        fread(&d, sizeof(char), 1, db);

    fread(&d, sizeof(size_t), 1, db);

    fread(&d, sizeof(int), 1, db);
    fprintf(stdout, "%d|", d);


    for (i=0; i<16; i++){
        fread(&c, sizeof(char), 1, db);
        fprintf(stdout, "%c", c);
    }
    fprintf(stdout, "|");

    for (; i<indexbook_getSize(ib)-sizeof(size_t)-sizeof(int); i++){
        fread(&c, sizeof(char), 1, db);
        fprintf(stdout, "%c", c);
    }


    fprintf(stdout, "\n");

    indexbook_free(aux);

    return OK;     
}