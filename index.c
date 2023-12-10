#include "index.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _Index {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
  P_ele_size size_ele;
  P_ele_free free_ele;
};

/**** PRIVATE FUNCTIONS HEADINGS ****/

BSTNode *_bst_node_new();
void _bst_node_free(BSTNode *pn, P_ele_free free_ele);
void _bst_node_free_rec(BSTNode *pn, P_ele_free free_ele);
int _bst_depth_rec(BSTNode *pn);
size_t index_size_rec(BSTNode *pn, P_ele_size size_ele);
Bool index_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele, int *order);
void *index_find_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);

/**** PUBLIC FUNCTIONS ****/

Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele, P_ele_size size_ele, P_ele_free free_ele){
  Index *index = NULL;

  if (!print_ele || !cmp_ele) return NULL;

  index = malloc(sizeof(Index));
  if (!index) return NULL;

  index->root = NULL;
  index->print_ele = print_ele;
  index->cmp_ele = cmp_ele;
  index->size_ele = size_ele;
  index->free_ele = free_ele;

  return index;
}

void index_destroy(Index *index){
  if (!index) return;

  _bst_node_free_rec(index->root, index->free_ele);
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

size_t index_size(const Index *index){
  if (!index || !index->size_ele) return -1;

  return index_size_rec(index->root, index->size_ele);
}

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
int index_inOrder(FILE *f, const Index *index){
  int order = 0;

  if (!f || !index) return -1;

  return _bst_inOrder_rec(index->root, f, index->print_ele, &order) + fprintf(f, "\n");
}

/**
 * @brief Same as tree_preOrder but with postOrder algorithm.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return See tree_preOrder.
 */
int index_postOrder(FILE *f, const Index *index);

void *index_find(Index *index, const void *elem){
  if (!index || index_isEmpty(index) || !elem) return NULL;

  return index_find_rec(index->root, elem, index->cmp_ele);
}

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

Bool index_contains(Index *index, const void *elem){
  if (!index || !elem) return TRUE;

  return index_contains_rec(index->root, elem, index->cmp_ele);
}

Status index_insert(Index *index, const void *elem){
  BSTNode *pn = NULL;

  if (!index || !elem) return ERROR; 

  if (index_contains(index, elem)) return OK;
  
  pn = _bst_insert_rec(index->root, elem, index->cmp_ele);
  if (!pn) return ERROR;
  
  index->root = pn;
  
  return OK;
}

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
Status index_remove(Index *index, const void *elem) {
  BSTNode *aux_elem = index->root;
  
  if(!index || !elem || !index_contains(index, elem)) {
    return ERROR;
  }

  while(index->cmp_ele(aux_elem, elem) != 0) {
    if(index->cmp_ele(aux_elem, elem) > 0) aux_elem = aux_elem->left;
    if(index->cmp_ele(aux_elem, elem) < 0) aux_elem = aux_elem->right;
  }

  _bst_node_free(aux_elem, index->free_ele);
  return OK;
}



/**** PRIVATE FUNCTIONS ****/

BSTNode *_bst_node_new(){
  BSTNode  *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) return NULL;

  pn->info = NULL;
  pn->left = NULL;
  pn->right = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn, P_ele_free free_ele){
  if (!pn) return;

  free_ele(pn->info);
  free(pn);
}

void _bst_node_free_rec(BSTNode *pn, P_ele_free free_ele){
  if (!pn) return;

  _bst_node_free_rec(pn->left, free_ele);
  _bst_node_free_rec(pn->right, free_ele);
  _bst_node_free(pn, free_ele);
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

size_t index_size_rec(BSTNode *pn, P_ele_size size_ele){
  size_t size = 0;

  if (!pn) return 0;

  size += index_size_rec(pn->left, size_ele);
  size += index_size_rec(pn->right, size_ele);
  size += size_ele(pn->info);

  return size;
}

Bool index_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  if (!pn) return FALSE;

  if (cmp_ele(pn->info, elem) == 0  || index_contains_rec(pn->right, elem, cmp_ele) || index_contains_rec(pn->left, elem, cmp_ele))
    return TRUE;
  
  return FALSE;
}

BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  
  if (!pn){
    pn = _bst_node_new();
    pn->info = (void*)elem;
    return pn;
  }

  if (cmp_ele(elem, pn->info) < 0){
    pn->left = _bst_insert_rec(pn->left, elem, cmp_ele);
  }
  else if (cmp_ele(elem, pn->info) > 0){
    pn->right = _bst_insert_rec(pn->right, elem, cmp_ele);
  }
  
  return pn;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele, int *order){
  int count = 0;

  if (!pn) return count;

  count += _bst_inOrder_rec(pn->left, pf, print_ele, order);
  count += fprintf(stdout, "Entry #%d\n", *order);
  (*order)++;
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele, order);

  return count;
}

void *index_find_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  int cmp;

  if (!pn || !elem || !cmp_ele) return NULL;

  cmp = cmp_ele(pn->info, elem);

  if (cmp == 0) return pn->info;
  else if (cmp < 0) return index_find_rec(pn->right, elem, cmp_ele);
  else return index_find_rec(pn->left, elem, cmp_ele);
}