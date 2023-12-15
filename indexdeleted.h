#ifndef INDEXDELETED_H
#define INDEXDELETED_H

#include "types.h"

/**
 * Index type definition: an structure for a deleted register.
 */
typedef struct _IndexDeleted IndexDeleted;

/**
 * @brief Function that allocates memory for a new indexdeleted strcuture.
 * 
 * @return a pointer to the indexdeleted structure or NULL in case of ERROR.
*/
IndexDeleted *indexdeleted_init();

/**
 * @brief Function that frees the memory allocated for an indexdeleted structure.
 *
 * @param id a pointer to an indexdeleted.
 * 
 * @return no return.
 */
void indexdeleted_free(void *id);

/**
 * @brief Function that gets the offset value of an indexdeleted.
 * 
 * @param id a pointer to an indexdeleted.
 * 
 * @return the offset value of the indexdeleted or -1 in case of error.
*/
long indexdeleted_getOffset(const IndexDeleted *id);

/**
 * @brief Function that gets the size value of an indexdeleted.
 * 
 * @param id a pointer to an indexdeleted.
 * 
 * @return the size value of the indexdeleted or -1 in case of error.
*/
size_t indexdeleted_getSize(const IndexDeleted *id);

/**
 * @brief Function that modifies the offset value of an indexdeleted.
 * 
 * @param id a pointer to the indexdeleted.
 * @param offset the offset value of the indexdeleted.
 * 
 * @return OK if everything goes well, ERROR if not.
*/
Status indexdeleted_setOffset(IndexDeleted *id, const long offset);

/**
 * @brief Function that modifies the size value of an indexdeleted.
 * 
 * @param id a pointer to the indexdeleted.
 * @param size the size value of the indexdeleted.
 * 
 * @return OK if everything goes well, ERROR if not.
*/
Status indexdeleted_setSize(IndexDeleted *id, const size_t size);

/**
 * @brief Function that compares two indexdeleted structures.
 * 
 * @param id1 a pointer to an indexdeleted.
 * @param id2 a pointer to an indexdeleted.
 * 
 * @return 0 if both indexdeleteds are equal (they have the same key),
 * a negative value if the id1 key is smallest than the id2 or a positive
 * value otherwise.
*/
int indexdeleted_cmp(const void *id1, const void *id2);

/**
 * @brief Function that allocates memory for an indexdeleted and copies the data of
 * a source one.
 * 
 * @param src a pointer to an indexdeleted.
 * 
 * @return a pointer to an indexdeleted or NULL in case of error.
*/
IndexDeleted *indexdeleted_copy(const IndexDeleted *src);

/**
 * @brief Function that prints the data of an indexdeleted.
 * 
 * @param pf a pointer to a file.
 * @param id a pointer to an indexdeleted.
 * 
 * @return the number of characters printed or -1 in case of error.
*/
int indexdeleted_print(FILE *pf, const void *id);

/**
 * @brief Function that loads the data of a file in an indexdeleted structure.
 * 
 * @param pf a pointer to a file.
 *
 * @return a pointer to an indexdeleted or NULL in case of error.
*/
IndexDeleted *indexdeleted_load(FILE *pf);

/**
 * @brief Functions that saves the data of an indexdeleted structure in a file.
 * 
 * @param id a pointer to an indexdeleted.
 * @param pf a pointer to a file.
 * 
 * @return the number of characters printed in the file or -1 in case of error.
*/
int indexdeleted_save(const void *id, FILE *pf);

#endif