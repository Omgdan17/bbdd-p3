#ifndef BOOK_H
#define BOOK_H

#include "types.h"

/**
 * Book type definition.
*/
typedef struct _Book Book;

/**
 * @brief Constructor. Initialize a book.
 *
 * @return Return the initialized book if it was done correctly, 
 * otherwise return NULL.
*/
Book *book_init ();

/**
 * @brief Destructor. Free the dynamic memory reserved for a book .
 *
 * @param book a pointer to a book
 */
void book_free (void *book);

/**
 * @brief  Gets the book size.
 *
 * @param book a pointer to a book
 *
 * @return  Returns an array with the ISBN of the given book.
 */
size_t *book_getSize (const Book *book);

/**
 * @brief  Gets the book id.
 *
 * @param book a pointer to a book
 *
 * @return  Returns the id of the given book, or -1 in case of error.
 */
int book_getId (const Book *book);

/**
 * @brief  Gets the book isbn.
 *
 * @param book a pointer to a book
 *
 * @return  Returns an array with the isbn of the given book.
 */
char *book_getIsbn (const Book *book);

/**
 * @brief  Gets the book title.
 *
 * @param book a pointer to a book
 *
 * @return  Returns an array with the title of the given book.
 */
char *book_getTitle (const Book *book);

/**
 * @brief  Gets the book printedby.
 *
 * @param book a pointer to a book
 *
 * @return  Returns an array with the printedby of the given book.
 */
char *book_getPrintedBy (const Book *book);

/**
 * @brief Modifies the id of a given book.
 *
 * @param ib a pointer to a book
 *
 * @return Returns OK or ERROR in case of error 
 */
Status book_setSize (Book *book);

/**
 * @brief Modifies the id of a given book.
 *
 * @param book a pointer to a book
 * @param id the id number of a new book, must be equal or greater than 0
 *
 * @return Returns OK or ERROR in case of error 
 */
Status book_setId (Book *book, const int id);

/**
 * @brief Modifies the isbn of a given book.
 *
 * @param book a pointer to a book
 * @param isbn an array with the isbn of a new book
 *
 * @return Returns OK or ERROR in case of error 
 */
Status book_setIsbn (Book *book, const char *isbn);

/**
 * @brief Modifies the title of a given book.
 *
 * @param book a pointer to a book
 * @param title an array with the title of a new book
 *
 * @return Returns OK or ERROR in case of error 
 */
Status book_setTitle (Book *book, const char *title);

/**
 * @brief Modifies the printedBy of a given book.
 *
 * @param book a pointer to a book
 * @param printedBy an array with the printedBy of a new book
 *
 * @return Returns OK or ERROR in case of error 
 */
Status book_setPrintedBy (Book *book, const char *printedBy);

/** 
 * @brief Prints in pf the data of a book.
 *
 * @param pf a pointer to a file
 * @param ib a pointer to a book
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int book_print (FILE *pf, const Book *book);

#endif