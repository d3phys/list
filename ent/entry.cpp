#include <entry.h>
#include <list.h>

int list_compare(item_t itm1, item_t itm2)
{
        return itm1 > itm2;
}

void list_print_item(FILE *file, item_t item)
{
       fprintf(file, "%lf", item); 
}
