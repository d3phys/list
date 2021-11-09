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
$       (list_delete(&lst, 3);)
$       (list_delete(&lst, 4);)
$       (list_delete(&lst, 5);)
$       (list_delete(&lst, 1);)
$       (list_delete(&lst, 2);)
        dump_list(&lst);

$       (list_insert_back(&lst, 10);)
        dump_list(&lst);
$       (list_insert_back(&lst, 20);)
        dump_list(&lst);
$       (list_insert_back(&lst, 30);)
        dump_list(&lst);
$       (list_insert_back(&lst, 40);)
        dump_list(&lst);
$       (list_insert_back(&lst, 50);)
        dump_list(&lst);
        destruct_list(&lst);

        return 0;
}


