#include "mergesort.h"
#include "set.h"
#include <stdlib.h> 
#include <stdio.h>
#include <assert.h>

struct set { 
  int len;
  int maxlen;
  int *data;
};

static int isize = 32;


struct set *set_create(void) {
  struct set *s = malloc(sizeof(struct set));
  s->len = 0;
  s->maxlen = isize;
  s->data = malloc(s->maxlen * sizeof(int));
  return s;
}


void set_destroy(struct set *s) {
  assert(s);

  free(s->data);
  free(s);
}


int set_size(const struct set *s) {
 assert(s);

 return s->len;
}


bool set_member(const struct set *s, int i) {
 assert(s);

 int len = s->len;
 int d = 0;
 while(d < len) {
  if (s->data[d] == i) {
    return true;
  }
  ++d;
 }
 return false;
}
 

void set_add(struct set *s, int i) { 
 assert(s);
 
  if (!set_member(s, i)) {
    ++s->len;
    s->data = realloc(s->data, s->len * sizeof(int));
    s->data[s->len - 1] = i;
    merge_sort(s->data, s->len);
  }
}


void set_remove(struct set *s, int i) {
 assert(s);

 if (set_member(s, i)) {
  int a = 1;
  while (a < s->len) {
   if (s->data[a] > i) {
    s->data[a-1] = s->data[a];
   }
   ++a;
  }
  s->len -= 1;
 }
}


struct set *array_to_set(const int a[], int len) {
 struct set *s = set_create();
 int i = 0; 
 while (i < len) {
  if ((set_member(s, a[i])) == 1) {
  }
  else {
  set_add(s, a[i]);
  }
  ++i;
 }
 return s;
}
 

int *set_to_array(const struct set *s) {
 assert(s);
 if (s->len == 0) {
  return NULL;
 }
 else {
  int *a = malloc(s->len * sizeof(int));
  int i = 0;
  while (i < s->len) {
    a[i] = s->data[i];
    ++i;
  }
 return a;
 }
}


void set_print(const struct set *s) {
 if (s->len == 0) {
  printf("[empty]\n");
  return;
 }
 printf("[");
 int i = 0;
 while (i < (s->len - 1)) {
  printf("%d,", s->data[i]);
  ++i;
 }
 printf("%d]\n", s->data[s->len - 1]) ;
}
 

struct set *set_intersect(const struct set *s1, const struct set *s2) {
 struct set *ret = set_create();
 int i = 0;
 int len = s1->len;
 while (i < len) { 
  if (ret->len == ret->maxlen) { 
    ret->maxlen *= 2;
    ret->data = realloc(ret->data, ret->maxlen * sizeof(int));
  }   
  if (set_member(s2, s1->data[i])) {
    set_add(ret, s1->data[i]);
  }
   ++i;
 }
 return ret;
}


struct set *set_union(const struct set *s1, const struct set *s2){
 struct set *ret1 = set_create();
 
  int a = 0;
  for(int i = 0; i < s1->len; ++i) {
    if (!set_member(ret1, s1->data[i])) {
      ++ret1->len;
      if (ret1->len == ret1->maxlen) {
        ret1->maxlen *= 2;
        ret1->data = 
        realloc(ret1->data, ret1->maxlen * sizeof(int));
      }
      ret1->data[a] = s1->data[i];
      ++a;
    }
  }
  for(int i = 0; i < s2->len; ++i) {
    if (!set_member(ret1, s2->data[i])) {
      ++ret1->len;
      if (ret1->len == ret1->maxlen) {
        ret1->maxlen *= 2;
        ret1->data = 
        realloc(ret1->data, ret1->maxlen * sizeof(int));
      }
      ret1->data[a] = s2->data[i];
      ++a;
    }
  }
  merge_sort(ret1->data, a); 
  return ret1;
}
 