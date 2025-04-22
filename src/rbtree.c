#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *tree = calloc(1, sizeof(rbtree));
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

void left_rotate(rbtree *tree, node_t *x) {
  node_t *y = x ->right;
  x -> right = y -> left;

  if (y->left != tree->nil) {
    y->left->parent = x;
  }
  y -> parent = x->parent;
  if (x -> parent == tree->nil) {
    tree->root = y;
  }
  else if (x == x -> parent->left) {
    x -> parent->left = y;
  }
  else {
    x -> parent->right = y;
  }
  y -> parent = x;
  x -> parent = y;
}

void right_rotate(rbtree *tree, node_t *x) {
  node_t *y = x->left;
  x->left = y -> right;
  if (y -> right != tree->nil) {
    y -> right ->parent = x;
  }
  y -> parent = x->parent;
  if ( x -> parent == tree->nil ) {
    tree->root = y;
  }
  else if (x == x -> parent->right) {
    x -> parent->right = y;
  }
  else {
    x -> parent->left = y;
  }
  y -> right = x;
  x -> parent = y;
}

void delete_node(rbtree *tree, node_t *node) {
  if (node == tree->nil) return;

  delete_node(tree, node->left);
  delete_node(tree, node->right);
  free(node);
}

void delete_rbtree(rbtree *t) {
  delete_node(t, t->root);
  free(t -> nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *x = t -> root;
  node_t *y = t->nil;
  node_t *z = calloc(1, sizeof(node_t));
  if (!z) return NULL;
  z -> key = key;


  while (x != t->nil) {
    y = x;
    if (z -> key < x -> key) {
      x = x -> left;
    }
    else {
      x = x -> right;
    }
  }
  z -> parent = y;
  if (y == t->nil) {
    t->root = z;
  }
  else if (z -> key < y -> key) {
    y -> left = z;
  }
  else {
    y -> right = z;
  }
  z -> left = t -> nil;
  z -> right = t -> nil;
  z -> color = RBTREE_RED;
  rbtree_insert_fixup(t, z);
  return t ->root;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  node_t *y;
  while (z->parent -> color == RBTREE_RED) {
    if (z->parent == z -> parent -> left) {
        y = z -> parent -> left;
        if (y -> color == RBTREE_RED) {
          z->parent->color = RBTREE_BLACK;
          y->color = RBTREE_BLACK;
          z -> parent -> parent -> color = RBTREE_RED;
          z = z -> parent -> parent;
        }
        else {
          if (z == z -> parent -> right) {
            z = z -> parent;
            left_rotate(t, z);
          }
          z -> parent -> color = RBTREE_BLACK;
          z -> parent -> parent -> color = RBTREE_RED;
          right_rotate(t, z -> parent -> parent);
        }
    }
    else {
      y = z -> parent -> parent -> left;
      if (y -> color == RBTREE_RED) {
        z -> parent -> color = RBTREE_BLACK;
        y -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        z = z -> parent -> parent;
      }
      else {
        if (z == z -> parent -> left) {
          z = z -> parent;
          right_rotate(t, z);
        }
        z -> parent -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        left_rotate(t, z -> parent -> parent);
      }
    }
  }
  t -> root -> color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cur = t->root;
  while (cur != t->nil) {
    if (cur->key < key) {
      cur = cur->right;
    }
    else if (cur->key > key) {
      cur = cur->left;
    }
    else {
      return cur;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *z = t->root;
  while (z->left != t->nil) {
    z = z->left;
  }
  return z;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *z = t->root;
  while (z->right != t->nil) {
    z = z->right;
  }
  return z;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}



