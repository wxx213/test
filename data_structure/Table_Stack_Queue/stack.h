#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int stack_element;

struct stack_record {
    int capacity;
    int topofstack;
    stack_element *parray;
};

struct stack_record *stack_create(int maxelements);
void stack_push(struct stack_record *pstack, stack_element ele);
void stack_pop(struct stack_record *pstack);
stack_element stack_top(struct stack_record *pstack);

#endif // STACK_H_INCLUDED
