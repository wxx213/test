#ifndef DOUBLY_LIST_H_INCLUDED
#define DOUBLY_LIST_H_INCLUDED

struct doubly_list_node {
    int element;
    struct doubly_list_node *pnext;
    struct doubly_list_node *pprev;
};
struct doubly_list_head {
    struct doubly_list_node *pfirst;
};

#endif // DOUBLY_LIST_H_INCLUDED
