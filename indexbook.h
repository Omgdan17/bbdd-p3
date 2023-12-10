#ifndef INDEXBOOK_H
#define INDEXBOOK_H

#include "types.h"

/**
 * Index type definition: a binary search of arbitrary elements.
 */
typedef struct _IndexBook IndexBook;

/**
 * @brief Constructor. Initialize a indexbook.
 *
 * @return Return the initialized indexbook if it was done correctly, 
 * otherwise return NULL.
*/
IndexBook *indexbook_init ();


/**
 * @brief Destructor. Free the dynamic memory reserved for a indexbook .
 *
 * @param ib a pointer to a indexbook
 */
void indexbook_free (void *ib);


/**
 * @brief  Gets the indexbook id.
 *
 * @param ib a pointer to a indexbook
 *
 * @return  Returns the id of the given indexbook, or -1 in case of error.
 */
int indexbook_getKey (const IndexBook *ib);


/**
 * @brief Gets the indexbook offset.
 *
 * @param ib a pointer to a indexbook
 *
 * @return Returns the Offset of the given indexbook, or -1 in case of error.
 */
long indexbook_getOffset (const IndexBook *ib);

/**
 * @brief Gets the indexbook size.
 *
 * @param ib a pointer to a indexbook
 *
 * @return Returns the size of the given indexbook, or -1 in case of error.
 */
size_t indexbook_getSize (const IndexBook *ib);

/**
 * @brief Modifies the id of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param id the id number of a new indexbook, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setKey (IndexBook *ib, const int id);

/**
 * @brief Modifies the offset of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param offset the offset of a new indexbook
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setOffset (IndexBook *ib, const long offset);

/**
 * @brief Modifies the size of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param size the size of a new indexbook
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setSize (IndexBook *ib, const size_t size);

/**
 * @brief Compares indexbooks.
 * 
 * @param ib1 a pointer to a indexbook
 * @param ib2 a pointer to a indexbook
 *
 * @return It returns an integer less than or greater than zero if
 * id of ib1 is found,  respectively, to be less than or be greater 
 * than id of ib2.
 */
int indexbook_cmp (const void *ib1, const void *ib2);


/**
 * @brief Allocates memory for a indexbook where it copies the data from
 * the indexbook src.
 * 
 * @param src a pointer to the original indexbook
 *
 * @return Returns the pointer of the copied indexbook if everything 
 * went well, or NULL otherwise.
 */
IndexBook *indexbook_copy (const IndexBook *src);


/** 
 * @brief Prints in pf the data of a indexbook.
 *
 * @param pf a pointer to a file
 * @param ib a pointer to a indexbook
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int indexbook_print (FILE *pf, const void *ib);

#endif