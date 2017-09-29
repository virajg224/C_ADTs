#include <assert.h>
#include <string.h>
#include "strdeque.h"

// a simple test client for strdeque.c

const char *apple = "apple";
const char *zebra = "zebra";

int main(void) {
  char buffer[10];
  struct strdeque *sdeq = strdeque_create();
  strcpy(buffer, apple);
  strdeque_add_front(buffer, sdeq);
  strcpy(buffer, zebra);
  strdeque_add_back(buffer, sdeq);
  assert(strcmp(strdeque_front(sdeq), apple) == 0);
  assert(strcmp(strdeque_back(sdeq), zebra) == 0);
  strdeque_remove_front(sdeq);
  assert(strcmp(strdeque_front(sdeq), zebra) == 0);
  strdeque_remove_back(sdeq);
  assert(strdeque_is_empty(sdeq));
  strdeque_destroy(sdeq);
}
