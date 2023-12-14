#ifndef INDEX_H
#define INDEX_H

#include "types.h"
#include "file_utils.h"
#include "indexbook.h"
#include "indexdeleted.h"
/**
 * Index type definition: a binary search of arbitrary elements.
 */
typedef struct _Index Index;

/**
 * @brief Public function that creates a new Index.
 *
 * @param print_ele Pointer to the function that prints a index element.
 * @param cmp_ele Pointer to the function that compares two index elements.
 * @param size_ele Pointer to the function that returns the size of an element in the index.
 *
 * @return Returns the address of the new Tree, or NULL in case of error.
 */
Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele, P_ele_size size_ele, P_ele_free free_ele, P_ele_save save_ele);

/**
 * @brief Public function that frees a Tree.
 *
 * Frees all the memory allocated for the Tree.
 *
 * @param tree Pointer to the Tree.
 */
void index_destroy(Index *index);

/**
 * @brief Public function that checks if a Tree is empty.
 *
 * Note that the return value is TRUE for a NULL Tree.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Bool value TRUE if the Tree is empty or NULL, Bool value FALSE
 * otherwise.
 */
Bool index_isEmpty(const Index *index);

/**
 * @brief Public function that returns the Tree's depth.
 *
 * @param tree Pointer to the Tree.
 *
 * @return -1 if the tree is empty, its depth otherwise, -1 for a NULL Tree.
 */
int index_depth(const Index *index);

/**
 * @brief Public function that returns the Tree's size (its number of elements).
 *
 * @param tree Pointer to the Tree.
 *
 * @return 0 if the tree is empty, its size otherwise, -1 for a NULL Tree.
 */
size_t index_size(const Index *index);

/**
 * @brief Public functions that prints the content of a Tree
 * when traversed with preOrder algorithm.
 *
 * Prints all the elements in the Tree to an output stream.
 * To print an element this function calls the function specified when creating
 * the Tree, print_ele.
 *
 * Note that this function simply calls the print_ele function for each Tree
 * element, without printing any additional information. Any desired format must
 * be included in the print_ele function.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return The sum of the return values of all the calls to print_ele if these
 * values are all positive; the first negative value encountered otherwise. If
 * the function print_ele is well constructed, this means that, upon successful
 * return, this function returns the number of characters printed, and a
 * negative value if an error occurs.
 */
int index_preOrder(FILE *f, const Index *index);

/**
 * @brief Same as tree_preOrder but with inOrder algorithm.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return See tree_preOrder.
 */
int index_inOrder(FILE *f, const Index *index);

/**
 * @brief Same as tree_preOrder but with postOrder algorithm.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return See tree_preOrder.
 */
int index_postOrder(FILE *f, const Index *index);

void *index_find(Index *index, const void *elem);

/**
 * @brief Public function that finds the minimum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * minimum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the minimum element if found, NULL otherwise.
 */
void *index_find_min(Index *index);

/**
 * @brief Public function that finds the maximum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * maximum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the maximum element if found, NULL otherwise.
 */
void *index_find_max(Index *index);

/**
 * @brief Public function that tells if an element is in an index.
 *
 * @param index Pointer to an index.
 * @param elem Pointer to the element to be found in the Index.
 *
 * @return Bool value TRUE if the element was found, FALSE otherwise.
 */
Bool index_contains(Index *index, const void *elem);

/**
 * @brief Public function that inserts an element into a Binary Search Tree.
 *
 * Inserts as a leaf the pointer of the element received as argument. If the
 * element is already in the BST it returns OK.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * insert position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be inserted into the Tree.
 *
 * @return Status value OK if the insertion could be done or the element was
 * already in the BST, Status value ERROR otherwise.
 */
Status index_insert(Index *index, const void *elem);

/**
 * @brief Public function that removes an element into a Binary Search Tree.
 *
 * Removes the (first) occurrence of the element received as argument.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * remove position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be removed from the Tree.
 *
 * @return Status value OK if the removal could be done or the element was not
 * in the BST, Status value ERROR otherwise.
 */
Status index_remove(Index *index, const void *elem);

int index_numberOfNodes(const Index *index);

int *index_inOrder_keys(const Index *index, P_ele_key key_ele);

Status index_load(Index *index, FILE *pf, char *type);

int index_save(const Index *index, FILE *pf);

long index_firstfit(Index *index, int size);
long index_bestfit(Index *index, int size);
long index_worstfit(Index *index, int size);







#endif