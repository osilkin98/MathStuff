#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

void print_skiplist(Skiplist s) {
  printf("null ");
  while((s = s -> next[0])) {
    printf("=> %d ", s -> key);
  }
  printf(" => INF\n");
}


int main(void) {
  Skiplist list = create_skiplist();
  for(int i = 1; i < 6; ++i) {
    insert_into_skiplist(list, rand() % 53);
    print_skiplist(list);
  }
  delete_skiplist(list);
  return 0;
}
