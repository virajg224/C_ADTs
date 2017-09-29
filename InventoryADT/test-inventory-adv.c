#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "inventory.h"

static struct inventory *inv_a, *inv_b, *inv_c, *inv_d;

//--------------Helper Functions--------------

static struct inventory *interpret(char c){
  if (c == 'a'){
    return inv_a;
  } else if (c == 'b'){
    return inv_b;
  } else if (c == 'c'){
    return inv_c;
  } else if (c == 'd'){
    return inv_d;
  } else {
    printf("INVALID INVENTORY '%c'\n", c);
    exit(1);
  }
}

static char *readstring(){
  int len;
  scanf("%d", &len);
  ++len;
  char *str = malloc(len * sizeof(char));
  int i = 0;
  scanf("%c", &(str[i]));
  while(i < len - 1){
    scanf("%c", &(str[i]));
    ++i;
  }
  str[i] = '\0';
  return str;
}

// An advanced test program for inventory

/*
Each command takes in a parameter inv, which determines which inventory it works
on. Some commands take in additional parameters, such as quantitity.
requires: inv must be one of [a,b,c,d]
          qty must int >= 0
-----Command List------
c = inventory_create
d = inventory_destroy
l = inventory_lookup
a = inventory_add
r = inventory_remove
q = quits the program
*/

int main(void){
  char cmd, inv;
  int qty, ret;
  char *str;
  while(1){
    scanf(" %c", &cmd);
    scanf(" %c", &inv);
    if (cmd == 'c'){
      if (inv == 'a'){
        inv_a = inventory_create();
      } else if (inv == 'b'){
        inv_b = inventory_create();
      } else if (inv == 'c'){
        inv_c = inventory_create();
      } else if (inv == 'd'){
        inv_d = inventory_create();
      } else {
        printf("INVALID INVENTORY '%c'\n", inv);
        break;
      }
    } else if (cmd == 'd'){
      inventory_destroy(interpret(inv));
      if (inv == 'a'){
        inv_a = NULL;
      } else if (inv == 'b'){
        inv_b = NULL;
      } else if (inv == 'c'){
        inv_c = NULL;
      } else if (inv == 'd'){
        inv_d = NULL;
      }
    } else if (cmd == 'l'){
      str = readstring();
      ret = inventory_lookup(interpret(inv), str);
      printf("%d\n", ret);
      if (str) free(str);
    } else if (cmd == 'a'){
      scanf("%d", &qty);
      str = readstring();
      inventory_add(interpret(inv), str, qty);
      if (str) free(str);
    } else if (cmd == 'r'){
      scanf("%d", &qty);
      str = readstring();
      inventory_remove(interpret(inv), str, qty);
      if (str) free(str);
    } else if (cmd == 'q'){
      break;
    } else {
      printf("INVALID COMMAND '%c'\n", cmd);
      break;
    }
  }
  if (inv_a) inventory_destroy(inv_a);
  if (inv_b) inventory_destroy(inv_b);
  if (inv_c) inventory_destroy(inv_c);
  if (inv_d) inventory_destroy(inv_d);
}
