#include "delete.h"

/**
 * delete deletes an element from an index
*/
Status delete(Index *index, Index *lst, int key)
{
    IndexBook *aux = NULL, *ib = NULL;
    IndexDeleted *id = NULL;

    aux = indexbook_init();
    if (!aux)
        return ERROR;

    indexbook_setKey(aux, key);

    if (index_contains(index, aux) == FALSE)
    {
        indexbook_free(aux);
        return ERROR;
    }

    ib = index_find(index, aux);

    indexbook_free(aux);

    id = indexdeleted_init();
    if (!id)
        return ERROR;

    indexdeleted_setOffset(id, indexbook_getOffset(ib));
    indexdeleted_setSize(id, indexbook_getSize(ib));

    index_insert(lst, id);

    index_remove(index, ib);

    return OK;
}