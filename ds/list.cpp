#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <log.h>
#include "list.h"

const item_t    FREE_DATA =  1337; 
const ptrdiff_t FREE_PREV = -1; 

static node *realloc_list(list *const lst, const size_t new_cap);
static ptrdiff_t find_empty(list *const lst);
static int verify_list(list *const lst);

static ptrdiff_t list_insert(list *const lst, 
                             item_t data, ptrdiff_t next, ptrdiff_t prev)
{
        assert(lst && lst->nodes);

        if (!lst->free) {
$               (node *nodes = realloc_list(lst, lst->capacity * 2);)
                if (!nodes)
                        return 0;
        }

        ptrdiff_t free = lst->free;

        lst->free = lst->nodes[free].next;

        lst->nodes[free] = { 
                .next = next,
                .prev = prev,
                .data = data, 
        };

        if (!prev)
                lst->head = free;

        if (!next)
                lst->tail = free;

        return free;
}

list *construct_list(list *const lst, const size_t cap)
{
        assert(lst && !lst->nodes);
        assert(cap);

        lst->free     = 0;
        lst->head     = 0;
        lst->tail     = 0;
        lst->capacity = 1;

$       (node *nodes = realloc_list(lst, cap + 1);)
        if (!nodes)
                return nullptr;

        lst->nodes[0] = { 
                .next = 0,
                .prev = 0,
                .data = 0, 
        };

        return lst;
}

void destruct_list(list *const lst)
{
        assert(lst && lst->nodes);

$       (free(lst->nodes);)

        lst->capacity =  0;
}

ptrdiff_t list_delete(list *const lst, ptrdiff_t pos)
{
        assert(lst && lst->nodes);

        assert(lst->nodes[pos].prev != FREE_PREV);
        if (lst->nodes[pos].prev == FREE_PREV) {
                log("Unable to release freed item\n");
                return pos;
        }

        node *const nodes = lst->nodes;

        if (lst->head == pos)
                lst->head = lst->nodes[pos].next;

        if (lst->tail == pos)
                lst->tail = lst->nodes[pos].prev;

        nodes[nodes[pos].next].prev = nodes[pos].prev; 
        nodes[nodes[pos].prev].next = nodes[pos].next; 

        nodes[pos].prev = FREE_PREV;
        nodes[pos].data = FREE_DATA;

        nodes[pos].next = lst->free;
        lst->free = pos;

        return pos;
}

ptrdiff_t list_insert_after(list *const lst, ptrdiff_t pos, item_t data)
{
        assert(lst && lst->nodes);

        ptrdiff_t ins = list_insert(lst, data, lst->nodes[pos].next, pos);
        if (ins && pos) {
                if (lst->nodes[pos].next)
                        lst->nodes[lst->nodes[pos].next].prev = ins;

                lst->nodes[pos].next = ins;
        }

        return ins;
}

ptrdiff_t list_insert_before(list *const lst, ptrdiff_t pos, item_t data)
{
        assert(lst && lst->nodes);

        ptrdiff_t ins = list_insert(lst, data, pos, lst->nodes[pos].prev);
        if (ins && pos) {
                if (lst->nodes[pos].prev)
                        lst->nodes[lst->nodes[pos].prev].next = ins;

                lst->nodes[pos].prev = ins;
        }

        return ins;
}

ptrdiff_t list_insert_front(list *const lst, item_t data)
{
        assert(lst && lst->nodes);
        return list_insert_before(lst, lst->head, data);
}

ptrdiff_t list_insert_back(list *const lst, item_t data)
{
        assert(lst && lst->nodes);
        return list_insert_after(lst, lst->tail, data);
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
        assert(new_cap > lst->capacity);

        size_t cap = new_cap * sizeof(node);

$       (node *const nodes = (node *)realloc(lst->nodes, cap);)
        if (!nodes)
                return nullptr;

        for (size_t n = lst->capacity; n < new_cap; n++)
                nodes[n] = { 
                        .next = n + 1,
                        .prev = FREE_PREV,
                        .data = FREE_DATA, 
                };

        nodes[new_cap - 1].next = lst->free; 

$       (lst->free = lst->capacity;)

        lst->capacity = new_cap;
        lst->nodes    = nodes;

        return nodes;
}

void dump_list(list *const lst)
{
        assert(lst);

        static unsigned dump_num = 0;

        static char buf[512] = {0};
        snprintf(buf, sizeof(buf), "dump%u.dot", dump_num);

        FILE *file = fopen(buf, "w");

//R"(afs///)"
        fprintf(file, "digraph {                                                        \n"
                                "node[penwidth=2, shape=box, color=grey, fillcolor=white, style=\"rounded, filled\", fontname=\"Courier\"]\n"
                                "fontname=\"Courier\"\n"
                                "dpi=57\n"
		                "edge[color=darkgrey, arrowhead=onormal, arrowsize=1.6, penwidth=1.2]                                      \n"
                                "graph[fillcolor=lightgreen, ranksep=1.3, nodesep=0.5,style=\"rounded,filled\",color=green, penwidth=2]                \n"
                                "compound=true;                                                       \n"
                                "                                                       \n"
                                "newrank = true;                                        \n"
                                "rankdir = LR;                                          \n",
                                dump_num);

        fprintf(file, "0");
        for (size_t i = 1; i < lst->capacity; i++) {
                fprintf(file, "-> %lu", i);
        }
        fprintf(file, "[style=invis, weight=1, minlen=\"1.5\"]");

                fprintf(file, "free->%ld:n[color=cadetblue]\n", lst->free);

                fprintf(file, "tail->%ld:p[color=cadetblue]\n", lst->tail);

                fprintf(file, "head->%ld:n[color=cadetblue]\n", lst->head);

        for (size_t i = 0; i < lst->capacity; i++) {
                fprintf(file, "subgraph cluster%lu {                                                                     \n"
                                "       label = %lu;                                                                    \n"
                                "       fontsize= 20;                                                                    \n"
                                "       %lu [shape=record, label=\"<p>prev: %ld | data: %lg | <n>next: %ld\"]     \n"
                                "}                                                                                      \n",
                                i, i, i, lst->nodes[i].prev, lst->nodes[i].data, lst->nodes[i].next);

                if (lst->nodes[i].prev != FREE_PREV)
                        fprintf(file, "%lu:n -> %ld:n[color=darkgoldenrod2, style=dashed]\n", i, lst->nodes[i].next);
                else
                        fprintf(file, "%lu:n -> %ld:n[color=mediumpurple4 ]\n", i, lst->nodes[i].next);

                if (lst->nodes[i].prev != FREE_PREV)
                        fprintf(file, "%lu:p -> %ld:p[color=darkslategray, style=dashed]\n", i, lst->nodes[i].prev);
        }


        fprintf(file, "\n}");
        fclose(file);

        snprintf(buf, sizeof(buf), "dot -Tsvg dump%u.dot -o dump%u.svg", dump_num, dump_num);
        system(buf);

        log("List dump\n <img src=\"dump%u.svg\"/>\n", dump_num);

        dump_num++;
}

