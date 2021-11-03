#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>

typedef double item_t;

const size_t INIT_CAP = 8;

struct item {
        item_t   value = 0;        
        ptrdiff_t next = 0;        
};

struct list {
        item *items = nullptr;
        size_t capacity = 0;

        ptrdiff_t head = -1; 
        ptrdiff_t tail = -1; 
};

enum list_state {
        INVALID_HEAD     = 1 << 0,
        INVALID_TAIL     = 1 << 1,
        INVALID_ITEMS    = 1 << 2,
        INVALID_CAPACITY = 1 << 3,
};

list *construct_list(list *const lst);
void destruct_list (list *const lst);

ptrdiff_t list_insert_after (list *const lst, ptrdiff_t index, item_t item);
ptrdiff_t list_insert_before(list *const lst, ptrdiff_t index, item_t item);

ptrdiff_t list_delete(list *const lst, ptrdiff_t index);

ptrdiff_t list_insert_back(list *const lst, item_t item);
ptrdiff_t list_delete_back(list *const lst, item_t item);

ptrdiff_t list_insert_front(list *const lst, item_t item);
ptrdiff_t list_delete_front(list *const lst, item_t item);

void print_list(list *const lst);


#endif /* LIST_H_ */

