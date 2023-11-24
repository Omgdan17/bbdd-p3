#ifndef BOOK_H
#define BOOK_H

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
IndexBook * indexbook_init ();


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
long indexbook_getId (const IndexBook *ib);


/**
 * @brief Gets the indexbook isbn.
 *
 * @param ib a pointer to a indexbook
 *
 * @return Returns a pointer to the isbn of the indexbook, or NULL in 
 * case of error.
 */
const char* indexbook_getIsbn (const IndexBook *ib);

/**
 * @brief Gets the indexbook title.
 *
 * @param ib a pointer to a indexbook
 *
 * @return Returns a pointer to the title of the indexbook, or NULL in 
 * case of error.
 */
const char* indexbook_getTitle (const IndexBook *ib);

/**
 * @brief Gets the indexbook printedby.
 *
 * @param ib a pointer to a indexbook
 *
 * @return Returns a pointer to the printedby of the indexbook, or NULL in 
 * case of error.
 */
const char* indexbook_getPrintedBy (const IndexBook *ib);

/**
 * @brief Modifies the id of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param id the id number of a new indexbook, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setId (IndexBook *ib, const long id);

/**
 * @brief Modifies the isbn of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param isbn the isbn of a new indexbook
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setIsbn (IndexBook *ib, const char *isbn);

/**
 * @brief Modifies the title of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param title the title of a new indexbook
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setTitle (IndexBook *ib, const char *title);

/**
 * @brief Modifies the printedby of a given indexbook.
 *
 * @param ib a pointer to a indexbook
 * @param printedby the printedby of a new indexbook
 *
 * @return Returns OK or ERROR in case of error 
 */
Status indexbook_setPrintedBy (IndexBook *ib, const char *printedby);

/**
 * @brief Compares two vertices.
 *
 * First it compares their ids. If they are equal, then compares
 * their tags.
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
void *indexbook_copy (const void *src);


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