#include "delete.h"

Status delete(Index *index, Index *lst, int key){
    IndexBook *aux = NULL, *ib = NULL;
    IndexDeleted *id = NULL;

    printf("1\n");
    aux = indexbook_init();
    if (!aux) return ERROR;

    indexbook_setKey(aux, key);
    printf("2\n");
    if (index_contains(index, aux) == FALSE){
        indexbook_free(aux);
        printf("2.5\n");
        return ERROR;
    }

    ib = index_find(index, aux);
    printf("3\n");
    id = indexdeleted_init();
    if (!id){
        indexbook_free(aux);
        return ERROR;
    }
    printf("4\n");
    indexdeleted_setOffset(id, indexbook_getOffset(ib));
    indexdeleted_setSize(id, indexbook_getSize(ib)-8);

    index_insert(lst, id);
    printf("5\n");
    index_remove(index, ib);

    indexbook_free(aux);

    return OK;
}