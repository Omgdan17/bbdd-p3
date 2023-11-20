#include "library.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _indexbook {
    int key; /*Book isbn*/
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
} indexbook;

/* START [_BSTNode] */
typedef struct _BSTNode {
  indexbook *info;
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