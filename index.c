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
  P_ele_save save_ele;
};

/**** PRIVATE FUNCTIONS HEADINGS ****/

BSTNode *_bst_node_new();
void _bst_node_free(BSTNode *pn, P_ele_free free_ele);
void _bst_node_free_rec(BSTNode *pn, P_ele_free free_ele);
int _bst_depth_rec(BSTNode *pn);
size_t _index_size_rec(BSTNode *pn, P_ele_size size_ele);
Bool _index_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
BSTNode *_index_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele, P_ele_free free_ele);
BSTNode *_bst_find_min_rec(BSTNode *pn);
BSTNode *_bst_find_max_rec(BSTNode *pn);
BSTNode *_bst_find_node_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
BSTNode *_bst_find_father(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele, int *order);
void *_index_find_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele);
int _index_numberOfNodes_rec(BSTNode *pn);
void _index_inOrder_keys_rec(BSTNode *pn, int *keys, P_ele_key key_ele, int pos);
int _index_save_rec(BSTNode *pn, FILE *pf, P_ele_save save_ele);
long _index_firstfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele);
long _index_bestfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele);
long _index_worstfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele);

/**** PUBLIC FUNCTIONS ****/

Index *index_init(P_ele_print print_ele, P_ele_cmp cmp_ele, P_ele_size size_ele, P_ele_free free_ele, P_ele_save save_ele){
  Index *index = NULL;

  /*if (!print_ele || !cmp_ele || !size_ele || !free_ele || !save_ele) return NULL;*/

  index = malloc(sizeof(Index));
  if (!index) return NULL;

  index->root = NULL;
  index->print_ele = print_ele;
  index->cmp_ele = cmp_ele;
  index->size_ele = size_ele;
  index->free_ele = free_ele;
  index->save_ele = save_ele;

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

  return _index_size_rec(index->root, index->size_ele);
}

int index_inOrder(FILE *f, const Index *index){
  int order = 0;

  if (!f || !index) return -1;
  if (index_isEmpty(index)) return 0;

  return _bst_inOrder_rec(index->root, f, index->print_ele, &order) + fprintf(f, "\n");
}

void *index_find(Index *index, const void *elem){
  if (!index || index_isEmpty(index) || !elem) return NULL;

  return _index_find_rec(index->root, elem, index->cmp_ele);
}

