#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#define stack_depth 50
typedef int avl_etype;

struct avlnode {
    avl_etype element;
    struct avlnode *pleft;
    struct avlnode *pright;
    int height;
};

enum context_end_child {left_end, right_end};

union context_user {
    struct avlnode *pnode;
    enum context_end_child end_child;
};

struct stack_user {
    int curr_p;
    union context_user ele_array[stack_depth];
};

struct avlnode *avltree_insert(struct avlnode *pnode, avl_etype ele);
struct avlnode *avltree_delete(struct avlnode *pnode, avl_etype ele);
void avltree_print(struct avlnode *proot);
void avltree_print2(struct avlnode *proot);
void avltree_print3(struct avlnode *proot);
void avltree_print4(struct avlnode *proot);
#endif // AVLTREE_H_INCLUDED
