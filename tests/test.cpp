#include "../ds/list.h"
#include <stdio.h>

int main()
{
        printf("List tests:\n");
        list lst = {0};
        //list_insert_front(&lst, 777);
        say_hello(2);
        construct_list(&lst, 1);
        log("hey\n");

        dump_list(&lst);
$(        list_insert_front(&lst, 10);)
        dump_list(&lst);
        $(ptrdiff_t in = list_insert_after(&lst, 1, 20);)
        dump_list(&lst);
        log("IN: %ld\n", in);
$       (list_insert_back(&lst, 30);)
        dump_list(&lst);
$       (list_insert_front(&lst, 40);)
        dump_list(&lst);
$       (list_insert_back(&lst, 30);)
$       (list_insert_front(&lst, 40);)
        dump_list(&lst);
$       (list_insert_back(&lst, 30);)
$       (list_insert_front(&lst, 40);)
        dump_list(&lst);
$       (list_insert_back(&lst, 30);)
$       (list_insert_front(&lst, 40);)
        dump_list(&lst);
        $(list_delete(&lst, 2);)
        dump_list(&lst);
$       (list_insert_front(&lst, 40);)
$       (list_delete(&lst, 4);)
$       (list_delete(&lst, 6);)
$       (list_delete(&lst, 2);)
        dump_list(&lst);
        //in = list_insert_after(&lst, in, 40);
        $(list_insert_back(&lst, 50);)
        log("IN: %ld\n", in);
        dump_list(&lst);

        destruct_list(&lst);

        return 0;
}


