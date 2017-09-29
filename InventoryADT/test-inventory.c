#include <assert.h>
#include "inventory.h"

// a simple test client for inventory.c

int main(void) {
  struct inventory *inv = inventory_create();
  assert(inventory_lookup(inv, "apples") == -1);
  inventory_add(inv, "apples", 3);
  assert(inventory_lookup(inv, "apples") == 3);
  inventory_remove(inv, "apples", 1);
  assert(inventory_lookup(inv, "apples") == 2);
  inventory_destroy(inv);
}
