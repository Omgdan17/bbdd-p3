#ifndef FIND_H_
#define FIND_H_

#include "types.h"
#include "index.h"

/**
 * @brief Function that shows the data of a an element
 * 
 * @param index a pointer to an index
 * @param filename the name of the file containing the data
 * @param key the key value of the element to show
 * 
 * @return OK if everything goes well, ERROR if not
*/
Status find(Index *index, char *filename, int key);

#endif