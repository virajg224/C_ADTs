#include "priqueue.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct priqueue {
  int *index;
  int *priority;
  int len;
  int maxlen;
};


struct priqueue *priqueue_create(void) {
  struct priqueue *ret = malloc(sizeof(struct priqueue));
  ret->len = 0;
  ret->maxlen = 1;
  ret->index = malloc(ret->maxlen * sizeof(int));
  ret->priority = malloc(ret->maxlen * sizeof(int));
  return ret;
}


void priqueue_destroy(struct priqueue *pq) {
  assert(pq);
  free(pq->index);
  free(pq->priority);
  free(pq);
}


int priqueue_length(const struct priqueue *pq) {
  assert(pq);
 
  return pq->len;
}


static int round_closest(const int a, const int b) {
	  if ((a % b) <= (b / 2)) { 
	  return a / b; 
  } 
	   else { 
	   return ((a / b) + 1); 
  } 
}

static void swap(struct priqueue *pq, int pos1, int pos2) {
  assert(pq);
  assert(0 <= pos1);
  assert(pos1 < pq->len);
  assert(0 <= pos2);
  assert(pos2 < pq->len);
 
  int temp = pq->index[pos1];
  pq->index[pos1] = pq->index[pos2];
  pq->index[pos2] = temp;
  temp = pq->priority[pos1];
  pq->priority[pos1] = pq->priority[pos2];
  pq->priority[pos2] = temp;
}

void priqueue_add(struct priqueue *pq, int item, int priority) {
  assert(pq);
 
  if (pq->len == pq->maxlen) {
    pq->maxlen *= 2;
    pq->index = realloc(pq->index, pq->maxlen * sizeof(int));
    pq->priority = realloc(pq->priority, pq->maxlen * sizeof(int));
  }
  pq->index[pq->len] = item;
  pq->priority[pq->len] = priority;
  ++pq->len;
  for (int i = pq->len - 1; i > 0;) {
   int parent = round_closest(i - 1, 2);
   if (pq->priority[i] > pq->priority[parent]) {
    swap(pq, i, parent);
    i = parent;
   }
   else {
    break;
   }
  }
}
 

int priqueue_front(const struct priqueue *pq) {
  assert(pq);
  assert(pq->len != 0);
 
  return pq->index[0];
}


int priqueue_remove(struct priqueue *pq) {
  assert(pq);
  
  int i = 0;
  int ret = pq->index[0];
  swap(pq, 0, pq->len - 1);
  --pq->len;
  while (i*2+2 < pq->len) {
    if (pq->priority[i] < pq->priority[i*2+1] && 
        pq->priority[i] < pq->priority[i*2+2]) {
     if (pq->priority[i*2+1] > pq->priority[i*2+2]) {
        swap(pq, i, i*2+1);
        i = i*2+1;
      } 
     else {
        swap(pq, i, i*2+2);
        i = i*2+2;
      }
    } 
   else if (pq->priority[i] < pq->priority[i*2+1]) {
      swap(pq, i, i*2+1);
      i = i*2+1;
    } 
   else if (pq->priority[i] < pq->priority[i*2+2]) {
      swap(pq, i, i*2+2);
      i = i*2+2;
    } 
   else {
      break;
    }
  }
  return ret;
}


void priqueue_print(const struct priqueue *pq) {
  assert(pq);
  if (pq->len == 0) {
   printf("[empty]\n");
  } 
  else {
   printf("[");
   for (int i = 0; i < pq->len - 1; ++i) {
     printf("(%d:%d),", pq->index[i], pq->priority[i]);
   }
     printf("(%d:%d)]\n", pq->index[pq->len - 1], 
            pq->priority[pq->len - 1]);
   }
}
