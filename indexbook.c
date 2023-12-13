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

int indexbook_getKey (const IndexBook *ib){
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

Status indexbook_setKey (IndexBook *ib, const int id){
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

int indexbook_cmp (const void *ib1, const void *ib2){
    if (!ib1 || !ib2) return 0;

    return indexbook_getKey(ib1) - indexbook_getKey(ib2);
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

int indexbook_print (FILE *pf, const void *ib){
    int count = 0;
    
    if (!pf || !ib) return -1;

    count += fprintf(pf, "    key: #%5d\n", indexbook_getKey(ib));
    count += fprintf(pf, "    offset: #%ld\n", indexbook_getOffset(ib));
    /*count += fprintf(pf, "\t Size: #%ld\n", indexbook_getSize(ib));*/

    return count;
}

IndexBook *indexbook_load(FILE *f){
    IndexBook *ib = NULL;
    int key;
    long offset;
    size_t size;

    if (!f) return NULL;

    if (fread(&key, sizeof(int), 1, f) != 0 && fread(&offset, sizeof(long), 1, f) != 0 && fread(&size, sizeof(size_t), 1, f) != 0){
        ib = indexbook_init();
            if (!ib) return NULL;
        indexbook_setKey(ib, key);
        indexbook_setOffset(ib, offset);
        indexbook_setSize(ib, size - 8);
    }

    return ib;
}

int indexbook_save(const IndexBook *ib, FILE *pf){
    int count = 0, aux;

    if (!ib || !pf) return -1;

    aux = fwrite(&(ib->key), sizeof(int), 1, pf);
    if (aux == -1) return -1;

    count += aux;

    aux = fwrite(&(ib->offset), sizeof(long), 1, pf);
    if (aux == -1) return -1;

    count += aux;

    aux = fwrite(&(ib->size), sizeof(size_t), 1, pf);
    if (aux == -1) return -1;

    count += aux;

    return count;
}