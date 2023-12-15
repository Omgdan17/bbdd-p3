#ifndef INDEX_H
#define INDEX_H

#include "types.h"
#include "indexbook.h"
#include "indexdeleted.h"
/**
 * Index type definition: a binary search of arbitrary elements.
 */
typedef struct _Index Index;

/**
 * @brief Function that allocates memory for a new index structure.
 *
 * @param print_ele a pointer to the function that prints an index element.
 * @param cmp_ele a pointet to the function that compares tow index elements.
 * @param size_ele a pointer to the function that returns the size of an index element.
 * @param free_ele a pointer to the function that frees the memory allocated for an index element.
 * @param save_ele a pointer to the function that saves the data of an index element in a file.
 *
 * @return a pointer to the index structure created or NULL in case of error.
 */
Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele, P_ele_size size_ele, P_ele_free free_ele, P_ele_save save_ele);

/**
 * @brief Function that frees the memory allocated for an index structure.
 *
 * @param index a pointer to an index structure.
 *
 * @return no return
 */
void index_destroy(Index *index);

/**
 * @brief Function that checks if an index estructure is empty.
 *
 * @param index a pointer to an index structure.
 *
 * @return TRUE if the index is empty, FALSE if not.
 */
Bool index_isEmpty(const Index *index);

/**
 * @brief Function that returns the size of an index structure.
 *
 * @param index a pointer to an index structure.
 *
 * @return the index's size or -1 in case of error.
 */
size_t index_size(const Index *index);

/**
 * @brief Function that prints the data of an index strcuture in a file.
 *
 * @param index a pointer to an index structure.
 * @param pf a pointer to a file.
 *
 * @return the number of characters printed or -1 in case of error.
 */
int index_print(const Index *index, FILE *pf);

/**
 * @brief Function that returns the element from an index structure by a given field.
 *
 * This is very useful when the element is a structure with different fields and
 * we use just one field to check if two structures are equal or not (primary key).
 *
 * @param index a pointer to an index structure.
 * @param elem a pointer to the element to find.
 *
 * @return a pointer to the data structure in the element.
 */
void *index_find(const Index *index, const void *elem);

/**
 * @brief Function that returns the minimum element of an index structure (the most lefted element).
 *
 * @param index a pointer to an index structure.
 *
 * @return a pointer to the minimum element.
 */
void *index_find_min(const Index *index);

/**
 * @brief Function that returns the maximum element of an index structure (the most righted element).
 *
 * @param index a pointer to an index structure.
 *
 * @return a pointer to the maximum element.
 */
void *index_find_max(const Index *index);

/**
 * @brief Function that checks if an element is in an index structure.
 *
 * Note that this only checks if there is an element with the same primary key, just checking
 * the strcuture's fields added to the cmp function of the data structure.
 *
 * @param index a pointer to an index structure.
 * @param elem a pointer to the element to find.
 *
 * @return TRUE if the element was found, FALSE if not.
 */
Bool index_contains(const Index *index, const void *elem);

/**
 * @brief Function that inserts a new element in an index structure.
 *
 * @param index a pointer to an index structure.
 * @param elem a pointer to the element to insert.
 *
 * @return OK if everything goes well, ERROR if not.
 */
Status index_insert(Index *index, const void *elem);

/**
 * @brief Function that removes an element form an index structure.
 *
 * @param index a pointer to an index structure.
 * @param elem a pointer to the element to remove.
 *
 * @return OK if everything goes well, ERROR if not.
 */
Status index_remove(Index *index, const void *elem);

/**
 * @brief Function that returns the number of elements of an index structure.
 *
 * @param index a pointer to an index structure.
 *
 * @return the number of elements of the index strcuture, -1 in case of error.
 */
int index_numberOfElements(const Index *index);

/**
 * @brief Function that returns an array with the primary keys in order of all the elements in the index.
 *
 * @param index a pointer to an index structure.
 * @param key_ele a pointer to a function that returns the primary key of an element.
 *
 * @return an array with the primary keys of the index structure.
 */
int *index_keys(const Index *index, P_ele_key key_ele);

/**
 * @brief Function that loads the data of a file in an index structure.
 *
 * @param index a pointer to an index structure.
 * @param pf a pointer to a file.
 * @param type the type of element in the index.
 *
 * @return OK if everything goes well, ERROR if not.
 */
Status index_load(Index *index, FILE *pf, int type);

/**
 * @brief Function that saves the data of an index structure in a file.
 *
 * @param index a pointer to an index structure.
 * @param pf a pointer to a file.
 *
 * @return the number of characters written, -1 in case of error
 */
int index_save(const Index *index, FILE *pf);

/**
 * @brief Function that returns the offset where a new element is going to be stored.
 *
 * It follows the firstfit algorithm, taking the first gap with a bigger size than the element's.
 *
 * @param index a pointer to the index structure.
 * @param size the size of the new element.
 *
 * @return the offset choosen or -1 if there wasn't a gap big enough.
 */
long index_firstfit(Index *index, int size);

/**
 * @brief Function that returns the offset where a new element is going to be stored.
 *
 * It follows the best algorithm, taking the smallest gap with a bigger size than the element's.
 *
 * @param index a pointer to the index structure.
 * @param size the size of the new element.
 *
 * @return the offset choosen or -1 if there wasn't a gap big enough.
 */
long index_bestfit(Index *index, int size);

/**
 * @brief Function that returns the offset where a new element is going to be stored.
 *
 * It follows the worstfit algorithm, taking the gap with the biggest size (if it is bigger than the element's).
 *
 * @param index a pointer to the index structure.
 * @param size the size of the new element.
 *
 * @return the offset choosen or -1 if there wasn't a gap big enough.
 */
long index_worstfit(Index *index, int size);

#endif