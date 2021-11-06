#include "../ds/list.h"
#include <stdio.h>

int main()
{
        printf("List tests:\n");
        list lst = {0};

        say_hello(2);
        construct_list(&lst, 12);

        print_list(&lst);

        destruct_list(&lst);

        return 0;
}


