#include "find.h"

/**
 * find shows the data of a an element
*/
Status find(Index *index, char *filename, int const key)
{
    IndexBook *aux = NULL, *ib = NULL;
    FILE *db = NULL;
    int i, d = 0;
    char c = 0;

    if (!index || !filename || key < 0)
        return ERROR;

    db = fopen(filename, "rb");
    if (!db)
        return ERROR;

    aux = indexbook_init();

    indexbook_setKey(aux, key);

    if (index_contains(index, aux) == FALSE)
    {
        indexbook_free(aux);
        return ERROR;
    }

    ib = index_find(index, aux);

    fseek(db, indexbook_getOffset(ib), SEEK_SET);

    fread(&d, sizeof(size_t), 1, db);

    fread(&d, sizeof(int), 1, db);
    fprintf(stdout, "%d|", d);

    for (i = 0; i < 16; i++)
    {
        fread(&c, sizeof(char), 1, db);
        fprintf(stdout, "%c", c);
    }
    fprintf(stdout, "|");

    for (; i < indexbook_getSize(ib) - sizeof(int); i++)
    {
        fread(&c, sizeof(char), 1, db);
        fprintf(stdout, "%c", c);
    }

    fprintf(stdout, "\n");

    indexbook_free(aux);

    fclose(db);

    return OK;
}