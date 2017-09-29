#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct sequence {
 struct seqnode *front;
 int len;
};

struct seqnode {
 int item;
 struct seqnode *next;
};


struct sequence *sequence_create(void) {
 struct sequence *seq = malloc(sizeof(struct sequence));
 seq->len = 0;
 seq->front = NULL;
 return seq;
};
 

void sequence_destroy(struct sequence *seq) {
 assert(seq);
 
 struct seqnode *curnode = seq->front;
 while(curnode) {
  struct seqnode *nextnode = curnode->next;
  free(curnode);
  curnode = nextnode;
 }
 free(seq);
}


int sequence_length(const struct sequence *seq) {
 assert(seq);
 
 return seq->len;
}


int sequence_item_at(const struct sequence *seq, int pos) {
 assert(seq);
 assert(0 <= pos);
 assert(pos < sequence_length(seq));
 
 struct seqnode *node = seq->front;
 int i = 0;
 while(node) {
  if (i == pos) {
   break;
  }
  node = node->next;
  ++i;
 }
 return node->item;
}


void sequence_insert_at(struct sequence *seq, int pos, int val) {
 assert(seq);
 assert(0 <= pos);
 assert(pos <= sequence_length(seq));
 
 struct seqnode *node = seq->front;
 struct seqnode *newnode = malloc(sizeof(struct seqnode));
 newnode->item = val;
 newnode->next = NULL;
  if (pos == 0) {
    newnode->next = seq->front;
    seq->front = newnode;
    ++seq->len;
  } 
  else {
    int i = 0;
    while (i != pos - 1) {
      node = node->next;
      ++i;
    }
    newnode->next = node->next;
    node->next = newnode;
    ++seq->len;
  } 
}
 

int sequence_remove_at(struct sequence *seq, int pos) {
 assert(seq);
 assert(0 <= pos);
 assert(pos < sequence_length(seq));
 
 struct seqnode *node = seq->front;
  if (pos == 0) {
    struct seqnode *temp = seq->front;
    seq->front = node->next;
    int ret = temp->item; 
    free(temp);
    --seq->len;
    return ret;
  }
  else {
    int i = 0;
    while (i != pos-1) {
      node = node->next;
      ++i;
    }
    struct seqnode *temp = node->next;
    node->next = node->next->next;
    int ret = temp->item; 
    free(temp);
    --seq->len;
    return ret;
  } 
}


void sequence_print(const struct sequence *seq) {
  assert(seq);

  struct seqnode *node = seq->front; 
  if (seq->len == 0) {
    printf("[empty]\n");
  }
  else {
    printf("[");
    while(node) {
      printf("%d", node->item);
      if (node->next) {
       printf(",");
      }
      node = node->next;
    }
    printf("]\n");
  } 
}
