#include "../ds/list.h"
#include <stdio.h>

int main()
{
        printf("List tests:\n");
        list lst = {0};
        say_hello(2);
        construct_list(&lst, 4);
        log("hey\n");

        dump_list(&lst);
        //in = list_insert_after(&lst, in, 40);
        //
$       (list_insert_front(&lst, 320);)
        dump_list(&lst);
$       (list_insert_front(&lst, 320);)
        dump_list(&lst);
$       (list_insert_back(&lst, 320);)
        dump_list(&lst);
$       (list_insert_front(&lst, 320);)
        dump_list(&lst);
$       (list_insert_back(&lst, 320);)

        dump_list(&lst);

        destruct_list(&lst);

        return 0;
}


