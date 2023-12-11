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
int index_numberOfNodes_rec(BSTNode *pn);
void index_inOrder_keys_rec(BSTNode *pn, int *keys, P_ele_key key_ele, int pos);
int index_save_rec(BSTNode *pn, FILE *pf);

/**** PUBLIC FUNCTIONS ****/

Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele, P_ele_size size_ele, P_ele_free free_ele){
  Index *index = NULL;

  if (!print_ele || !cmp_ele || !size_ele || !free_ele) return NULL;

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

int index_inOrder(FILE *f, const Index *index){
  int order = 0;

  if (!f || !index) return -1;

  return _bst_inOrder_rec(index->root, f, index->print_ele, &order) + fprintf(f, "\n");
}

void *index_find(Index *index, const void *elem){
  if (!index || index_isEmpty(index) || !elem) return NULL;

  return index_find_rec(index->root, elem, index->cmp_ele);
}

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

Status index_remove(Index *index, const void *elem) {
  BSTNode *aux_elem = index->root;
  
  if (!index || !elem || !index_contains(index, elem)) return ERROR;

  while (index->cmp_ele(aux_elem, elem) != 0){
    if(index->cmp_ele(aux_elem, elem) > 0) aux_elem = aux_elem->left;
    if(index->cmp_ele(aux_elem, elem) < 0) aux_elem = aux_elem->right;
  }

  _bst_node_free(aux_elem, index->free_ele);
  return OK;
}

int index_numberOfNodes(const Index *index){
  if (!index) return -1;

  return index_numberOfNodes_rec(index->root);
}

int *index_inOrder_keys(const Index *index, P_ele_key key_ele){
  int *keys = NULL;

  if (!index || !key_ele)
    return NULL;

  keys = malloc(index_numberOfNodes(index)*sizeof(int));
  if (!keys) return NULL;

  index_inOrder_keys_rec(index->root, keys, key_ele, 0);

  return keys;
}

Status index_load(Index *index, FILE *pf){
  int key;
  long offset;
  size_t size;
  IndexBook *ib;

  if (!index || !pf) return ERROR;

  while (fread(&key, sizeof(int), 1, pf) != 0 && fread(&offset, sizeof(long), 1, pf) != 0 && fread(&size, sizeof(size_t), 1, pf) != 0){
    ib = indexbook_init();
    indexbook_setKey(ib, key);
    indexbook_setOffset(ib, offset);
    indexbook_setSize(ib, size - 8);
    index_insert(index, ib);
  }

  return OK;
}

int index_save(const Index *index, FILE *pf){
  if (!index || !pf) return -1;

  return index_save_rec(index->root, pf);
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
  if (!pn || !free_ele) return;

  free_ele(pn->info);
  free(pn);
}

void _bst_node_free_rec(BSTNode *pn, P_ele_free free_ele){
  if (!pn || !free_ele) return;

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
  if (!size_ele) return -1;

  size += index_size_rec(pn->left, size_ele);
  size += index_size_rec(pn->right, size_ele);
  size += size_ele(pn->info);

  return size;
}

Bool index_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  if (!pn || !elem || !cmp_ele) return FALSE;

  if (cmp_ele(pn->info, elem) == 0  || index_contains_rec(pn->right, elem, cmp_ele) || index_contains_rec(pn->left, elem, cmp_ele))
    return TRUE;
  
  return FALSE;
}

BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  
  if (!elem || !cmp_ele) return NULL;

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

  if (!pf || !print_ele || !order) return -1;

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

int index_numberOfNodes_rec(BSTNode *pn){
  if (!pn) return 0;

  return index_numberOfNodes_rec(pn->left) + index_numberOfNodes_rec(pn->right) + 1;
}

void index_inOrder_keys_rec(BSTNode *pn, int *keys, P_ele_key key_ele, int pos){
  if (!pn || !keys || !key_ele || pos < 0) return;

  index_inOrder_keys_rec(pn->left, keys, key_ele, pos);
  keys[pos] = key_ele(pn->info);
  pos++;
  index_inOrder_keys_rec(pn->right, keys, key_ele, pos);
}

int index_save_rec(BSTNode *pn, FILE *pf){
  int count=0, aux;

  if (!pn || !pf) return 0;

  aux = index_save_rec(pn->left, pf);
  if (aux == -1) return -1;

  count += aux;

  aux = indexbook_save(pn->info, pf);
  if (aux == -1) return -1;

  count += aux;

  aux = index_save_rec(pn->right, pf);
  if (aux == -1) return -1;

  count += aux;

  return count;
}