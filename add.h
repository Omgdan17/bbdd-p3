#ifndef ADD_H
#define ADD_H

#include "types.h"
#include "index.h"

/**
 * @brief Function that adds a new book to an index and stores it in memory
 * 
 * @param index a pointer to the index structure
 * @param lst a pointer to the index structure of deleted books
 * @param filename string with the name of a file
 * @param method the method for the insertion in the file
 * @param book_id int of the book id of the new book
 * @param isbn string of the isbn of the new book
 * @param title string of the title of the new book
 * @param printedBy string of the printedBy of the new book
 * 
 * @return OK if everything goes well, ERROR if not
*/
Status add(Index *index, Index *lst, char *filename, Method method, int book_id, char *isbn, char *title, char *printedBy);

/**
 * @brief Function that adds a new book's data to a file
 * 
 * @param filename the name of a file
 * @param offset the position of the file to write on
 * @param size the size of the data to be written
 * @param book_id int of the book id of the new book
 * @param isbn string of the isbn of the new book
 * @param title string of the title of the new book
 * @param printedBy string of the printedBy of the new book
*/
int add_to_file(char *filename, long offset, size_t size, int book_id, char *isbn, char *title, char *printedBy);

#endif