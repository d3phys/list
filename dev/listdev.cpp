#include <list.h>
#include <assert.h>
#include <log.h>

ptrdiff_t verify_list(list *const lst)
{
        assert(lst);

        size_t n_nodes = 0;
        node *nodes = lst->nodes;
        ptrdiff_t it = 0;

        if (nodes[0].prev != 0 || nodes[0].next != 0)
                goto verify_error;

        it = lst->head;
        if (nodes[it].prev != 0)
                goto verify_error;

        for (it = 1; it < lst->capacity; it++) {

                if (nodes[it].prev == FREE_PREV) {
                        if (nodes[it].next < 0 || nodes[it].next > lst->capacity)
                                goto verify_error;

                        continue;
                }

                if (nodes[it].prev < 0 || nodes[it].prev > lst->capacity) 
                        goto verify_error;

                if (nodes[it].next < 0 || nodes[it].next > lst->capacity) 
                        goto verify_error;

                if (nodes[nodes[it].prev].next != it && it != lst->head)
                        goto verify_error;

                if (nodes[nodes[it].next].prev != it && it != lst->tail)
                        goto verify_error;

                n_nodes++;
        }
        
        it = lst->free;
        for (ptrdiff_t i = 1; i < lst->capacity; i++) {
                if (nodes[it].prev != FREE_PREV && it)
                        goto verify_error;

                if (nodes[it].next < 0 || nodes[it].next > lst->capacity)
                        goto verify_error;

                it = nodes[it].next;
        }

        if (it != 0)
                goto verify_error;

        it = lst->tail;
        if (nodes[it].next != 0)
                goto verify_error;

        if (lst->n_nodes != n_nodes) {
                it = -231;
                goto verify_error;
        }


        log("<font color=\"green\">verification passed</font>\n");
        return 0;

verify_error:
        log("<font color=\"red\">DAMAGED NODE:  %ld</font>\n", it);
$       (dump_list(lst);)
        destruct_list(lst);
        exit(1);
        return it;
}

void dump_list(const list *const lst)
{
        assert(lst);

        static unsigned dump_num = 0;

        static char buf[512] = {0};
        snprintf(buf, sizeof(buf), "log/dump%u.dot", dump_num);

        FILE *file = fopen(buf, "w");

        static const char HEADER[] = R"(
                                        digraph {
                                                dpi      = 57
                                                fontname = "Courier"

                                                edge [color = darkgrey, arrowhead = onormal, arrowsize = 1.6, penwidth = 1.2]

                                                graph[fillcolor = lightgreen, ranksep = 1.3, nodesep = 0.5,
                                                      style = "rounded, filled",color = green, penwidth = 2]

                                                node [penwidth = 2, shape = box, color = grey, 
                                                      fillcolor = white, style = "rounded, filled", fontname = "Courier"]

                                                compound  =  true;
                                                newrank   =  true;
                                                rankdir   =  LR; 
                                        )";

        fprintf(file, HEADER);

        fprintf(file, "0");
        for (size_t i = 1; i < lst->capacity; i++) {
                fprintf(file, "-> %lu", i);
        }
        fprintf(file, "[style=invis, weight=1, minlen=\"1.5\"]");


        fprintf(file, "free->%ld:n[color=cadetblue]\n", lst->free);
        fprintf(file, "tail->%ld:p[color=cadetblue]\n", lst->tail);
        fprintf(file, "head->%ld:n[color=cadetblue]\n", lst->head);


        for (size_t i = 0; i < lst->capacity; i++) {
                fprintf(file, "subgraph cluster%lu { \n"
                               "       label = %lu;  \n"
                               "       fontsize= 20; \n", i, i);


               fprintf(file, "       %lu [shape=record, label=\"<p>prev: %ld | data: %lg | <n>next: %ld\"] \n} \n",
                       i, lst->nodes[i].prev, lst->nodes[i].data, lst->nodes[i].next);

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

