#include <list.h>
#include <stdio.h>

int main()
{
        printf("List tests:\n");
        list lst = {0};
        construct_list(&lst, 4);
        log("hey\n");

$       (dump_list(&lst);)
        //in = list_insert_after(&lst, in, 40);
        //
$       (list_insert_before(&lst, 0, 3);)
$       (dump_list(&lst);)
$       (list_insert_front(&lst, 2);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 4);)
$       (dump_list(&lst);)
$       (list_insert_front(&lst, 1);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 5);)
$       (dump_list(&lst);)
$       (sort_list(&lst);)
$       (dump_list(&lst);)
$       (list_delete(&lst, 3);)
$       (list_delete(&lst, 4);)
$       (list_delete(&lst, 5);)
$       (list_delete(&lst, 1);)
$       (dump_list(&lst);)
$       (list_delete(&lst, 2);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 10);)
$       (dump_list(&lst);)

$       (list_insert_back(&lst, 20);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 30);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 40);)
$       (dump_list(&lst);)
$       (list_insert_back(&lst, 50);)
$       (list_delete(&lst, 2);)
$       (list_delete(&lst, 4);)
$       (dump_list(&lst);)
$       (sort_list(&lst);)
$       (dump_list(&lst);)
        destruct_list(&lst);

        return 0;
}


