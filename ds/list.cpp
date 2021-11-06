#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <print.h>
#include "list.h"

const item_t    POISON_VALUE =  1; 
const ptrdiff_t POISON_INDEX = -1; 

static node *realloc_list(list *const lst, const size_t new_cap);
static ptrdiff_t find_empty(list *const lst);
static int verify_list(list *const lst);

list *construct_list(list *const lst, const size_t cap)
{
        assert(lst);
        assert(cap);
        assert(!lst->nodes);

        node *nodes = realloc_list(lst, cap);
        if (!nodes)
                return nullptr;

        lst->nodes    = nodes;
        lst->capacity = cap;
        lst->tail     = -1;
        lst->head     = -1;

        return lst;
}

void destruct_list(list *const lst)
{
        assert(lst);
        assert(lst->nodes);

        free(lst->nodes);
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

        lst->nodes[empty].next  = lst->nodes[index].next;
        lst->nodes[index].next  = empty;
        lst->nodes[empty].value = value;

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
static node *realloc_list(list *const lst, const size_t new_cap)
{
        assert(lst);
        assert(new_cap);
        assert(new_cap <= lst->capacity);

        static const node poison = {
                                value: POISON_VALUE,
                                next:  POISON_INDEX,
                                prev:  POISON_INDEX,
                        };

        size_t cap = new_cap * sizeof(node);

        node *const nodes = (node *)realloc(lst->nodes, cap);
        if (!nodes) {
                print("Can't realloc nodes\n");
                return nodes;
        }

        for (size_t n = lst->capacity; n < new_cap; n++)
                nodes[n] = poison;

        return nodes;
}

void print_list(list *const lst)
{
        printf("Print list: \n");

        printf("|");
        for (size_t i = 0; i < lst->capacity; i++) {
                printf(" %5.g |", lst->nodes[i].value);
        }

        printf("\n|");

        for (size_t i = 0; i < lst->capacity; i++) {
                printf(" %5.ld |", lst->nodes[i].next);
        }

        printf("\n|");

        for (size_t i = 0; i < lst->capacity; i++) {
                printf(" %5.ld |", lst->nodes[i].prev);
        }
}


