#include <list.h>
#include <assert.h>
#include <log.h>

ptrdiff_t verify_list(const list *const lst)
{
        assert(lst);

        size_t n_nodes = 0;
        node *nodes = lst->nodes;

        ptrdiff_t it = lst->head;
        if (it)
                n_nodes++;

        if (nodes[it].prev != 0)
                goto verify_error;

        for (it = nodes[lst->head].next; it != 0; it = nodes[it].next) {
                if (nodes[nodes[it].prev].next != it)
                        goto verify_error;

                n_nodes++;
        }

        it = lst->tail;
        if (nodes[it].next != 0)
                goto verify_error;

        if (lst->n_nodes != n_nodes) {
                it = -32131;
                goto verify_error;
        }

        log("SUCCESSFUL VERIFICATION\n");
        return 0;

verify_error:
$       (dump_list(lst);)
        return it;
}

void dump_list(const list *const lst)
{
        assert(lst);

        static unsigned dump_num = 0;

        static char buf[512] = {0};
        snprintf(buf, sizeof(buf), "log/dump%u.dot", dump_num);

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

        snprintf(buf, sizeof(buf), "dot -Tsvg log/dump%u.dot -o log/dump%u.svg", dump_num, dump_num);
        system(buf);

        log("\n<img src=\"log/dump%u.svg\"/>\n", dump_num);

        dump_num++;
}

