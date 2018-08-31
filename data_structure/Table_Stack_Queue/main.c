#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"
#include "list.h"

int main()
{
    struct single_list_head *phead;
    phead = single_list_init();
    if(NULL == phead) {
        printf("single_list_init error\n");
        return 0;
    }
    single_list_insert(phead, 6);
    single_list_insert(phead, 5);
    single_list_insert(phead, 4);
    single_list_insert(phead, 3);
    single_list_insert(phead, 2);
    single_list_print(phead);
    single_list_reverse2(phead);
    single_list_print(phead);
    return 0;
}
