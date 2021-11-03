#include "../ds/list.h"
#include <stdio.h>

int main()
{
        printf("List tests:\n");
        list lst = {0};
        construct_list(&lst);

        destruct_list(&lst);

        return 0;
}


