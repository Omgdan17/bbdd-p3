#include "indexbook.h"

/**
 * Index type definition: an structure for a register.
 */
struct _IndexBook
{
    int key;     /*Book id*/
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};

/**
 * indexbook_init allocates memory for a new indexbook strcuture
*/
IndexBook *indexbook_init()
{
    IndexBook *ib = NULL;

    ib = malloc(sizeof(IndexBook));
    if (!ib)
        return NULL;

    ib->key = 0;
    ib->offset = 0;
    ib->size = 0;

    return ib;
}

/**
 * index_free frees the memory allocated for an indexbook structure
*/
void indexbook_free(void *ib)
{
    free(ib);
}

/**
 * indexbook_getKey gets the key value of an indexbook
*/
int indexbook_getKey(const IndexBook *ib)
{
    if (!ib)
        return NO_ID;

    return ib->key;
}

/**
 * indexbook_getOffset gets the offset value of an indexbook
*/
long indexbook_getOffset(const IndexBook *ib)
{
    if (!ib)
        return NO_ID;

    return ib->offset;
}

/**
 * indexbook_getSize gets the size value of an indexbook
*/
size_t indexbook_getSize(const IndexBook *ib)
{
    if (!ib)
        return NO_ID;

    return ib->size;
}

/**
 * indexbook_setKey modifies the key value of an indexbook
*/
Status indexbook_setKey(IndexBook *ib, const int id)
{
    if (!ib)
        return ERROR;

    ib->key = id;

    return OK;
}

/**
 * indexbook_setOffset modifies the offset value of an indexbook
*/
Status indexbook_setOffset(IndexBook *ib, const long offset)
{
    if (!ib || offset < 0)
        return ERROR;

    ib->offset = offset;

    return OK;
}

/**
 * indexbook_setSize modifies the size value of an indexbook
*/
Status indexbook_setSize(IndexBook *ib, const size_t size)
{
    if (!ib || size < 0)
        return ERROR;

    ib->size = size;

    return OK;
}

/**
 * indexbook_cmp compares two indexbook structures
*/
int indexbook_cmp(const void *ib1, const void *ib2)
{
    if (!ib1 || !ib2)
        return 0;

    return indexbook_getKey(ib1) - indexbook_getKey(ib2);
}

/**
 * indexbook_copy llocates memory for an indexbook and copies the data
 * a source one
*/
IndexBook *indexbook_copy(const IndexBook *src)
{
    IndexBook *ib = NULL;

    if (!src || src->key < 0 || src->offset < 0 || src->size < 0)
        return NULL;

    if (!(ib = indexbook_init()))
        return NULL;

    ib->key = src->key;
    ib->offset = src->offset;
    ib->size = src->size;

    return ib;
}

/**
 * indexbook_print prints the data of an indexbook
*/
int indexbook_print(FILE *pf, const void *ib)
{
    int count = 0;

    if (!pf || !ib)
        return -1;

    count += fprintf(pf, "    key: #%5d\n", indexbook_getKey(ib));
    count += fprintf(pf, "    offset: #%ld\n", indexbook_getOffset(ib));

    return count;
}

/**
 * index_load loads the data of a file in an indexbook structure
*/
IndexBook *indexbook_load(FILE *pf)
{
    IndexBook *ib = NULL;
    int key;
    long offset;
    size_t size;

    if (!pf)
        return NULL;

    if (fread(&key, sizeof(int), 1, pf) != 0 && fread(&offset, sizeof(long), 1, pf) != 0 && fread(&size, sizeof(size_t), 1, pf) != 0)
    {
        ib = indexbook_init();
        if (!ib)
            return NULL;
        indexbook_setKey(ib, key);
        indexbook_setOffset(ib, offset);
        indexbook_setSize(ib, size);
    }

    return ib;
}

/**
 * indexbook_save saves the data of an indexbook structure in a file
*/
int indexbook_save(const void *ib, FILE *pf)
{
    int count = 0, aux, key;
    long offset;
    size_t size;

    if (!ib || !pf)
        return -1;

    key = indexbook_getKey(ib);
    offset = indexbook_getOffset(ib);
    size = indexbook_getSize(ib);


    aux = fwrite(&(key), sizeof(int), 1, pf);
    if (aux == -1)
        return -1;

    count += aux;

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