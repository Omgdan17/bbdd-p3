#ifndef INDEXBOOK_H
#define INDEXBOOK_H

#include "types.h"

/**
 * Index type definition: an structure for a register.
 */
typedef struct _IndexBook IndexBook;

/**
 * @brief Function that allocates memory for a new indexbook strcuture.
 * 
 * @return a pointer to the indexbook structure or NULL in case of ERROR.
*/
IndexBook *indexbook_init();

/**
 * @brief Function that frees the memory allocated for an indexbook structure.
 *
 * @param ib a pointer to an indexbook.
 * 
 * @return no return.
 */
void indexbook_free(void *ib);

/**
 * @brief Function that gets the key value of an indexbook.
 * 
 * @param ib a pointer to an indexbook.
 * 
 * @return the key value of the indexbook or -1 in case of error.
*/
int indexbook_getKey(const IndexBook *ib);

/**
 * @brief Function that gets the offset value of an indexbook.
 * 
 * @param ib a pointer to an indexbook.
 * 
 * @return the offset value of the indexbook or -1 in case of error.
*/
long indexbook_getOffset(const IndexBook *ib);

/**
 * @brief Function that gets the size value of an indexbook.
 * 
 * @param ib a pointer to an indexbook.
 * 
 * @return the size value of the indexbook or -1 in case of error.
*/
size_t indexbook_getSize(const IndexBook *ib);

/**
 * @brief Function that modifies the key value of an indexbook.
 * 
 * @param ib a pointer to the indexbook.
 * @param id the key value of the indexbook.
 * 
 * @return OK if everything goes well, ERROR if not.
*/
Status indexbook_setKey(IndexBook *ib, const int id);

/**
 * @brief Function that modifies the offset value of an indexbook.
 * 
 * @param ib a pointer to the indexbook.
 * @param offset the offset value of the indexbook.
 * 
 * @return OK if everything goes well, ERROR if not.
*/
Status indexbook_setOffset(IndexBook *ib, const long offset);

/**
 * @brief Function that modifies the size value of an indexbook.
 * 
 * @param ib a pointer to the indexbook.
 * @param size the size value of the indexbook.
 * 
 * @return OK if everything goes well, ERROR if not.
*/
Status indexbook_setSize(IndexBook *ib, const size_t size);

/**
 * @brief Function that compares two indexbook structures.
 * 
 * @param ib1 a pointer to an indexbook.
 * @param ib2 a pointer to an indexbook.
 * 
 * @return 0 if both indexbooks are equal (they have the same key),
 * a negative value if the ib1 key is smallest than the ib2 or a positive
 * value otherwise.
*/
int indexbook_cmp(const void *ib1, const void *ib2);

/**
 * @brief Function that allocates memory for an indexbook and copies the data of
 * a source one.
 * 
 * @param src a pointer to an indexbook.
 * 
 * @return a pointer to an indexbook or NULL in case of error.
*/
IndexBook *indexbook_copy(const IndexBook *src);

/**
 * @brief Function that prints the data of an indexbook.
 * 
 * @param pf a pointer to a file.
 * @param ib a pointer to an indexbook.
 * 
 * @return the number of characters printed or -1 in case of error.
*/
int indexbook_print(FILE *pf, const void *ib);

/**
 * @brief Function that loads the data of a file in an indexbook structure.
 * 
 * @param pf a pointer to a file.
 *
 * @return a pointer to an indexbook or NULL in case of error.
*/
IndexBook *indexbook_load(FILE *pf);

/**
 * @brief Functions that saves the data of an indexbook structure in a file.
 * 
 * @param ib a pointer to an indexbook.
 * @param pf a pointer to a file.
 * 
 * @return the number of characters printed in the file or -1 in case of error.
*/
int indexbook_save(const void *ib, FILE *pf);

/**
 * P_ele_size type definition: pointer to a function that takes the size of an element.
 * It returns the size of the element.
 */
typedef size_t (*P_ele_size)(const IndexBook *);

/**
 * P_ele_key type definition: pointer to a function that takes the key of an structure.
 * It returns the key value of the element.
 */
typedef int (*P_ele_key)(const IndexBook *);

#endif