Bool index_contains(Index *index, const void *elem){
  if (!index || !elem) return TRUE;

  return _index_contains_rec(index->root, elem, index->cmp_ele);
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

Status index_remove(Index *index, const void *elem){

  if (!index || !elem || index_isEmpty(index) || !index_contains(index, elem)) return ERROR;

  /*pn = _bst_find_node_rec(index->root, elem, index->cmp_ele);
  if (!pn) return ERROR;*/

  if (index->cmp_ele(index->root->info, elem) == 0){
    index->root = _index_remove_rec(index->root, elem, index->cmp_ele, index->free_ele);
    return OK;
  }

  _index_remove_rec(index->root, elem, index->cmp_ele, index->free_ele);

  /*if (pn == index->root){
    index->root = _index_remove_rec(index->root, elem, index->cmp_ele, index->free_ele);
    return OK;
  }*/

  /*fat = _bst_find_father(index->root, elem, index->cmp_ele);*/


  /*if (index->cmp_ele(pn->info, elem) < 0)
    pn->left = _index_remove_rec(pn->left, elem, index->cmp_ele, index->free_ele);
  else
    pn->right = _index_remove_rec(pn->left, elem, index->cmp_ele, index->free_ele);*/

  /*if (index->cmp_ele(fat->info, elem) < 0)
    fat->left =  _index_remove_rec(index->root, elem, index->cmp_ele, index->free_ele);
  else
    fat->right = _index_remove_rec(index->root, elem, index->cmp_ele, index->free_ele);*/

  return OK;
}

void *index_find_min(Index *index){
  BSTNode *aux = NULL;

  if (!index)
    return NULL;
  if (index_isEmpty(index))
    return NULL;

  aux = _bst_find_min_rec(index->root);
  
  return aux->info;
}

void *index_find_max(Index *index){
  BSTNode *aux = NULL;

  if (!index)
    return NULL;
  if (index_isEmpty(index))
    return NULL;

  aux = _bst_find_max_rec(index->root);
  
  return aux->info;
}


int index_numberOfNodes(const Index *index){
  if (!index) return -1;

  return _index_numberOfNodes_rec(index->root);
}

int *index_inOrder_keys(const Index *index, P_ele_key key_ele){
  int *keys = NULL;

  if (!index || !key_ele)
    return NULL;

  keys = malloc(index_numberOfNodes(index)*sizeof(int));
  if (!keys) return NULL;

  _index_inOrder_keys_rec(index->root, keys, key_ele, 0);

  return keys;
}

Status index_load(Index *index, FILE *pf, char *type){
  IndexBook *auxb = NULL, *ib = NULL;
  IndexDeleted *auxd = NULL, *id = NULL;

  if (!index || !pf || !type) return ERROR;

  if (strcmp(type, "indexbook") == 0){
    while ((auxb = indexbook_load(pf)) != NULL){
      ib = indexbook_copy(auxb);
      index_insert(index, ib);
      free(auxb);
    }    
  }
  else if (strcmp(type, "indexdeleted") == 0){
    while ((auxd = indexdeleted_load(pf))){
      id = indexdeleted_copy(auxd);
      index_insert(index, id);
      free(auxd);
    }
  }

  return OK;
}

int index_save(const Index *index, FILE *pf){
  if (!index || !pf) return -1;

  return _index_save_rec(index->root, pf, index->save_ele);
}

long index_firstfit(Index *index, const int size){
  if (!index || index_isEmpty(index) || size < 0) return -1;

  return _index_firstfit_rec(index, index->root, size, index->cmp_ele);
}

long index_bestfit(Index *index, const int size){
  if (!index || index_isEmpty(index) || size < 0) return -1;

  return _index_bestfit_rec(index, index->root, size, index->cmp_ele);
}

long index_worstfit(Index *index, const int size){
  if (!index || index_isEmpty(index) || size < 0) return -1;

  return _index_worstfit_rec(index, index->root, size, index->cmp_ele);
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

size_t _index_size_rec(BSTNode *pn, P_ele_size size_ele){
  size_t size = 0;

  if (!pn) return 0;
  if (!size_ele) return -1;

  size += _index_size_rec(pn->left, size_ele);
  size += _index_size_rec(pn->right, size_ele);
  size += size_ele(pn->info);

  return size;
}

Bool _index_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  if (!pn || !elem || !cmp_ele) return FALSE;

  if (cmp_ele(pn->info, elem) == 0  || _index_contains_rec(pn->right, elem, cmp_ele) || _index_contains_rec(pn->left, elem, cmp_ele))
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

BSTNode *_index_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele, P_ele_free free_ele){
  BSTNode *aux = NULL;

  if (cmp_ele(elem, pn->info) < 0)
    pn->left = _index_remove_rec(pn->left, elem, cmp_ele, free_ele);
  else if (cmp_ele(elem, pn->info) > 0)
    pn->right = _index_remove_rec(pn->right, elem, cmp_ele, free_ele);
  else{
    if (pn->right && pn->left){
      aux = _bst_find_min_rec(pn->right);
      pn->info = aux->info;
      pn->right = _index_remove_rec(pn->right, aux->info, cmp_ele, free_ele);
    }
    else{
      aux = pn;
      if (!(pn->left))
        pn = pn->right;
      else if (!(pn->right))
        pn = pn->left;
      _bst_node_free(aux, free_ele);
    }
  }

  return pn;
}

BSTNode *_bst_find_min_rec(BSTNode *pn){

  if (!pn) return NULL;

  if (!pn->left) return pn;

  return _bst_find_min_rec(pn->left);
}

BSTNode *_bst_find_max_rec(BSTNode *pn){
  /*check arguments*/
  if (!pn) return NULL;

  if (!pn->right) return pn;

  return _bst_find_max_rec(pn->right);
}

BSTNode *_bst_find_node_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  /*check arguments*/
  if (!pn || !elem || !cmp_ele) return NULL;

  if (cmp_ele(elem, pn->info) < 0)
    return _bst_find_node_rec(pn->left, elem, cmp_ele);
  else if (cmp_ele(elem, pn->info) > 0)
    return _bst_find_node_rec(pn->right, elem, cmp_ele);
  else
    return pn;
}
BSTNode *_bst_find_father(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  if (!pn || !elem || !cmp_ele) return NULL;

  if (cmp_ele(pn->info, elem) == 0) return NULL;

  if (cmp_ele(pn->info, elem) > 0){
    if (cmp_ele(pn->left->info, elem) == 0)
      return pn;
    else
      return _bst_find_father(pn->left, elem, cmp_ele);
  }
  else{
    if (cmp_ele(pn->right->info, elem) == 0)
      return pn;
    else
      return _bst_find_father(pn->right, elem, cmp_ele);
  }
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

void *_index_find_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele){
  int cmp;

  if (!pn || !elem || !cmp_ele) return NULL;

  cmp = cmp_ele(pn->info, elem);

  if (cmp == 0) return pn->info;
  else if (cmp < 0) return _index_find_rec(pn->right, elem, cmp_ele);
  else return _index_find_rec(pn->left, elem, cmp_ele);
}

