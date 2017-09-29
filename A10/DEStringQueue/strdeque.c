#include "strdeque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct strdeque {
 struct node *front;
 struct node *back;
 int len;
};

struct node {
 char *string;
 struct node *next;
 struct node *pre;
};
 

struct strdeque *strdeque_create(void) {
  struct strdeque *queue = malloc(sizeof(struct strdeque));
  queue->front = NULL;
  queue->back = NULL;
  queue->len = 0;
  return queue;
}


void strdeque_destroy(struct strdeque *sdeq) {
 assert(sdeq);
 
 struct node *node = sdeq->front; 
 while(node) {
  struct node *nextnode = node->next;
  free(node->string);
  free(node);
  node = nextnode;
 }
 free(sdeq);
}


bool strdeque_is_empty(const struct strdeque *sdeq) {
 assert(sdeq);
 
 return sdeq->len == 0;
}


static char *my_strdup(const char *s) {
  assert(s);
  char *newstr = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(newstr, s); 
  return newstr;
}

void strdeque_add_front(const char *str, struct strdeque *sdeq) {
  assert(str);
  assert(sdeq);
 
  struct node *node = sdeq->front; 
  struct node *newnode = malloc(sizeof(struct node));
  newnode->string = my_strdup(str); 
  newnode->pre = NULL;
  if (node == NULL) {
    newnode->next = NULL;
    sdeq->back = newnode;
  }
  else {
    newnode->next = node;
    node->pre = newnode;
  } 
  sdeq->front = newnode;
  ++sdeq->len;
}


void strdeque_add_back(const char *str, struct strdeque *sdeq) {
  assert(str);
  assert(sdeq);
 
  struct node *node = sdeq->back; 
  struct node *newnode = malloc(sizeof(struct node));
  newnode->string = my_strdup(str); 
  newnode->next = NULL;
  if (node == NULL) {
    newnode->pre = NULL;
    sdeq->front = newnode;
  }
  else {
    newnode->pre = node;
    node->next = newnode;
  } 
  sdeq->back = newnode;
  ++sdeq->len;
}


void strdeque_remove_front(struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->len);
 
  struct node *node = sdeq->front;
  if (sdeq->len == 1) {
    free(node->string);
    free(node);
    sdeq->front = NULL;
    sdeq->back = NULL;
  } 
  else {
    sdeq->front = node->next;
    free(node->string);
    free(node);
    sdeq->front->pre = NULL;
  }
  --sdeq->len;
}


void strdeque_remove_back(struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->len);
 
  struct node *node = sdeq->back; 
  if (sdeq->len == 1) {
    free(node->string);
    free(node);
    sdeq->front = NULL;
    sdeq->back = NULL;
  } 
  else {
    sdeq->back = node->pre;
    free(node->string);
    free(node);
    sdeq->back->next = NULL;
  }
  --sdeq->len;
}


const char *strdeque_front(const struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->len);
 
  return sdeq->front->string;
}


const char *strdeque_back(const struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->len);
 
  return sdeq->back->string;
}
