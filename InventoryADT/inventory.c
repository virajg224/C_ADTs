#include "inventory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


struct invnode {
  char *item;   
  int value;  
  struct invnode *left;
  struct invnode *right;
};

struct inventory {
  struct invnode *root;
};


struct inventory *inventory_create(void) {
  struct inventory *inv = malloc(sizeof(struct inventory));
  inv->root = NULL;
  return inv;
}


void free_invnode(struct invnode *node) {
  if (node) {
    free_invnode(node->left);
    free_invnode(node->right);
    free(node->item);
    free(node);
  }
}

void inventory_destroy(struct inventory *inv) {
  assert(inv);

  free_invnode(inv->root);
  free(inv);
}


int inventory_lookup(const struct inventory *inv, const char *item) {
 assert(inv);
 
 struct invnode *curnode = inv->root;
  while (curnode) {
    if (strcmp(curnode->item, item) == 0) {
      return curnode->value;
    }
    else if (item < curnode->item) {
      curnode = curnode->left;
    } 
    else {
      curnode = curnode->right;
    }
  }
  return -1;
}


static char *my_strdup(const char *src) {
  char *dup = malloc(strlen(src) * sizeof(char) + 1);
  strcpy(dup, src);
  return dup;
}

struct invnode *insert_invnode(int key, const char *val, struct invnode *node) {

  if (node == NULL) {
    node = malloc(sizeof(struct invnode));
    node->value = key;
    node->item = my_strdup(val); 
    node->left = NULL;
    node->right = NULL;
  }
   else if (strcmp(node->item, val) == 0) {
    node->value = node->value + key;
  }
   else if (val < node->item) {
    node->left = insert_invnode(key, val, node->left);
  } 
   else if (val > node->item) {
    node->right = insert_invnode(key, val, node->right);
  } 
   else { 
    free(node->item);
    node->item = my_strdup(val);
  }
  return node;
}

void inventory_add(struct inventory *inv, const char *item, int qty) {
 assert(qty >= 0);
 assert(inv);

 inv->root = insert_invnode(qty, item, inv->root);
}


struct invnode *remove_invnode(int key, const char *item, struct invnode *node) {
  if (node == NULL) {
   return NULL;
  }
  else if (strcmp(node->item, item) == 0) {
   struct invnode *backup = node;
   backup->value = backup->value - key;
   return backup;
  } 
 else if (item < node->item) {
    node->left = remove_invnode(key, item, node->left);
  } 
 else if (item > node->item) {
    node->right = remove_invnode(key, item, node->right);
  } 
 else if ((node->left == NULL) && (node->value - key == 0))  {
    struct invnode *backup = node->right;
    free(node->item);
    free(node);
    return backup;    
 } 
  else {
    struct invnode *backup = node->left;
    free(node->item);
    free(node);
    return backup; 
  } 
 
 return node;
}
  
void inventory_remove(struct inventory *inv, const char *item, int qty){
  assert(inv);
  assert(0 < qty && qty <= inventory_lookup(inv, item));

  inv->root = remove_invnode(qty, item, inv->root);
}
