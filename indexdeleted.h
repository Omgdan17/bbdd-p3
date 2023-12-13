#ifndef INDEXDELETED_H
#define INDEXDELETED_H

#include "types.h"

/**
 * Index type definition: a binary search of arbitrary elements.
 */
typedef struct _IndexDeleted IndexDeleted;

/**
 * @brief Constructor. Initialize a indexdeleted.
 *
 * @return Return the initialized indexdeleted if it was done correctly, 
 * otherwise return NULL.
*/
IndexDeleted *indexdeleted_init ();


/**
 * @brief Destructor. Free the dynamic memory reserved for a indexdeleted .
 *
 * @param id a pointer to a indexdeleted
 */
void indexdeleted_free (void *id);

/**
 * @brief Gets the indexdeleted offset.
 *
 * @param id a pointer to a indexdeleted
 *
 * @return Returns the Offset of the given indexdeleted, or -1 in case of error.
 */
long indexdeleted_getOffset (const IndexDeleted *id);

/**
 * @brief Gets the indexdeleted size.
 *
 * @param id a pointer to a indexdeleted
 *
 * @return Returns the size of the given indexdeleted, or -1 in case of error.
 */
size_t indexdeleted_getSize (const IndexDeleted *id);

/**
 * @brief Modifies the offset of a given indexdeleted.
 *
 * @param id a pointer to a indexdeleted
 * @param offset the offset of a new indexdeleted
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexdeleted_setOffset (IndexDeleted *id, const long offset);

/**
 * @brief Modifies the size of a given indexdeleted.
 *
 * @param id a pointer to a indexdeleted
 * @param size the size of a new indexdeleted
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexdeleted_setSize (IndexDeleted *id, const size_t size);

/**
 * @brief Compares indexdeleteds.
 * 
 * @param id1 a pointer to a indexdeleted
 * @param id2 a pointer to a indexdeleted
 *
 * @return It returns an integer less than or greater than zero if
 * id of id1 is found,  respectively, to be less than or be greater 
 * than id of id2.
 */
int indexdeleted_cmp (const void *id1, const void *id2);


/**
 * @brief Allocates memory for a indexdeleted where it copies the data from
 * the indexdeleted src.
 * 
 * @param src a pointer to the original indexdeleted
 *
 * @return Returns the pointer of the copied indexdeleted if everything 
 * went well, or NULL otherwise.
 */
IndexDeleted *indexdeleted_copy (const IndexDeleted *src);


/** 
 * @brief Prints in pf the data of a indexdeleted.
 *
 * @param pf a pointer to a file
 * @param id a pointer to a indexdeleted
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int indexdeleted_print (FILE *pf, const void *id);

IndexDeleted *indexdeleted_load(FILE *f);

int indexdeleted_save (const IndexDeleted *id, FILE *pf);

/**
 * P_ele_save type definition: pointer to a function that saves the data of an indexdeleted in a file
*/
/*typedef int (*P_ele_save)(const IndexDeleted*, FILE *f);*/


#endif