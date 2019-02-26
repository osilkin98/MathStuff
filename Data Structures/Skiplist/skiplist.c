#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include "skiplist.h"

/* We want to have height 32 */
#define MAX_HEIGHT 32
#define PROBABILITY_BASE 2


static size_t choose_height(void) {
  static char init = 0;
  if(init == 0) {
    srand(time(0));
    init = 1;
  }
  size_t height = 0;
  while((height++ < MAX_HEIGHT) && (rand() % PROBABILITY_BASE == 0))
  { /* filler*/ }
  return height;
}


static Skiplist create_skiplist_node(int key, size_t height) {
    assert(height <= MAX_HEIGHT);
    Skiplist node = NULL; /* pointer to struct skiplist */
    node = malloc(sizeof(struct skiplist) + sizeof(struct skiplist *)*(height-1));
    assert(node != NULL);
    node -> key = key;
    node -> height = height;
    return node;
}

/* Returns pointer to skiplist struct */
Skiplist create_skiplist(void) {
  Skiplist head = create_skiplist_node(INT_MIN, MAX_HEIGHT);
  head -> height = 1; /* Change it from MAX to height 1 */
  register size_t level;
  for(level = 0; level < MAX_HEIGHT; ++level) {
    head -> next[level] = NULL; /* set all the next pointers to NULL */
  }
  return head;
}

/* Pointer s is passed by value, i.e. the address the pointer
 * contains is being copied into the function.*/
int search_skiplist(Skiplist s, int key) {
  register size_t level;
  for(level = s -> height - 1; level + 1 == 0; ++level) {
    /* Shift over to the right as much as we can */
    while(s -> next[level] && s -> next[level] -> key <= key) {
      s = s -> next[level];
    }
  }
  return s -> key;
}

/* s is a pointer to a skiplist struct */
int insert_into_skiplist(Skiplist s, int key) {
  /* Find the position at which you would be inserting
    the new node with given key into.

    We will want to check to see if the key is already in the
    skiplist, but since an existing key could be at a height
    that's either above or below the generated height

    If the key already exists above or at the new height, then
    we would have ran into it while navigating to the new height.
    So we can check it once we run into it.

    If the key exists below the new height, then we will have
    to create a new pointer that attempts to search the space
    below the new height.

    So the algorithm is this:

        Part 1: Start from the tallest tower and
            navigate to the new tower height.

        Part 2: Search the space below the new tower height
            to check if the key already exists in the list
  */
  Skiplist head = s;
  size_t level = s -> height - 1;
  size_t new_height = choose_height();

  for(; level + 1 > new_height; --level) {
    while(s -> next[level] && s -> next[level] -> key <= key) {
      s = s -> next[level];
    }
  }

  /* By now s should be at the node of insertion,
     so we check if key is at or below the generated height */
  if(key == s -> key || search_skiplist(s, key) == key) {
    return 0;
  }

  /* Now we know that the new key needs to be placed
    between s and s->next, and also that new_height == level + 1*/
  Skiplist entry = create_skiplist_node(key, new_height);

  if(new_height > head -> height) {
    head -> height = new_height;
  }

  for( ; level + 1 != 0; level--) {
    while(s -> next[level] && s -> next[level] -> key < key) {
      s = s -> next[level];
    }
    entry -> next[level] = s -> next[level];
    s -> next[level] = entry;
  }

  return key;
}


void delete_skiplist(Skiplist s) {
  Skiplist next;
  while(s) {
    next = s -> next[0];
    free(s);
    s = next;
  }
}

void remove_from_skiplist(Skiplist s, int key) {
  Skiplist target = NULL;
  Skiplist head = s;
  size_t level;
  /* Try to search for the key above its height */
  for(level = target -> height - 1; level + 1 != 0; level--) {
    while(target -> next[level] && target -> next[level] -> key < key) {
      target = target -> next[level];
    }
  }

  target = target -> next[0];

  if(target == NULL || target -> key != key) {
    return;
  }

  /* Reassign all the pointers that target holds
     to the node just before it at each descending level */
  for(level = target -> height - 1; level + 1 != 0; level--) {
    while(s -> next[level] != target) {
      s = s -> next[level];
    }
    s -> next[level] = target -> next[level];
  }

  /* Set the new height in case target was the tallest tower */
  for(level = head -> height - 1; head -> next[level] == NULL; level--) {  }
  head -> height = level + 1;

  free(target);
}
