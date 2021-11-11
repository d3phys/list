#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <log.h>

typedef double item_t;

const item_t    FREE_DATA =  1337; 
const ptrdiff_t FREE_PREV = -1; 

struct node {
        ptrdiff_t next = -1;        
        ptrdiff_t prev = -1;        
        item_t    data =  0;        
};

struct list {
        node *nodes = nullptr;
        size_t capacity = 0;

        ptrdiff_t head = 0; 
        ptrdiff_t tail = 0; 
        ptrdiff_t free = 0;

        size_t n_nodes = 0;
};

enum list_state {
        INVALID_HEAD     = 1 << 0,
        INVALID_TAIL     = 1 << 1,
        INVALID_ITEMS    = 1 << 2,
        INVALID_CAPACITY = 1 << 3,
};

list *construct_list(list *const lst, const size_t cap);
void   destruct_list(list *const lst);

ptrdiff_t sort_list(list *const lst);

ptrdiff_t list_delete(list *const lst, ptrdiff_t index);

ptrdiff_t list_insert_after (list *const lst, ptrdiff_t index, item_t item);
ptrdiff_t list_insert_before(list *const lst, ptrdiff_t index, item_t item);

ptrdiff_t list_insert_back (list *const lst, item_t item);
ptrdiff_t list_insert_front(list *const lst, item_t item);

#ifdef DEBUG 
ptrdiff_t verify_list(const list *const lst);
#else /* DEBUG */
static inline ptrdiff_t verify_list(const list *const lst) { return 0; }
#endif /* DEBUG */

#ifdef DEBUG 
void dump_list(const list *const lst);
#else /* DEBUG */
static inline void dump_list(list *const lst) {};
#endif /* DEBUG */


#endif /* LIST_H */
