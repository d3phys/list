#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "list.h"

static item *realloc_list(list *const lst, const size_t new_cap);
static ptrdiff_t find_empty(list *const lst);
static int verify_list(list *const lst);

list *construct_list(list *const lst)
{
        assert(lst);
        assert(!lst->items);

        item *items = realloc_list(lst, INIT_CAP);
        if (!items)
                return nullptr;

        lst->items    = items;
        lst->capacity = INIT_CAP;
        lst->tail     = -1;
        lst->head     = -1;

        return lst;
}

void destruct_list(list *const lst)
{
        assert(lst);
        assert(lst->items);

        free(lst->items);
        lst->capacity =  0;
        lst->tail     = -1;
        lst->head     = -1;
}

ptrdiff_t list_insert_after(list *const lst, ptrdiff_t index, item_t value)
{
        assert(lst);

        //verify_list(lst);

        // ptrdiff_t empty = find_empty(lst);
        ptrdiff_t empty = 0; 

        lst->items[empty].next  = lst->items[index].next;
        lst->items[index].next  = empty;
        lst->items[empty].value = value;

        return empty;
}

/**
 * @brief Reallocates list memory
 *
 * @param stk List to reallocate
 * @param stk List's new capacity
 *
 * It is ANSI realloc() function wrapper.
 */
static item *realloc_list(list *const lst, const size_t new_cap)
{
        assert(lst);
        assert(new_cap);

        size_t cap  = new_cap * sizeof(item_t);
        item *items = (item *)realloc(lst->items, cap);

        return items;
}
