#ifndef DELETE_H
#define DELETE_H

#include "types.h"
#include "index.h"

/**
 * @brief Function that deletes an element from an index
 * 
 * @param index a pointer to an index with the elements
 * @param lst a pointer to an index with the deleted elements
 * @param key the key value of the element to delete
 * 
 * @return OK if everything goes well, ERROR if not
*/
Status delete(Index *index, Index *lst, int key);

#endif