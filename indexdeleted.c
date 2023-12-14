#include "indexdeleted.h"

struct _IndexDeleted {
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};

IndexDeleted *indexdeleted_init (){
    IndexDeleted *id = NULL;

    id = malloc(sizeof(IndexDeleted));
    if (!id) return NULL;

    id->offset = 0;
    id->size = 0;

    return id;
}

void indexdeleted_free (void *id){
    free(id);
}

long indexdeleted_getOffset (const IndexDeleted *id){
    if (!id) return NO_ID;

    return id->offset;
}

size_t indexdeleted_getSize (const IndexDeleted *id){
    if (!id) return NO_ID;

    return id->size;
}

Status indexdeleted_setOffset (IndexDeleted *id, const long offset){
    if (!id || offset < 0) return ERROR;

    id->offset = offset;

    return OK;
}

Status indexdeleted_setSize (IndexDeleted *id, const size_t size){
    if (!id || size < 0) return ERROR;

    id->size = size + sizeof(id->offset);

    return OK;
}

int indexdeleted_cmp (const void *id1, const void *id2){
    if (!id1 || !id2) return 0;

    if (indexdeleted_getSize(id1) - indexdeleted_getSize(id2) == 0)
        return indexdeleted_getOffset(id1) - indexdeleted_getOffset(id2);  

    return indexdeleted_getSize(id1) - indexdeleted_getSize(id2);
}

IndexDeleted *indexdeleted_copy (const IndexDeleted *src){
    IndexDeleted *id = NULL;

    if (!src || src->offset < 0 || src->size < 0) return NULL;

    if (!(id = indexdeleted_init())) return NULL;

    id->offset = src->offset;
    id->size = src->size;

    return id;
}

int indexdeleted_print (FILE *pf, const void *id){
    int count = 0;
    
    if (!pf || !id) return -1;

    count += fprintf(pf, "    offset: #%ld\n", indexdeleted_getOffset(id));
    count += fprintf(pf, "    size: #%ld\n", indexdeleted_getSize(id));

    return count;
}

IndexDeleted *indexdeleted_load(FILE *f){
    IndexDeleted *id = NULL;
    long offset;
    size_t size;

    if (!f) return NULL;

    while (fread(&offset, sizeof(long), 1, f) != 0 && fread(&size, sizeof(size_t), 1, f) != 0){
        id = indexdeleted_init();
            if (!id) return NULL;
        indexdeleted_setOffset(id, offset);
        indexdeleted_setSize(id, size - 8);
    }

    return id;
}

int indexdeleted_save(const IndexDeleted *id, FILE *pf){
    int count = 0, aux;

    if (!id || !pf) return -1;

    aux = fwrite(&(id->offset), sizeof(long), 1, pf);
    if (aux == -1) return -1;

    count += aux;

    aux = fwrite(&(id->size), sizeof(size_t), 1, pf);
    if (aux == -1) return -1;

    count += aux;

    return count;
}