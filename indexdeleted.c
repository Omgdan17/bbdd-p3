#include "indexdeleted.h"

/**
 * Index type definition: an structure for a deleted register.
 */
struct _IndexDeleted
{
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};

/**
 * indexdeleted_init allocates memory for a new indexdeleted strcuture
*/
IndexDeleted *indexdeleted_init()
{
    IndexDeleted *id = NULL;

    id = malloc(sizeof(IndexDeleted));
    if (!id)
        return NULL;

    id->offset = 0;
    id->size = 0;

    return id;
}

/**
 * index_free frees the memory allocated for an indexdeleted structure
*/
void indexdeleted_free(void *id)
{
    free(id);
}

/**
 * indexdeleted_getOffset gets the offset value of an indexdeleted
*/
long indexdeleted_getOffset(const IndexDeleted *id)
{
    if (!id)
        return NO_ID;

    return id->offset;
}

/**
 * indexdeleted_getSize gets the size value of an indexdeleted
*/
size_t indexdeleted_getSize(const IndexDeleted *id)
{
    if (!id)
        return NO_ID;

    return id->size;
}

/**
 * indexdeleted_setOffset modifies the offset value of an indexdeleted
*/
Status indexdeleted_setOffset(IndexDeleted *id, const long offset)
{
    if (!id || offset < 0)
        return ERROR;

    id->offset = offset;

    return OK;
}

/**
 * indexdeleted_setSize modifies the size value of an indexdeleted
*/
Status indexdeleted_setSize(IndexDeleted *id, const size_t size)
{
    if (!id || size < 0)
        return ERROR;

    id->size = size;

    return OK;
}

/**
 * indexdeleted_cmp compares two indexdeleted structures
*/
int indexdeleted_cmp(const void *id1, const void *id2)
{
    if (!id1 || !id2)
        return 0;

    if (indexdeleted_getSize(id1) - indexdeleted_getSize(id2) == 0)
        return indexdeleted_getOffset(id1) - indexdeleted_getOffset(id2);

    return indexdeleted_getSize(id1) - indexdeleted_getSize(id2);
}

/**
 * indexdeleted_copy llocates memory for an indexdeleted and copies the data
 * a source one
*/
IndexDeleted *indexdeleted_copy(const IndexDeleted *src)
{
    IndexDeleted *id = NULL;

    if (!src || src->offset < 0 || src->size < 0)
        return NULL;

    if (!(id = indexdeleted_init()))
        return NULL;

    id->offset = src->offset;
    id->size = src->size;

    return id;
}

/**
 * indexdeleted_print prints the data of an indexdeleted
*/
int indexdeleted_print(FILE *pf, const void *id)
{
    int count = 0;

    if (!pf || !id)
        return -1;

    count += fprintf(pf, "    offset: #%ld\n", indexdeleted_getOffset(id));
    count += fprintf(pf, "    size: #%ld\n", indexdeleted_getSize(id));

    return count;
}

/**
 * index_load loads the data of a file in an indexdeleted structure
*/
IndexDeleted *indexdeleted_load(FILE *pf)
{
    IndexDeleted *id = NULL;
    long offset;
    size_t size;

    if (!pf)
        return NULL;

    while (fread(&offset, sizeof(long), 1, pf) != 0 && fread(&size, sizeof(size_t), 1, pf) != 0)
    {
        id = indexdeleted_init();
        if (!id)
            return NULL;
        indexdeleted_setOffset(id, offset);
        indexdeleted_setSize(id, size);
    }

    return id;
}

/**
 * indexdeleted_save saves the data of an indexdeleted structure in a file
*/
int indexdeleted_save(const void *id, FILE *pf)
{
    int count = 0, aux;
    long offset;
    size_t size;

    if (!id || !pf)
        return -1;

    offset = indexdeleted_getOffset(id);
    size = indexdeleted_getSize(id);

    aux = fwrite(&(offset), sizeof(long), 1, pf);
    if (aux == -1)
        return -1;

    count += aux;

    aux = fwrite(&(size), sizeof(size_t), 1, pf);
    if (aux == -1)
        return -1;

    count += aux;

    return count;
}