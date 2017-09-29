#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;


struct bst *bst_create(void) {
  struct bst *t = malloc(sizeof(struct bst));
  t->root = NULL;
  return t;
}


static void node_destroy(struct bstnode *node) {
  if (node) {
    node_destroy(node->left);
    node_destroy(node->right);
    free(node);
  }
}

void bst_destroy(struct bst *t) {
  assert(t);
  node_destroy(t->root);
  free(t);
}


int bst_size(struct bst *t) {
  assert(t);
  if (t->root == NULL) {
    return 0;
  } 
  else {
    return t->root->size;
  }
}


static struct bstnode *new_leaf(int i) {
  struct bstnode *leaf = malloc(sizeof(struct bstnode));
  leaf->item = i;
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->size = 1;
  return leaf;
}

static struct bstnode *insert_bstnode(int i, struct bstnode *node) {
  if (node == NULL) {
    node = new_leaf(i);
  } 
  else if (i < node->item) {
    node->left = insert_bstnode(i, node->left);
    ++node->size;
  } 
  else if (i > node->item) {
    node->right = insert_bstnode(i, node->right);
    ++node->size;
  }
  return node;
}

void bst_insert(int i, struct bst *t) {
  assert(t);
 
  if (bst_find(i, t)) {
   return;
  }
  t->root = insert_bstnode(i, t->root);
}


bool node_find(int i, struct bstnode *node) {
  if (node == NULL) {
    return false;
  } 
  else if (i > node->item) {
    return node_find(i, node->right);
  } 
  else if (i < node->item) {
    return node_find(i, node->left);
  } 
  else {
    return true;
  }
}

bool bst_find(int i, struct bst *t) {
  assert(t);
 
  return node_find(i, t->root);
}


static int node_select(int k, struct bstnode *node) {
  int left_size = 0;
  if (node->left) {
   left_size = node->left->size;
  }
  if (k < left_size) {
   return node_select(k, node->left);
  }
  if (k == left_size) {
   return node->item;
  }
  return node_select(k - left_size - 1, node->right);
}

int bst_select(int k, struct bst *t) {
  assert(t);
  assert(0 <= k);
  assert(k < t->root->size);
  return node_select(k, t->root);
}


struct bstnode *remove_bstnode(int i, struct bstnode *node) {
  if (node == NULL) {
   return NULL;
  }
  if (i < node->item) { 
    node->left = remove_bstnode(i, node->left);
    --node->size;
  } 
  else if (i > node->item) {
    node->right = remove_bstnode(i, node->right);
    --node->size;
  } 
  else if (node->left == NULL) { 
    struct bstnode *new_node = node->right; 
    free(node);
    return new_node;
  } 
  else if (node->right == NULL) {
    struct bstnode *new_node = node->left;
    free(node); 
    return new_node;
  } 
  else {
    struct bstnode *next = node->right; 
    while (next->left) { 
      next = next->left; 
    } 
    node->item = next->item;
    node->right = remove_bstnode(next->item, node->right);
    --node->size;
  } 
  return node;
}

void bst_remove (int i, struct bst *t) {
  if (!(bst_find(i, t))) {
   return;
  }
  t->root = remove_bstnode(i, t->root);
}


static int node_range(int start, int end, struct bstnode *node) {
  if (node == NULL) {
   return 0;
  }
   return node_range(start, end, node->left) + 
    ((start <= node->item) && (node->item <= end)) +
    node_range(start, end, node->right);
}

int bst_range(int start, int end, struct bst *t) {
  assert(t);
  assert(start <= end);
 
  return node_range(start, end, t->root);
}


static void pre_order(struct bstnode *node, int *len) {
 if (node == NULL) {
  return;
 }
 if (*len == 1) {
  printf("%d", node->item);
  return;
 }
 else {
  printf("%d,", node->item);
  --(*len);
 }
 pre_order(node->left, len);
 pre_order(node->right, len);
}

static void in_order(struct bst *t, int len) {
 int *arr = bst_to_sorted_array(t);
 for (int i = 0; i < len - 1; ++i) {
  printf("%d,", arr[i]);
 }
 printf("%d", arr[len - 1]);
 free(arr);
}

static void post_order(struct bstnode *node, int *len) {
 if (node == NULL) {
  return;
 }
 post_order(node->left, len);
 post_order(node->right, len); 
 if (*len > 1) {
  printf("%d,", node->item);
  --(*len);
 }
 else {
  printf("%d", node->item);
  return;
 }
}

void bst_print(int o, struct bst *t) {
 assert(t);
 
 if (t->root == NULL) {
  printf("[empty]\n");
  return;
 }
 else { 
 printf("[");
 int len = t->root->size;
 if (o == PRE_ORDER) {
  pre_order(t->root, &len);
 }
 else if (o == POST_ORDER) {
  post_order(t->root, &len);
 }
 else {
  in_order(t, len);
}
  printf("]\n");
  return;
 }
}


static int *node_to_array(struct bstnode *node, int *arr, int *i) {
  if (node->left) {
   node_to_array(node->left, arr, i);
  }
  arr[*i] = node->item;
  ++(*i);
  if (node->right) {
   node_to_array(node->right, arr, i);
  }
  return arr;
}

int *bst_to_sorted_array(struct bst *t) {
  assert(t);
 
  if (t->root == NULL) {
    return NULL;
  } 
  else {
    int i = 0;
    int len = t->root->size;
    int *arr = malloc(len * sizeof(int));
    return node_to_array(t->root, arr, &i);
  }
}


static struct bstnode *array_to_bst(int start, int end, int *arr) {
 if (start > end) {
  return NULL;
 }
 int mid = (start + end) / 2;
 struct bstnode *root = new_leaf(arr[mid]);
 root->size = end - start + 1;
 root->left = array_to_bst(start, mid - 1, arr);
 root->right = array_to_bst(mid + 1, end, arr);
 return root;
}

struct bst *sorted_array_to_bst(int *a, int len) {
  assert(a);
  assert(len > 0);

  struct bst *t = bst_create();
  t->root = array_to_bst(0, len - 1, a);
  return t;
}


void bst_rebalance(struct bst *t) {
  assert(t);

  if(t->root == NULL) {
   return;
  }
  int len = t->root->size;
  int *arr = bst_to_sorted_array(t);
  node_destroy(t->root);
  t->root = array_to_bst(0, len - 1, arr);
  free(arr);
}