int _index_numberOfNodes_rec(BSTNode *pn){
  if (!pn) return 0;

  return _index_numberOfNodes_rec(pn->left) + _index_numberOfNodes_rec(pn->right) + 1;
}

void _index_inOrder_keys_rec(BSTNode *pn, int *keys, P_ele_key key_ele, int pos){
  if (!pn || !keys || !key_ele || pos < 0) return;

  _index_inOrder_keys_rec(pn->left, keys, key_ele, pos);
  keys[pos] = key_ele(pn->info);
  pos++;
  _index_inOrder_keys_rec(pn->right, keys, key_ele, pos);
}

int _index_save_rec(BSTNode *pn, FILE *pf, P_ele_save save_ele){
  int count=0, aux;

  if (!pn || !pf || !save_ele) return 0;

  aux = _index_save_rec(pn->left, pf, save_ele);
  if (aux == -1) return -1;

  count += aux;

  aux = save_ele(pn->info, pf);
  if (aux == -1) return -1;

  count += aux;

  aux = _index_save_rec(pn->right, pf, save_ele);
  if (aux == -1) return -1;

  count += aux;

  return count;
}

long _index_firstfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele){
  long offset;

  if (!pn) return -1;

  if (indexdeleted_getSize(pn->info) - size > 0){
    offset = indexdeleted_getOffset(pn->info);
    indexdeleted_setOffset(pn->info, offset + sizeof(long) + size);
    indexdeleted_setSize(pn->info, indexdeleted_getSize(pn->info) - sizeof(long) - size);
    return offset;
  }
  else if (indexdeleted_getSize(pn->info) - size == 0){
    offset = indexdeleted_getOffset(pn->info);
    index_remove(index, pn->info);
    return offset;
  }
  else
   return _index_firstfit_rec(index, pn->right, size, cmp_ele);

}

long _index_bestfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele){
  long offset;

  if (!pn) return -1;

  if (indexdeleted_getSize(pn->info) - size == 0){
    offset = indexdeleted_getOffset(pn->info);
    index_remove(index, pn->info);
    return offset;
  }
  else if (indexdeleted_getSize(pn->info) - size > 0){
    offset = _index_bestfit_rec(index, pn->left, size, cmp_ele);
    if (offset == -1){
      offset = indexdeleted_getOffset(pn->info);
      indexdeleted_setOffset(pn->info, offset + sizeof(long) + size);
      indexdeleted_setSize(pn->info, indexdeleted_getSize(pn->info) - sizeof(long) - size);
      return offset;
    }
    else return offset;
  }
  else return _index_bestfit_rec(index, pn->right, size, cmp_ele);
}

long _index_worstfit_rec(Index *index, BSTNode *pn, const int size, P_ele_cmp cmp_ele){
  IndexDeleted *id = NULL;
  long offset;

  if (!pn) return -1;

  id = index_find_max(index);

  if (indexdeleted_getSize(id) - size > 0){
    offset = indexdeleted_getOffset(pn->info);
    indexdeleted_setOffset(pn->info, offset + sizeof(long) + size);
    indexdeleted_setSize(pn->info, indexdeleted_getSize(pn->info) - sizeof(long) - size);
    return offset;
  }
  else if (indexdeleted_getSize(id) - size == 0){
    offset = indexdeleted_getOffset(pn->info);
    index_remove(index, pn->info);
    return offset;
  }
  else
    return -1;
}