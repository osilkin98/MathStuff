#ifndef SKIPLIST_H
#define SKIPLIST_H

/*
  We need to make a skiplist which has at most T towers
  with a probability of P = 1/N^{k}

                |===|
                | 3 | ----------------------------------> 40 -----------------------> 0
                |---|                                     |
                | 2 | -----------> 7 -------> 17 -------> 40 -------------> 59 -----> 0
                |---|              |          |           |                 |
                | 1 | -> 1 ------> 7 -> 16 -> 17 -------> 40 -------> 58 -> 59 -----> 0
                |---|    |         |          |           |           |     |
    +---------> | 0 | -> 1 -> 3 -> 7 -> 16 -> 17 -> 18 -> 40 -> 52 -> 58 -> 59 -----> 0
    |           |===|
    |
    |
    |
    |
  |===|
  | A |
  |===|

*/

typedef struct skiplist * Skiplist;



struct skiplist {
  int key;
  size_t height; /* The height of the node in the tower */

  /* We want to intialize 1 right away when the tower
   height is 1, so that we can point to the next create_skiplist_node
   at the very bottom*/
  struct skiplist *next[1];
};



Skiplist create_skiplist(void);

void delete_skiplist(Skiplist s);

void remove_from_skiplist(Skiplist s, int key);

int insert_into_skiplist(Skiplist s, int key);

int search_skiplist(Skiplist s, int key);

#endif
