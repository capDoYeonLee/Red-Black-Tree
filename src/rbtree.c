#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *tree = calloc(1, sizeof(rbtree)); // 왜 쓰는지
  if (!tree) return NULL;

  tree->nil = malloc(sizeof(node_t));

  if(!tree->nil) {
    free(tree); return NULL;
  }

  tree->nil->color = RBTREE_BLACK;
  tree->nil->key = 0;
  tree->nil->left = tree->nil;
  tree->nil->right = tree->nil;
  tree->nil->parent = tree->nil;

  tree->root = tree->nil;

  return tree;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {


  node_t *z = calloc(1, sizeof(node_t));
  z->key = key;
  z->parent = z->left = z->right = t->nil;
  z->color = RBTREE_RED;

  node_t *x = t->root;
  node_t *y = t->nil;

  while (x != t->nil) {
    y = x;
    if (z->key < x->key) {
        x = x->left;
    }
    else{
      x = x->right;
    }
    z -> parent = y;

    if (y == t->nil) {
      t->root = z;
    }
    else if (z->key < y->key) {
      y->left = z;
    }
    else {
      y->right = z;
    }
    z -> left = t->nil;
    z -> right = t->nil;
    z -> color = RBTREE_RED;



  }


}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

