#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

struct single_list_node {
    int element;
    struct single_list_node *pnext;
};

struct single_list_head {
    struct single_list_node *pfirst;
};

struct single_list_head *single_list_init();
int single_list_insert(struct single_list_head *phead, int value);
void single_list_delete(struct single_list_head *phead, int value);
void single_list_print(struct single_list_head *phead);
void single_list_reverse(struct single_list_head *phead);
void single_list_reverse2(struct single_list_head *phead);
#endif // LIST_H_INCLUDED
