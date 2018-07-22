#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

static void stack_empty(struct stack_record *pstack) {
    pstack->topofstack = -1;
}
static int is_stack_empty(struct stack_record *pstack) {
    return pstack->topofstack == -1;
}
static int is_stack_full(struct stack_record *pstack) {
    return pstack->topofstack == (pstack->capacity - 1);
}
struct stack_record *stack_create(int maxelements)
{
    struct stack_record *pstack;

    pstack = malloc(sizeof(struct stack_record));
    if(NULL == pstack) {
        return NULL;
    }

    pstack->parray = malloc(sizeof(stack_element) * maxelements);
    if(NULL == pstack->parray) {
        free(pstack);
        return NULL;
    }
    pstack->capacity = maxelements;
    stack_empty(pstack);

    return pstack;
}
void stack_push(struct stack_record *pstack, stack_element ele)
{
    if(is_stack_full(pstack)) {
        return;
    }
    else {
        pstack->parray[++pstack->topofstack] = ele;
    }
}

void stack_pop(struct stack_record *pstack)
{
    if(is_stack_empty(pstack)) {
        return;
    }
    else {
        pstack->topofstack--;
    }
}

stack_element stack_top(struct stack_record *pstack)
{
    if(is_stack_empty(pstack)) {
        return 0;
    }
    else {
        return pstack->parray[pstack->topofstack];
    }
    return 0;
}

