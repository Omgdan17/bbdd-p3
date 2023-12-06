#include "indexbook.h"

struct _IndexBook {
    int key; /*Book id*/
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};

IndexBook *indexbook_init (){
    IndexBook *ib = NULL;

    ib = malloc(sizeof(IndexBook));
    if (!ib) return NULL;

    ib->key = 0;
    ib->offset = 0;
    ib->size = 0;

    return ib;
}

void indexbook_free (void *ib){
    free(ib);
}

int indexbook_getId (const IndexBook *ib){
    if (!ib) return NO_ID;

    return ib->key;
}

long indexbook_getOffset (const IndexBook *ib){
    if (!ib) return NO_ID;

    return ib->offset;
}

size_t indexbook_getSize (const IndexBook *ib){
    if (!ib) return NO_ID;

    return ib->size;
}

Status indexbook_setId (IndexBook *ib, const int id){
    if (!ib) return ERROR;

    ib->key = id;

    return OK;
}

Status indexbook_setOffset (IndexBook *ib, const long offset){
    if (!ib || offset < 0) return ERROR;

    ib->offset = offset;

    return OK;
}

Status indexbook_setSize (IndexBook *ib, const size_t size){
    if (!ib || size < 0) return ERROR;

    ib->size = size + sizeof(ib->offset);

    return OK;
}

int indexbook_cmp (const IndexBook *ib1, const IndexBook *ib2){
    if (!ib1 || !ib2) return 0;

    return ib1->key - ib2->key;
}

IndexBook *indexbook_copy (const IndexBook *src){
    IndexBook *ib = NULL;

    if (!src || src->key < 0 || src->offset < 0 || src->size < 0) return NULL;

    if (!(ib = indexbook_init())) return NULL;

    ib->key = src->key;
    ib->offset = src->offset;
    ib->size = src->size;

    return ib;
}

int indexbook_print (FILE *pf, const IndexBook *ib){
    int count = 0;
    
    if (!pf || !ib) return -1;

    count += fprintf(pf, "\t Key: #%5d\n", ib->key);
    count += fprintf(pf, "\t Offset: #%ld\n", ib->offset);
    count += fprintf(pf, "\t Size: #%ld\n", ib->size);

    return count;
}