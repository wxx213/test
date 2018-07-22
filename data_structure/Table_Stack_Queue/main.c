#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

int main()
{
    struct stack_record *pstack = stack_create(10);
    stack_push(pstack, 9);
    stack_push(pstack, 13);
    stack_push(pstack, 3);
    stack_pop(pstack);
    printf("%d\n", stack_top(pstack));
    return 0;
}
