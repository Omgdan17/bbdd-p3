#include "library.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  IndexBook *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _Index {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};

BSTNode *_bst_node_new(){
  BSTNode  *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) return NULL;

  pn->info = NULL;
  pn->left = NULL;
  pn->right = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn){
  if (!pn) return;

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn){
  if (!pn) return;

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);
}

int _bst_depth_rec(BSTNode *pn){
  int depth_l, depth_r;

  if (!pn) return 0;

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l)
    return depth_r + 1;
  else
    return depth_l + 1;
}

Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele){
  Index *index = NULL;

  if (!print_ele || !cmp_ele) return NULL;

  index = malloc(sizeof(Index));
  if (!index) return NULL;

  index->root = NULL;
  index->print_ele = print_ele;
  index->cmp_ele = cmp_ele;

  return index;
}

void index_destroy(Index *index){
  if (!index) return;

  _bst_node_free_rec(index->root);
  free(index);
}

Bool index_isEmpty(const Index *index){
  if (!index || !index->root) return TRUE;

  return FALSE;
}

int index_depth(const Index *index){
  if (!index) return -1;

  return _bst_depth_rec(index->root);
}

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
 * @brief Public function that tells if an element is in a Binary Search Tree.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be found in the Tree.
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